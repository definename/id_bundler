#include "pch.h"
#include "Bundler.h"

// Usage:
// *.exe --help
// *.exe --dest=D:/cl_token_test.exe --src=D:/libs/boost/boost_samples/assets/cl_token_test.exe --email=test@test.com --pass=qwer --id=123
// *.exe -d d:/dest/app.exe -s d:/src/app.exe -email test@test.com -p qwer

int main(int argc, char* argv[])
{
	try
	{
		boost::program_options::options_description desc("All options");
		desc.add_options()
			("help,h", "Produce help message")
			("dest,d", boost::program_options::value<std::string>(), "Specifies destination file")
			("email,e", boost::program_options::value<std::string>(), "Specifies user's email")
			("id,i", boost::program_options::value<std::string>(), "Specifies installation id")
			("pass,p", boost::program_options::value<std::string>(), "Specifies user's password")
			("src,s", boost::program_options::value<std::string>(), "Specifies source file");

		boost::program_options::variables_map vm;
		boost::program_options::store(
			boost::program_options::parse_command_line(argc, argv, desc), vm);

		boost::program_options::notify(vm);
		if (vm.count("help") || argc == 1)
		{
			std::cout << desc << std::endl;
			return -1;
		}

		blr::types::ParamsPtr params = std::make_shared<blr::types::Params>();
		if (vm.count("dest"))
			params->dest_ = vm["dest"].as<std::string>();
		if (vm.count("email"))
			params->email_ = vm["email"].as<std::string>();
		if (vm.count("id"))
			params->installationId_ = vm["id"].as<std::string>();
		if(vm.count("pass"))
			params->password_ = vm["pass"].as<std::string>();
		if (vm.count("src"))
			params->src_ = vm["src"].as<std::string>();

		blr::types::BundlerPtr bundler = std::make_shared<blr::Bundler>();
		bundler->Bundle(params);
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error occurred: " << e.what();
		return -1;
	}

	return 0;
}