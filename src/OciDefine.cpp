//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciDefine.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::handle::Define::Define():
     p((OCIDefine**)(&handle))
{
     return;
}

db::oracle::oci::handle::Define::~Define() {

     if (handle != nullptr) {

	  OCIHandleFree(handle, OCI_HTYPE_DEFINE);
     }
}

db::oracle::oci::handle::Define::Handle
db::oracle::oci::handle::Define::operator*() const {

     Handle h {(OCIDefine*)handle, p};
     return h;
}

void db::oracle::oci::handle::Define::setStatus(const sword s) {

     status = s;
}
//////////////////////////////////////////////////////////////////
