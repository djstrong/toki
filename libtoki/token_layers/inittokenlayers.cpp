/*
    Copyright (C) 2010 Tomasz Śniatowski, Adam Radziszewski
    Part of the libtoki project

    This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3 of the License, or (at your option)
any later version.

    This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. 

    See the LICENSE and COPYING files for more details.
*/

#include <libtoki/token_layers/inittokenlayers.h>
#include <libtoki/token_layers/affixsplitlayer.h>
#include <libtoki/token_layers/appendlayer.h>
#include <libtoki/token_layers/basicsplitlayer.h>
#include <libtoki/token_layers/checklayer.h>
#include <libtoki/token_layers/combinelayer.h>
#include <libtoki/token_layers/groupsplitlayer.h>
#include <libtoki/token_layers/groupaffixsplitlayer.h>
#include <libtoki/token_layers/regexpclassifylayer.h>
#include <libtoki/token_layers/regexmatchsplitlayer.h>
#include <libtoki/token_layers/lexiconclassifylayer.h>

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
