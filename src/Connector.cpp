//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Connector.hpp"
#include "OciText.hpp"
#include "Error.hpp"
#include "ReturnInfo.hpp"
#include <oci.h>

//////////////////////////////////////////////////////////////////
void db::oracle::Connector::
Connect(const Environment& oe,
	const UserName un,
	const Password p,
	const ConnectString cs) {

     oci::Text un_txt(un);
     oci::Text p_txt(p);
     oci::Text cs_txt(cs);
     oci::handle::Error& e = oe.getError();
     oci::handle::ServiceContext& ohsc = oe.getServiceContext();
     ReturnInfo ri(
	  e,
	  OCILogon(
	       *(oe.getEnvironment()),
	       *(e),
	       (*ohsc).ptrptr,
	       un_txt.getOratext(),
	       un_txt.length(),
	       p_txt.getOratext(),
	       p_txt.length(),
	       cs_txt.getOratext(),
	       cs_txt.length()
	       )
	  );

     auto orc = ri.getReturnCode();
     ohsc.setStatus(*orc);
     if (! ohsc) {
	  if (*orc != 0) {

	       throw Error(ri.string());

	  } else {

	       throw Error("Can't init OCISvcCtx!");
	  }
     }
}

void db::oracle::Connector::
Disconnect(const Environment& oe) {

     orc = oci::ReturnCode(
	  OCILogoff(
	       (*(oe.getServiceContext())).ptr,
	       *(oe.getError())
	       )
	  );
}
//////////////////////////////////////////////////////////////////
