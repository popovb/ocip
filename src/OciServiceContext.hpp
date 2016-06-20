//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciHandle.hpp"

#ifndef __oci_handle_ServiceContext_hpp__
#define __oci_handle_ServiceContext_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
	       namespace handle {
//////////////////////////////////////////////////////////////////
		    class ServiceContext: public Handle {

		    public:
			 typedef struct {

			      OCISvcCtx* ptr;
			      OCISvcCtx** ptrptr;

			 } Handle;

		    public:
			 ServiceContext();
			 virtual ~ServiceContext();

			 Handle operator*() const;

			 void setStatus(const sword);

		    private:
			 OCISvcCtx** p;
		    };
//////////////////////////////////////////////////////////////////
	       }
	  }
     }
}
#endif // __oci_handle_ServiceContext_hpp__
