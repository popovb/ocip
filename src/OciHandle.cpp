//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciHandle.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::handle::Handle::Handle():
     handle(nullptr),
     status(0)
{
     return;
}

db::oracle::oci::handle::Handle::~Handle() {

     return;
}

sword db::oracle::oci::handle::Handle::getStatus() const {

     return status;
}

db::oracle::oci::handle::Handle::operator bool() const {

     if (status == 0) {
	  if (handle != nullptr) return true;
     }
     return false;
}

bool db::oracle::oci::handle::Handle::operator!() const {

     if (status != 0) return true;
     if (handle == nullptr) return true;
     return false;
}
//////////////////////////////////////////////////////////////////	  
