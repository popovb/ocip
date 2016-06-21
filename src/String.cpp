//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "String.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::String db::oracle::chomp(const String in) {

     String inn(in);
     auto i = inn.find_last_not_of(" \n\r\t");
     if (i == std::string::npos) return inn;
     return inn.erase(i + 1);
}
//////////////////////////////////////////////////////////////////
