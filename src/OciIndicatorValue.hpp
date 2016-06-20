//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include <oci.h>

#ifndef __oci_IndicatorValue_hpp__
#define __oci_IndicatorValue_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
//////////////////////////////////////////////////////////////////
	       class IndicatorValue {

	       public:
		    enum class Null { Yes, No };
		    typedef struct {

			 bool exist;
			 sb2  size;

		    } SizeBeforeTruncate;

	       public:
		    IndicatorValue();
		    IndicatorValue(const Null);
		    ~IndicatorValue();

		    bool is_null() const;
		    const sb2* ptr() const;

		    operator bool() const;

		    SizeBeforeTruncate size() const;

	       private:
		    sb2 indicator;
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __oci_IndicatorValue_hpp__
