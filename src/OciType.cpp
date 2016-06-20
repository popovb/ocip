//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//
// Copyright (c) 2016, Boris Popov <popov.b@gmail.com>
//

#include "OciType.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::Type::Type(const ub2 t):
     oci_type(t)
{
     return;
}

db::oracle::oci::Type::~Type() {

     return;
}

ub2 db::oracle::oci::Type::get_oci_type() const {

     return oci_type;
}
//////////////////////////////////////////////////////////////////
