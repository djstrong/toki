#include "inittokenlayers.h"
#include "affixsplitlayer.h"
#include "appendlayer.h"
#include "basicsplitlayer.h"
#include "combinelayer.h"
#include "regexpclassifylayer.h"
#include "lexiconclassifylayer.h"

bool init_token_layers()
{
	static bool init_done = false;
	if (init_done) return false;

	TokenLayer::register_layer<TokenLayer>("passthrough");
	TokenLayer::register_layer<AffixSplitLayer>("affix_split");
	TokenLayer::register_layer<AppendLayer>("append");
	TokenLayer::register_layer<BasicSplitLayer>("split");
	TokenLayer::register_layer<CombineLayer>("combine");
	TokenLayer::register_layer<RegexpClassifyLayer>("regexp");
	TokenLayer::register_layer<LexiconClassifyLayer>("lexicon");

	init_done = true;
	return true;
}
