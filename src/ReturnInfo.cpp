//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "ReturnInfo.hpp"
#include "OciReturnCodeMapper.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::ReturnInfo::ReturnInfo(const oci::handle::Error& e,
			   const sword s):
     success(true)
{
     oci::ReturnCodeMapper rcm(e, s);
     rcm.process();
     return_code = rcm.getReturnCode();
     error_code = rcm.getErrorCode();
     success = rcm.getSuccess();
}

db::oracle::ReturnInfo::ReturnInfo():
     success(false)
{
     return;
}

db::oracle::ReturnInfo::operator bool() const {

     return success;
}

bool db::oracle::ReturnInfo::operator!() const {

     return (! success);
}

db::oracle::String db::oracle::ReturnInfo::string() const {

     String result;
     if (return_code.string().size() != 0) {

	  add_space(result);
	  result += return_code.string();
     }

     if (return_code.string_extra().size() != 0) {

	  add_space(result);
	  result += return_code.string_extra();
     }

     if ((*error_code) != 0) {

	  add_space(result);
	  result += "error code = ";
	  result += error_code.string();
	  
     }
     return result;
}

bool db::oracle::ReturnInfo::isNoData() const {

     if (*return_code == OCI_NO_DATA) return true;
     return false;
}

bool db::oracle::ReturnInfo::needData() const {

     if (*return_code == OCI_NEED_DATA) return true;
     return false;
}

db::oracle::oci::ReturnCode
db::oracle::ReturnInfo::getReturnCode() const {

     return return_code;
}

db::oracle::oci::ErrorCode
db::oracle::ReturnInfo::getErrorCode() const {

     return error_code;
}

void db::oracle::ReturnInfo::add_space(String& s) const {

     if (s.size() != 0) s += "; ";
}
//////////////////////////////////////////////////////////////////
