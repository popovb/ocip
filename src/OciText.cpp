//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciText.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::Text::Text(const String s):
     string(s)
{
     return;
}

db::oracle::oci::Text::Text():
     string("")
{
     return;
}

CONST OraText* db::oracle::oci::Text::getOratext() const {

     return (CONST OraText*)(string.c_str());
}

CONST text* db::oracle::oci::Text::getText() const {

     return (CONST text*)(string.c_str());
}

ub4 db::oracle::oci::Text::length() const {

     return string.size();
}
//////////////////////////////////////////////////////////////////
