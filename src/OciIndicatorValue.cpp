//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciIndicatorValue.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::IndicatorValue::IndicatorValue():
     indicator(0)
{
     return;
}

db::oracle::oci::IndicatorValue::IndicatorValue(const Null n):
     indicator(0)
{
     if (n == Null::Yes) indicator = -1;
     return;
}

db::oracle::oci::IndicatorValue::~IndicatorValue() {

     return;
}

bool db::oracle::oci::IndicatorValue::is_null() const {

     if (indicator == -1) return true;
     return false;
}

const sb2* db::oracle::oci::IndicatorValue::ptr() const {

     return &indicator;
}

db::oracle::oci::IndicatorValue::operator bool() const {

     if (indicator == 0) return true;
     if (indicator == -1) return true;
     return false;
}

db::oracle::oci::IndicatorValue::SizeBeforeTruncate
db::oracle::oci::IndicatorValue::size() const {

     if (indicator > 0) {

	  return {true, indicator};
     }
     return {false, 0};
}
//////////////////////////////////////////////////////////////////
