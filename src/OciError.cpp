//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciError.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::handle::Error::Error(Environment& e) {

     status = OCIHandleAlloc(
	  (dvoid*) *e,
	  (dvoid**) &handle,
	  OCI_HTYPE_ERROR,
	  (size_t)0,
	  (dvoid**)0);
}

db::oracle::oci::handle::Error::~Error() {

     if (handle != nullptr) {

	  OCIHandleFree(handle, OCI_HTYPE_ERROR);
     }
}

OCIError* db::oracle::oci::handle::Error::operator*() const {

     return (OCIError*)handle;
}
//////////////////////////////////////////////////////////////////
