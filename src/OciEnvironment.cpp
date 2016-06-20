//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciEnvironment.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::handle::Environment::Environment() {

     status = OCIEnvCreate(
	  (OCIEnv**) &handle,
	  (ub4)OCI_DEFAULT,
	  (dvoid*)0,
	  (dvoid* (*)(dvoid*, size_t))0,
	  (dvoid* (*)(dvoid*, dvoid*, size_t))0,
	  (void (*)(dvoid*, dvoid*))0,
	  (size_t)0,
	  (dvoid**)0);
}

db::oracle::oci::handle::Environment::~Environment() {

     if (handle != nullptr) {

	  OCIHandleFree(handle, OCI_HTYPE_ENV);
     }
}

OCIEnv* db::oracle::oci::handle::Environment::operator*() const {

     return (OCIEnv*)handle;
}
//////////////////////////////////////////////////////////////////     
