#include "tokensource.h"
#include "token.h"
#include <ostream>
#include <sstream>

namespace Toki {

	TokenSource::TokenSource()
	{
	}

	TokenSource::~TokenSource()
	{
	}

	void TokenSource::tokenize(boost::function<void(Token *)> sink)
	{
		while (Token* t = get_next_token()) {
			sink(t);
		}
	}

} /* end namespace Toki */
