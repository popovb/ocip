//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "LobType.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::lob::TypeBlob::TypeBlob():
     db::oracle::oci::Type(SQLT_BLOB)
{
     return;
}

db::oracle::lob::TypeBlob::~TypeBlob() {

     return;
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::lob::TypeClob::TypeClob():
     db::oracle::oci::Type(SQLT_CLOB)
{
     return;
}

db::oracle::lob::TypeClob::~TypeClob() {

     return;
}
//////////////////////////////////////////////////////////////////
