#include "icustringsource.h"

IcuStringSource::IcuStringSource(const UnicodeString& u)
	: iter_(u)
{
}

IcuStringSource::~IcuStringSource()
{
}

UChar IcuStringSource::peekNextChar()
{
	return iter_.current();
}

UChar IcuStringSource::getNextChar()
{
	return iter_.nextPostInc();
}

bool IcuStringSource::hasMoreChars()
{
	return iter_.hasNext();
}
