#include "unicodeicustringwrapper.h"

namespace Toki {

	UnicodeIcuStringWrapper::UnicodeIcuStringWrapper(const UnicodeString& u)
		: iter_(u)
	{
	}

	UnicodeIcuStringWrapper::~UnicodeIcuStringWrapper()
	{
	}

	UChar UnicodeIcuStringWrapper::peekNextChar()
	{
		return iter_.current();
	}

	UChar UnicodeIcuStringWrapper::getNextChar()
	{
		return iter_.nextPostInc();
	}

	bool UnicodeIcuStringWrapper::hasMoreChars()
	{
		return iter_.hasNext();
	}

} /* end namespace Toki */
