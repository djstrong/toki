#include "unicodeicustringwrapper.h"

namespace Toki {

	UnicodeIcuStringWrapper::UnicodeIcuStringWrapper(const UnicodeString& u)
		: iter_(u)
	{
	}

	UnicodeIcuStringWrapper::~UnicodeIcuStringWrapper()
	{
	}

	UChar UnicodeIcuStringWrapper::peek_next_char()
	{
		return iter_.current();
	}

	UChar UnicodeIcuStringWrapper::get_next_char()
	{
		return iter_.nextPostInc();
	}

	bool UnicodeIcuStringWrapper::has_more_chars()
	{
		return iter_.hasNext();
	}

} /* end namespace Toki */
