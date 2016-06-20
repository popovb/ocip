//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciErrorCode.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::ErrorCode::ErrorCode():
     code(0),
     code_string(std::to_string(code))
{
     return;
}

db::oracle::oci::ErrorCode::ErrorCode(const ub4 c):
     code(c),
     code_string(std::to_string(code))
{
     return;
}

ub4 db::oracle::oci::ErrorCode::operator*() const {

     return code;
}

db::oracle::String db::oracle::oci::ErrorCode::string() const {

     return std::to_string(code);
}
//////////////////////////////////////////////////////////////////
