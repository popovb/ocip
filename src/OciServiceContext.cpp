//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciServiceContext.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::handle::ServiceContext::ServiceContext():
     p((OCISvcCtx**)(&handle))
{
     return;
}

db::oracle::oci::handle::ServiceContext::~ServiceContext() {

     if (handle != nullptr) {

	  OCIHandleFree(handle, OCI_HTYPE_SVCCTX);
     }
}

db::oracle::oci::handle::ServiceContext::Handle
db::oracle::oci::handle::ServiceContext::operator*() const {

     Handle h {(OCISvcCtx*)handle, p};
     return h;
}

void db::oracle::oci::handle::ServiceContext::setStatus(const sword s) {

     status = s;
}
//////////////////////////////////////////////////////////////////
