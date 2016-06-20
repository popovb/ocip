//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciReturnCode.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::ReturnCode::ReturnCode():
     code(OCI_SUCCESS),
     str("OCI_SUCCESS"),
     str_extra("")
{
     return;
}

db::oracle::oci::ReturnCode::ReturnCode(const sword s):
     code(s),
     str(""),
     str_extra("")
{
     return;
}

db::oracle::oci::ReturnCode::ReturnCode(const sword s,
					const CodeString s1,
					const CodeStringExtra s2):
     code(s),
     str(s1),
     str_extra(s2)
{
     return;
}

db::oracle::oci::ReturnCode&
db::oracle::oci::ReturnCode::operator=(const ReturnCode& rc) {

     code = rc.code;
     str = rc.str;
     str_extra = rc.str_extra;
     return *this;
}

sword db::oracle::oci::ReturnCode::operator*() const {

     return code;
}

db::oracle::oci::CodeString
db::oracle::oci::ReturnCode::string() const {

     return str;
}

db::oracle::oci::CodeStringExtra
db::oracle::oci::ReturnCode::string_extra() const {

     return str_extra;
}
//////////////////////////////////////////////////////////////////
