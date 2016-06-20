//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Environment.hpp"
#include "ReturnInfo.hpp"

#ifndef __dbOracleComitter_hpp__
#define __dbOracleComitter_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  class Committer {

	  public:
	       ReturnInfo Commit(const Environment&) const;
	       ReturnInfo Rollback(const Environment&) const;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __dbOracleComitter_hpp__
