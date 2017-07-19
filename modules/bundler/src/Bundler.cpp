#include "pch.h"
#include "Bundler.h"
#include "Stub.h"

namespace blr
{

void Bundler::Bundle(types::ParamsPtr const& params) const
{
	std::ifstream src(params->src_, std::ios::binary | std::ios::in);
	if (!src)
		BOOST_THROW_EXCEPTION(std::runtime_error(
			"Unable to open source file: " + params->src_));

	blr::types::Buffer buf;
	buf.assign(
		std::istreambuf_iterator<char>(src),
		std::istreambuf_iterator<char>());

	Bundle(buf, stub::installationId, params->installationId_);
	std::cout << "Id was bundler: " << params->installationId_ << std::endl;
	Bundle(buf, stub::email, params->email_);
	std::cout << "Email was bundler: " << params->email_ << std::endl;
	Bundle(buf, stub::password, params->password_);
	std::cout << "Password was bundler: " << params->password_ << std::endl;

	std::ofstream dest(params->dest_, std::ios::binary | std::ios::out);
	if (!dest)
		BOOST_THROW_EXCEPTION(std::runtime_error(
			"Unable to open destination file: " + params->dest_));

	boost::range::copy(buf, std::ostreambuf_iterator<char>(dest));
}

void Bundler::Bundle(types::Buffer& buf, std::string const& signature, std::string const& val) const
{
	auto ret = boost::algorithm::find_first(buf, signature);
	if (!ret)
		BOOST_THROW_EXCEPTION(std::runtime_error(
			"Unable to find the stub signature for: " + signature));

	boost::range::fill_n(ret, ret.size(), 0);
	boost::range::copy(val, ret.begin());
}

} // namespace bl