//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "String.hpp"
#include <oci.h>

#ifndef __Oci_ErrorCode_hpp__
#define __Oci_ErrorCode_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
//////////////////////////////////////////////////////////////////
	       class ErrorCode {

	       public:
		    ErrorCode();
		    ErrorCode(const ub4);

		    ub4 operator*() const;
		    String string() const;

	       private:
		    ub4 code;
		    String code_string;
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __Oci_ErrorCode_hpp__
