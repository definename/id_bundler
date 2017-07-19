#include "pch.h"
#include "BundlerStub.h"

void Bundle(std::string& buf, std::string const& signature, std::string const& val)
{
	std::size_t found = buf.find(signature);
	if (found == std::string::npos)
		BOOST_THROW_EXCEPTION(std::runtime_error(
			"Unable to find the stub signature for: " + signature));

	memset(&buf[found], 0, signature.size());
	*std::copy(val.begin(), val.end(), &buf[found]) = '\0';
}

int main(int argc, char* argv[])
{
	po::options_description desc("Program usage");
	po::variables_map vm;
	int ret = 0;
	try
	{
		desc.add_options()
			("help,h", "Produce help message")
			("dest", po::value<std::string>()->required(), "Specifies destination file")
			("email", po::value<std::string>()->required(), "Specifies user's email")
			("id", po::value<std::string>()->required(), "Specifies installation id")
			("ip", po::value<std::string>()->required(), "Specifies server host")
			("pass", po::value<std::string>()->required(), "Specifies user's password")
			("port", po::value<std::string>()->required(), "Specifies server port")
			("src", po::value<std::string>()->required(), "Specifies source file");

		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		std::string srcPath(vm.at("src").as<std::string>());
		std::ifstream src(srcPath.c_str(), std::ios::binary | std::ios::in);
		if (!src)
			BOOST_THROW_EXCEPTION(std::runtime_error(
				"Unable to open source file: " + srcPath));

		std::string buf;
		buf.assign(std::istreambuf_iterator<char>(src), std::istreambuf_iterator<char>());

		Bundle(buf, bundler::stub::email, vm.at("email").as<std::string>());
		Bundle(buf, bundler::stub::installationId, vm.at("id").as<std::string>());
		Bundle(buf, bundler::stub::serverHost, vm.at("ip").as<std::string>());
		Bundle(buf, bundler::stub::password, vm.at("pass").as<std::string>());
		Bundle(buf, bundler::stub::serverPort, vm.at("port").as<std::string>());

		std::string destPath(vm.at("dest").as<std::string>());
		std::ofstream dest(destPath.c_str(), std::ios::binary | std::ios::out);
		if (!dest)
			BOOST_THROW_EXCEPTION(std::runtime_error(
				"Unable to open destination file: " + destPath));

		dest.write(&buf[0], buf.size());
	}
	catch (po::required_option const& e)
	{
		if (vm.count("help"))
		{
			std::cerr << desc << std::endl;
			return ret;
		}

		std::cerr << "Error occurred: " << e.what() << std::endl;
		ret = -1;
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error occurred: " << e.what() << std::endl;
		ret = -1;
	}

	return ret;
}
