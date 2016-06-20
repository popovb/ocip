//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Driver.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::Driver::Driver() {

     return;
}

db::oracle::Driver::~Driver() {

     disconnect();
}

void db::oracle::Driver::connect(const UserName un,
			       const Password p,
			       const ConnectString cs) {

     oc.Connect(oe, un, p, cs);
}

void db::oracle::Driver::disconnect() {

     oc.Disconnect(oe);
}

db::oracle::ReturnInfo db::oracle::Driver::commit() const {

     return committer.Commit(oe);
}

db::oracle::ReturnInfo db::oracle::Driver::rollback() const {

     return committer.Rollback(oe);
}

db::oracle::StatementPtr
db::oracle::Driver::prepare(const StatementString s) const {

     return std::make_shared<Statement>(oe, s);
}

db::oracle::lob::LocatorPtr
db::oracle::Driver::make_locator() const {

     return std::make_shared<lob::Locator>(oe);
}
//////////////////////////////////////////////////////////////////
