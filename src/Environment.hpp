//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciEnvironment.hpp"
#include "OciError.hpp"
#include "OciServiceContext.hpp"

#ifndef __dbOracleEnvironment_hpp__
#define __dbOracleEnvironment_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  class Environment {

	  public:
	       Environment();
	       ~Environment();

	       Environment(const Environment&) = delete;
	       Environment& operator=(const Environment&) = delete;

	       oci::handle::Environment& getEnvironment() const;
	       oci::handle::Error& getError() const;
	       oci::handle::ServiceContext& getServiceContext() const;

	  private:
	       oci::handle::Environment* env;
	       oci::handle::Error* error;
	       oci::handle::ServiceContext* scontext;

	       void init_env();
	       void destroy_env() const;

	       void init_error();
	       void destroy_error() const;

	       void init_service_context();
	       void destroy_service_context() const;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __dbEnvironment_hpp__
