//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Committer.hpp"
#include <oci.h>

//////////////////////////////////////////////////////////////////
db::oracle::ReturnInfo
db::oracle::Committer::Commit(const Environment& oe) const {

     oci::handle::Error& e = oe.getError();
     oci::handle::ServiceContext& s = oe.getServiceContext();
     ReturnInfo ri(
	  e,
	  OCITransCommit(
	       (*s).ptr,
	       *e,
	       (ub4)OCI_DEFAULT
	       )
	  );
     return ri;
}

db::oracle::ReturnInfo
db::oracle::Committer::Rollback(const Environment& oe) const {

     oci::handle::Error& e = oe.getError();
     oci::handle::ServiceContext& s = oe.getServiceContext();
     ReturnInfo ri(
	  e,
	  OCITransRollback(
	       (*s).ptr,
	       *e,
	       (ub4)OCI_DEFAULT
	       )
	  );
     return ri;
}
//////////////////////////////////////////////////////////////////
