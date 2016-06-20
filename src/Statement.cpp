//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Statement.hpp"
#include "Error.hpp"
#include "ReturnInfo.hpp"
#include <oci.h>

//////////////////////////////////////////////////////////////////
db::oracle::Statement::Statement(const Environment& e,
					     const StatementString s):
     oe(e),
     stmt(nullptr),
     binder(e.getError()),
     definer(e.getError()),
     fetcher(e.getError()),
     executor(e)
{
     init_stmt();
     prepare(s);
}

db::oracle::Statement::~Statement() {

     destroy_stmt();
}

void db::oracle::Statement::init_stmt() {

     stmt = new oci::handle::Stmt(oe.getEnvironment());
     if (! *stmt) {

	  throw Error("Can't init OCIStmt!");
     }
}

void db::oracle::Statement::destroy_stmt() const {

     if (stmt != nullptr) delete stmt;
}

void db::oracle::Statement::prepare(const StatementString s) {
     if (s.size() == 0) {

	  throw Error("Statement length is zero!");
     }

     text = oci::Text(s);
     oci::handle::Error& e = oe.getError();
     ReturnInfo ri(
	  e,
	  OCIStmtPrepare(
	       **stmt,
	       *e,
	       text.getText(),
	       text.length(),
	       (ub4)OCI_NTV_SYNTAX,
	       (ub4)OCI_DEFAULT
	       )
	  );

     if (! ri) {

	  throw Error(ri.string());
     }
}

db::oracle::ReturnInfo db::oracle::Statement::execute() const {

     return executor.execute(*stmt, 1);
}

db::oracle::ReturnInfo
db::oracle::Statement::execute(const IterationNumbers i) const {

     return executor.execute(*stmt, i);
}

db::oracle::ReturnInfo
db::oracle::Statement::bind(const PosNo i, const BindValue& bv) const {

     return binder.bind(*stmt, i, bv);
}

db::oracle::ReturnInfo
db::oracle::Statement::bind(const PosName i, const BindValue& bv) const {

     return binder.bind(*stmt, i, bv);
}

db::oracle::ReturnInfo
db::oracle::Statement::define(const PosNo i, const QueryValue& qv) const {

     return definer.define(*stmt, i, qv);
}

db::oracle::ReturnInfo
db::oracle::Statement::fetch() const {

     return fetcher.fetch(*stmt);
}
//////////////////////////////////////////////////////////////////
