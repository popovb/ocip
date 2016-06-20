//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Environment.hpp"
#include "Connector.hpp"
#include "Committer.hpp"
#include "ReturnInfo.hpp"
#include "Statement.hpp"
#include "LobLocator.hpp"

#ifndef __dbOracleDriver_hpp__
#define __dbOracleDriver_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  class Driver {

	  public:
	       Driver();
	       ~Driver();

	       void connect(const UserName,
			    const Password,
			    const ConnectString);
	       void disconnect();

	       ReturnInfo commit() const;
	       ReturnInfo rollback() const;

	       StatementPtr prepare(const StatementString) const;
	       oracle::lob::LocatorPtr make_locator() const;

	  private:
	       Environment oe;
	       Connector oc;
	       Committer committer;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __dbOracleDriver_hpp__
