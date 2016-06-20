//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciReturnCode.hpp"
#include "OciErrorCode.hpp"
#include "OciError.hpp"
#include "String.hpp"

#ifndef __dbOracleReturnInfo_hpp__
#define __dbOracleReturnInfo_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  class ReturnInfo {

	  public:
	       ReturnInfo(const oci::handle::Error&,
			  const sword);

	       operator bool() const;
	       bool operator!() const;

	       String string() const;
	       bool isNoData() const;

	       oci::ReturnCode getReturnCode() const;
	       oci::ErrorCode getErrorCode() const;

	  private:
	       oci::ReturnCode return_code;
	       oci::ErrorCode error_code;

	       bool success;

	       void add_space(String&) const;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __dbOracleReturnInfo_hpp__
