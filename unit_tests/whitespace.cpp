#include "whitespacetokenizer.h"
#include "debug.h"

#include <boost/test/unit_test.hpp>

struct F {
	F()
	 : cfg(), tok(cfg), ss()
	{
	}

	~F()
	{
	}

	Config::Node cfg;
	WhitespaceTokenizer tok;
	std::stringstream ss;
};


BOOST_FIXTURE_TEST_CASE( default_input, F )
{
	BOOST_CHECK_EQUAL( Debug::tokenize_orths_newline(tok), std::string());
}

BOOST_FIXTURE_TEST_CASE( null_input, F )
{
	tok.setNullInputSource();
	BOOST_CHECK_EQUAL( Debug::tokenize_orths_newline(tok), std::string());
}

BOOST_FIXTURE_TEST_CASE( whitespace_input, F )
{
	ss << "   \n \t   \t\n \n\t ";
	tok.setInputSource(ss);
	BOOST_CHECK_EQUAL( Debug::tokenize_orths_newline(tok), std::string());
}

BOOST_FIXTURE_TEST_CASE( one_token, F )
{
	ss << "token";
	tok.setInputSource(ss);
	BOOST_CHECK_EQUAL( Debug::tokenize_orths_newline(tok), std::string("token\n"));
}

BOOST_FIXTURE_TEST_CASE( two_tokens, F )
{
	ss << "token nekot";
	tok.setInputSource(ss);
	BOOST_CHECK_EQUAL( Debug::tokenize_orths_newline(tok),
		std::string("token\nnekot\n"));
}

BOOST_FIXTURE_TEST_CASE( tokens_with_whitespace, F )
{
	ss << "  \t  token  nekot  \n \n";
	tok.setInputSource(ss);
	BOOST_CHECK_EQUAL( Debug::tokenize_orths_newline(tok),
		std::string("token\nnekot\n"));
}


