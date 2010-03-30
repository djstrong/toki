#include "inittokenlayers.h"
#include "affixsplitlayer.h"
#include "appendlayer.h"
#include "basicsplitlayer.h"
#include "combinelayer.h"
#include "regexpclassifylayer.h"
#include "lexiconclassifylayer.h"

/*
template <class T, bool T::mptr(const T&)>
bool WRAP(const T& t1, const T& t2)
{
	return t1.*mptr(t2);
}
*/

#include <boost/bind.hpp>

bool init_token_layers()
{
	static bool init_done = false;
	if (init_done) return false;
	//boost::bind(&UnicodeString::compare, _1, _2);
	TokenLayer::register_layer<TokenLayer>("passthrough");
	TokenLayer::register_layer<AffixSplitLayer>("affix_split");
	TokenLayer::register_layer<AppendLayer>("append");
	TokenLayer::register_layer<BasicSplitLayer>("split");
	TokenLayer::register_layer<CombineLayer>("combine");
	TokenLayer::register_layer<RegexpClassifyLayer>("regexp");
	TokenLayer::register_layer<CaseLexiconClassifyLayer>("lexicon");
	TokenLayer::register_layer<CaselessLexiconClassifyLayer>("lexicon_caseless");

	init_done = true;
	return true;
}
