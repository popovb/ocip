//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Environment.hpp"
#include "OciReturnCode.hpp"
#include "String.hpp"

#ifndef __dbOracleConnector_hpp__
#define __dbOracleConnector_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  typedef String UserName;
	  typedef String Password;
	  typedef String ConnectString;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	  class Connector {

	  public:
	       void Connect(const Environment&,
			    const UserName,
			    const Password,
			    const ConnectString);
	  
	       void Disconnect(const Environment&);

	  private:
	       oci::ReturnCode orc;	  
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __dbOracleConnector_hpp__
