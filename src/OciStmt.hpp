//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciHandle.hpp"
#include "OciEnvironment.hpp"

#ifndef __oci_handle_Stmt_hpp__
#define __oci_handle_Stmt_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
	       namespace handle {
//////////////////////////////////////////////////////////////////
		    class Stmt: public Handle {

		    public:
			 Stmt(Environment&);
			 virtual ~Stmt();

			 OCIStmt* operator*() const;
		    };
//////////////////////////////////////////////////////////////////
	       }
	  }
     }
}
#endif // __oci_handle_Stmt_hpp__
