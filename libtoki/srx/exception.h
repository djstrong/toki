#ifndef LIBTOKI_SRX_EXCEPTION_H
#define LIBTOKI_SRX_EXCEPTION_H

#include <libtoki/exception.h>

namespace Toki { namespace Srx {

	class Error : public TokenizerLibError
	{
	public:
		Error(const std::string& what)
			: TokenizerLibError("SRX error: " + what)
		{
		}

		~Error() throw()
		{
		}
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_EXCEPTION_H
