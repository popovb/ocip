//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "QueryValue.hpp"
#include "QueryBuffer.hpp"
#include "LobType.hpp"
#include "LobLocator.hpp"
#include "LobQueryBuffer.hpp"

#ifndef __db_oracle_lob_Query_Value_hpp__
#define __db_oracle_lob_Query_Value_hpp__

namespace db {
     namespace oracle {
	  namespace lob {
//////////////////////////////////////////////////////////////////
	       class QueryValue: public oracle::QueryValue {

	       public:
		    QueryValue(const oci::Type,
			       const LocatorPtr);
		    virtual ~QueryValue() = 0;

		    virtual oracle::Buffer&
		    getBuffer() override;

		    virtual const oracle::Buffer&
		    getBuffer() const override;

		    LocatorPtr getLocator() const;

	       private:
		    Buffer qb;
		    const LocatorPtr locator;
	       };
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	       class BlobQueryValue: public QueryValue {

	       public:
		    BlobQueryValue(const LocatorPtr);
		    virtual ~BlobQueryValue();
	       };
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	       class ClobQueryValue: public QueryValue {

	       public:
		    ClobQueryValue(const LocatorPtr);
		    virtual ~ClobQueryValue();
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_lob_Query_Value_hpp__
