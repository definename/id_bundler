#pragma once

#include "BundlerTypes.h"

namespace blr
{

class Bundler
{
	//
	// Construction and destruction
	//
public:
	//! Constructor.
	Bundler() = default;
	//! Destructor.
	~Bundler() = default;

	//
	// Public interface.
	//
public:
	//! Prepares bundling with given params.
	void Bundle(types::ParamsPtr const& params) const;

	//
	// Private interface
	//
private:
	//! Bundles given stub signature with given value.
	void Bundle(types::Buffer& buf, std::string const& signature, std::string const& val) const;
};

} // namespace bl