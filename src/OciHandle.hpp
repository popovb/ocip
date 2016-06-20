//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include <oci.h>

#ifndef __oci_handle_Handle_hpp__
#define __oci_handle_Handle_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
	       namespace handle {
//////////////////////////////////////////////////////////////////
		    class Handle {

		    public:
			 Handle();
			 virtual ~Handle() = 0;

			 sword getStatus() const;

			 operator bool() const;
			 bool operator!() const;

		    protected:
			 dvoid* handle;
			 sword status;
		    };
//////////////////////////////////////////////////////////////////
	       }
	  }
     }
}
#endif // __oci_handle_Handle_hpp__
