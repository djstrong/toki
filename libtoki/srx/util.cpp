#include <libtoki/srx/util.h>
#include <libtoki/foreach.h>
#include <libtoki/util.h>
#include <sstream>
#include <boost/foreach.hpp>
#include <unicode/regex.h>
#include <boost/regex/icu.hpp>


namespace Toki { namespace Srx { namespace Util {

	std::string unquote_regex(const std::string& re)
	{
		std::stringstream ss;
		bool backslash = false;
		bool quoting = false;
		foreach (char c, re) {
			if (backslash) {
				if (c == 'Q' && !quoting) {
					quoting = true;
				} else if (c == 'E' && quoting) {
					quoting = false;
				} else if (quoting) {
					ss << "\\\\" << c;
				} else {
					ss << '\\' << c;
				}
				backslash = false;
			} else {
				if (c == '\\') {
					backslash = true;
				} else {
					// According to ICU regexp guide, these chars need quoting.
					// http://userguide.icu-project.org/strings/regexp
					if (quoting && (c == '*' || c == '?'
					             || c == '+' || c == '['
					             || c == '(' || c == ')'
					             || c == '{' || c == '}'
					             || c == '^' || c == '$'
					             || c == '|' || c == '\\'
					             || c == '.' || c == '/')) {
						ss << '\\' << c;
					} else {
						ss << c;
					}
				}
			}
		}
		return ss.str();
	}

	namespace {


	}

	std::string prepare_regex_for_lookbehind(const std::string& re, int max_lookbehind)
	{
		 UErrorCode ue = U_ZERO_ERROR;

		 RegexMatcher pat_star(UnicodeString::fromUTF8(
				"(?<=(?<!\\\\)(?:\\\\\\\\){0,1})\\*"), 0, ue);

		 boost::u32regex star = boost::make_u32regex(
				"(?<=(?<!\\\\)(?:\\\\\\\\)?)\\*");

		 //RegexMatcher pat_plus(UnicodeString::fromUTF8(
		//		"(?<=(?<!\\\\)(?:\\\\\\\\){0,100})(?<![\\?\\*\\+]|\\{[0-9],?[0-9]?\\}?\\})\\+"), 0, ue);

		 //RegexMatcher pat_range(UnicodeString::fromUTF8(
		//		"(?<=(?<!\\\\)(?:\\\\\\\\){0,100})\\{\\s*([0-9]+)\\s*,\\s*\\}"), 0, ue);

		 //RegexMatcher pat_capturing_group(UnicodeString::fromUTF8(
		//		"(?<=(?<!\\\\)(?:\\\\\\\\){0,100})\\((?!\\?)"), 0, ue);

		UnicodeString reu = UnicodeString::fromUTF8(unquote_regex(re));
		std::stringstream ss;

		//UErrorCode e = U_ZERO_ERROR;

		ss << "{0," << max_lookbehind << "}";
		//pat_star.reset(reu);
		//reu = pat_star.replaceAll(UnicodeString::fromUTF8(ss.str()), e);
		reu = boost::u32regex_replace(reu, star, "$&");
/*
		ss.str("");
		ss << "{1," << max_lookbehind << "}";
		pat_plus.reset(reu);
		reu = pat_plus.replaceAll(UnicodeString::fromUTF8(ss.str()), e);

		ss.str("");
		ss << "{$1," << max_lookbehind << "}";
		pat_range.reset(reu);
		reu = pat_range.replaceAll(UnicodeString::fromUTF8(ss.str()), e);
*/
		return Toki::Util::to_utf8(reu);
	}

} /* end ns Util */ } /* end ns Srx */ } /* end ns Toki */
