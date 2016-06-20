//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciError.hpp"
#include "OciReturnCode.hpp"
#include "OciErrorCode.hpp"
#include "String.hpp"
#include <oci.h>
#include <map>

#ifndef __Oci_ReturnCodeMapper_hpp__
#define __Oci_ReturnCodeMapper_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
//////////////////////////////////////////////////////////////////
	       class ReturnCodeMapper {

	       public:
		    ReturnCodeMapper(const handle::Error&,
				     const sword);

		    void process();

		    ReturnCode getReturnCode() const;
		    ErrorCode getErrorCode() const;
		    bool getSuccess() const;

	       private:
		    typedef bool AdditionalDiagnostic;
		    struct Data {

			 String str;
			 AdditionalDiagnostic ad;
		    };

		    const std::map<const sword, const Data> map;
		    String error_from_handler();
		    ub4 errcode;

		    const oci::handle::Error& err;
		    const sword ret;

		    bool success;
		    void is_it_success();

		    String code_string;
		    String code_string_extra;

		    void fill_strings();
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __Oci_ReturnCodeMapper_hpp__
