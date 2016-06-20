//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Executor.hpp"
#include "OciError.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::Executor::Executor(const Environment& o):
     oe(o)
{
     return;
}

db::oracle::ReturnInfo
db::oracle::Executor::execute(const oci::handle::Stmt& s,
			      const IterationNumbers in) const {

     oci::handle::ServiceContext& sc = oe.getServiceContext();
     oci::handle::Error& e = oe.getError();

     ReturnInfo ri(
	  e,
	  OCIStmtExecute(
	       (*sc).ptr,
	       *s,
	       *e,
	       (ub4)in,
	       (ub4)0,
	       (CONST OCISnapshot*)NULL,
	       (OCISnapshot*)NULL,
	       (ub4)OCI_DEFAULT
	       )
	  );
     return ri;
}
//////////////////////////////////////////////////////////////////
