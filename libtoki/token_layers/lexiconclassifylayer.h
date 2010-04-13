#ifndef LIBTOKI_LEXICONCLASSIFYLAYER_H
#define LIBTOKI_LEXICONCLASSIFYLAYER_H

#include "tokenlayer.h"
#include "token.h"

#include <unicode/unistr.h>


#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <fstream>
#include <set>

namespace Toki {

	/**
	 * Classification layer that changes a token type if the orth matches one of
	 * the words in the given lexicon. The lexicon is a set of words.
	 *
	 * This layer is a templated class to allow various comparison functions in the
	 * word set, mainly to allow case-insensitive lexicons. Two concrete typedefs
	 * are provided:
	 *  - CaseLexiconClassifyLayer, for case-sensitive lexicons -- "lexicon" key
	 *  - CaselessLexiconClassifyLayer, for case-insensitive lexicons
	 *    -- "lexicon_caseless" key.
	 */
	template <typename CMP>
	class LexiconClassifyLayer : public TokenLayer
	{
	public:
		/**
		 * Constructor.
		 *
		 * Keys recognized in the configuration:
		 * - lexicon      - The set of orths to recognize, space or comma separated.
		 * - token_type   - Token type to set in the recognized tokens.
		 * - lexicon_file - Path to lexicon file, with one word per line, UTF-8.
		 */
		LexiconClassifyLayer(TokenSource* input, const Config::Node& props);

		/// Destructor
		~LexiconClassifyLayer();

		/// TokenLayer override
		Token* processToken(Token *t);

		/// TokenLayer override
		virtual std::string info() const;

		/// TokenLayer override
		std::string long_info() const;

	private:
		/// The set of orths to recognize
		std::set<UnicodeString, CMP> lex_;

		/// Token type to set in the recognized tokens
		std::string token_type_;
	};


	/** Implementation */

	template<typename CMP>
	LexiconClassifyLayer<CMP>::LexiconClassifyLayer(TokenSource *input, const Config::Node &props)
		: TokenLayer(input, props), lex_(), token_type_()
	{
		token_type_ = props.get<std::string>("token_type", "lex");
		std::vector<std::string> v;
		std::string sep(", ");
		const std::string& sepstring = props.get<std::string>("lexicon", "");
		boost::algorithm::split(v, sepstring, boost::is_any_of(sep));
		BOOST_FOREACH (const std::string& s, v) {
			if (!s.empty()) {
				lex_.insert(UnicodeString::fromUTF8(s).unescape());
			}
		}
		const std::string& file_string = props.get<std::string>("lexicon_file", "");
		if (!file_string.empty()) {
			std::ifstream ifs;
			if (Config::open_file_from_search_path(file_string, ifs) && ifs.good()) {
				while (ifs.good()) {
					std::string s;
					std::getline(ifs, s);
					if (!s.empty()) {
						lex_.insert(UnicodeString::fromUTF8(s).unescape());
					}
				}
			} else {
				std::cerr << "Error opening file " << file_string << "\n";
			}
		}
	}

	template<typename CMP>
	LexiconClassifyLayer<CMP>::~LexiconClassifyLayer()
	{
	}

	template<typename CMP>
	std::string LexiconClassifyLayer<CMP>::info() const
	{
		std::stringstream ss;
		ss << "lexicon{" << lex_.size() << "}";
		return ss.str();
	}

	template<typename CMP>
	std::string LexiconClassifyLayer<CMP>::long_info() const
	{
		std::stringstream ss;
		ss << ", lexicon: " << lex_.size() << " words";
		return TokenLayer::long_info() + ss.str();
	}

	template<typename CMP>
	Token* LexiconClassifyLayer<CMP>::processToken(Token *t)
	{
		if (lex_.find(t->orth()) != lex_.end()) {
			t->set_type(token_type_);
		}
		return t;
	}

	struct IcuStringCaselessCompare
	{
	public:
		bool operator()(const UnicodeString& u1, const UnicodeString& u2) {
			return u1.caseCompare(u2, 0) < 0;
		}
	};

	typedef LexiconClassifyLayer<
		std::less< UnicodeString >
	> CaseLexiconClassifyLayer;

	typedef LexiconClassifyLayer<
		IcuStringCaselessCompare
	> CaselessLexiconClassifyLayer;


	template<>
	std::string LexiconClassifyLayer<IcuStringCaselessCompare>::info() const
	{
		std::stringstream ss;
		ss << "lexicon_caseless{" << lex_.size() << "}";
		return ss.str();
	}

	template<>
	std::string LexiconClassifyLayer<IcuStringCaselessCompare>::long_info() const
	{
		std::stringstream ss;
		ss << ", lexicon_caseless: " << lex_.size() << " words";
		return TokenLayer::long_info() + ss.str();
	}

} //end namespace Toki

#endif // LIBTOKI_LEXICONCLASSIFYLAYER_H
