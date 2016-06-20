//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "String.hpp"
#include <stdexcept>

#ifndef __db_OracleError_hpp__
#define __db_OracleError_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  typedef String ErrorMessage;
//////////////////////////////////////////////////////////////////     

//////////////////////////////////////////////////////////////////
	  class Error: public std::runtime_error {

	  public:
	       Error(const ErrorMessage);
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __db_OracleError_hpp__
