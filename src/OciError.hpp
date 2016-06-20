//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciEnvironment.hpp"
#include "OciHandle.hpp"

#ifndef __oci_handle_Error_hpp__
#define __oci_handle_Error_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
	       namespace handle {
//////////////////////////////////////////////////////////////////
		    class Error: public Handle {

		    public:
			 Error(Environment&);
			 virtual ~Error();

			 OCIError* operator*() const;
		    };
//////////////////////////////////////////////////////////////////
	       }
	  }
     }
}
#endif // __oci_handle_Error_hpp__
