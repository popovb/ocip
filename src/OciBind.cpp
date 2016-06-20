//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciBind.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::handle::Bind::Bind():
     p((OCIBind**)(&handle))
{
     return;
}

db::oracle::oci::handle::Bind::~Bind() {

     if (handle != nullptr) {

	  OCIHandleFree(handle, OCI_HTYPE_BIND);
     }
}

db::oracle::oci::handle::Bind::Handle
db::oracle::oci::handle::Bind::operator*() const {

     Handle h {(OCIBind*)handle, p};
     return h;
}

void db::oracle::oci::handle::Bind::setStatus(const sword s) {

     status = s;
}
//////////////////////////////////////////////////////////////////
