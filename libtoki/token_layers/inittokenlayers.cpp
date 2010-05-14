#include "inittokenlayers.h"
#include "affixsplitlayer.h"
#include "appendlayer.h"
#include "basicsplitlayer.h"
#include "checklayer.h"
#include "combinelayer.h"
#include "groupsplitlayer.h"
#include "groupaffixsplitlayer.h"
#include "regexpclassifylayer.h"
#include "regexmatchsplitlayer.h"
#include "lexiconclassifylayer.h"

namespace Toki {

	bool init_token_layers()
	{
		static bool init_done = false;
		if (init_done) return false;
		TokenLayer::register_layer<TokenLayer>("passthrough");
		TokenLayer::register_layer<AffixSplitLayer>("affix_split");
		TokenLayer::register_layer<AppendLayer>("append");
		TokenLayer::register_layer<BasicSplitLayer>("split");
		TokenLayer::register_layer<GroupSplitLayer>("group_split");
		TokenLayer::register_layer<GroupAffixSplitLayer>("group_affix_split");
		TokenLayer::register_layer<CheckLayer>("check");
		TokenLayer::register_layer<CombineLayer>("combine");
		TokenLayer::register_layer<RegexpClassifyLayer>("regexp");
		TokenLayer::register_layer<CaseLexiconClassifyLayer>("lexicon");
		TokenLayer::register_layer<CaselessLexiconClassifyLayer>("lexicon_caseless");
		TokenLayer::register_layer<RegexMatchSplitLayer>("regex_match_split");
		init_done = true;
		return true;
	}

} /* end namespace Toki */
