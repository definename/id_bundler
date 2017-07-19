#pragma once

namespace blr
{

// Forward declaration.
class Bundler;

namespace types
{

//! Params type.
struct Params
{
	//! Destination file.
	std::string dest_;
	//! Email address.
	std::string email_;
	//! Installation id.
	std::string installationId_;
	//! Password.
	std::string password_;
	//! Source file.
	std::string src_;
};

//! Params pointer type.
using ParamsPtr = std::shared_ptr<Params>;
//! Buffer type.
using Buffer = std::vector<char>;
//! Bundler pointer type.
using BundlerPtr = std::shared_ptr<Bundler>;

} // namespace types
} // namespace bl