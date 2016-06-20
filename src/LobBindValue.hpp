//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "BindValue.hpp"
#include "OciIndicatorValue.hpp"
#include "LobType.hpp"
#include "LobLocator.hpp"

#ifndef __db_oracle_lob_BINDVALUE_hpp__
#define __db_oracle_lob_BINDVALUE_hpp__

namespace db {
     namespace oracle {
	  namespace lob {
//////////////////////////////////////////////////////////////////
	       class BindValue: public oracle::BindValue {

	       public:
		    BindValue(const oci::IndicatorValue::Null,
			      const oci::Type,
			      const LocatorPtr);
		    BindValue(const oci::IndicatorValue::Null,
			      const oci::Type);

		    virtual ~BindValue() = 0;

		    virtual void* buffer() const override;
		    virtual size_t size() const override;

	       private:
		    void** buff;
		    size_t s;

		    void load_buff(const LocatorPtr);
	       };
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	       class BlobBindValue: public BindValue {

	       public:
		    BlobBindValue(const LocatorPtr);
		    BlobBindValue();

		    virtual ~BlobBindValue();
	       };
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	       class ClobBindValue: public BindValue {

	       public:
		    ClobBindValue(const LocatorPtr);
		    ClobBindValue();

		    virtual ~ClobBindValue();
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_lob_BINDVALUE_hpp__
