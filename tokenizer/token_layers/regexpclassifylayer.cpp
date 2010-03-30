#include "regexpclassifylayer.h"
#include "token.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

RegexpClassifyLayer::RegexpClassifyLayer(TokenSource* input, const Config::Node& props)
	: TokenLayer(input, props)
{
	BOOST_FOREACH (const Config::Node::value_type &v, props) {
		if (boost::algorithm::starts_with(v.first, "type:")) {
			std::string type = v.first.substr(5); //length of "type:"
			UErrorCode status = U_ZERO_ERROR;
			RegexMatcher *m = new RegexMatcher(UnicodeString::fromUTF8(v.second.data()), 0, status);
			if (U_SUCCESS(status)) {
				classifiers_.push_back(std::make_pair(type, m));
			} else {
				std::cerr << "Error in regexp for type:" << type
					<< " -- " << v.second.data() << "\n";
				delete m;
			}
		}
	}
}

RegexpClassifyLayer::~RegexpClassifyLayer()
{
	typedef std::pair<std::string, RegexMatcher*> vt;
	BOOST_FOREACH (const vt &v, classifiers_) {
		delete v.second;
	}
}

Token* RegexpClassifyLayer::processToken(Token* t)
{
	for (size_t i = 0; i < classifiers_.size(); ++i) {
		RegexMatcher& m = *classifiers_[i].second;
		m.reset(t->orth());
		UErrorCode status = U_ZERO_ERROR;
		if (m.matches(status)) {
			t->set_type(classifiers_[i].first);
			break;
		}
	}
	return t;
}
