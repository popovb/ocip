//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Environment.hpp"
#include "ReturnInfo.hpp"
#include "OciStmt.hpp"

#ifndef __db_OracleExecutor_hpp__
#define __db_OracleExecutor_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  typedef unsigned int IterationNumbers;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	  class Executor {

	  public:
	       Executor(const Environment&);

	       ReturnInfo execute(const oci::handle::Stmt&,
				  const IterationNumbers) const;
	  private:
	       const Environment& oe;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __db_OracleExecutor_hpp__
