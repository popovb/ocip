//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciHandle.hpp"

#ifndef __oci_handle_Bind_hpp__
#define __oci_handle_Bind_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
	       namespace handle {
//////////////////////////////////////////////////////////////////
		    class Bind: public Handle {

		    public:
			 typedef struct {

			      OCIBind* ptr;
			      OCIBind** ptrptr;

			 } Handle;

		    public:
			 Bind();
			 virtual ~Bind();

			 Handle operator*() const;

			 void setStatus(const sword);

		    private:
			 OCIBind** p;
		    };
//////////////////////////////////////////////////////////////////
	       }
	  }
     }
}
#endif // __oci_handle_Bind_hpp__
