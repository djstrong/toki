#include "whitespacetokenizer.h"
#include "debug.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( whitespace )

struct F {
	F()
	 : cfg(), tok(cfg), ss()
	{
	}

	~F()
	{
	}

	Toki::Config::Node cfg;
	Toki::WhitespaceTokenizer tok;
	std::stringstream ss;
};


BOOST_FIXTURE_TEST_CASE( default_config_input, F )
{
	BOOST_CHECK_EQUAL( Toki::Debug::tokenize_orths_newline(tok), std::string());
}

BOOST_FIXTURE_TEST_CASE( null_input, F )
{
	tok.set_null_input_source();
	BOOST_CHECK_EQUAL( Toki::Debug::tokenize_orths_newline(tok), std::string());
}

BOOST_FIXTURE_TEST_CASE( whitespace_input, F )
{
	ss << "   \n \t   \t\n \n\t ";
	tok.set_input_source(ss);
	BOOST_CHECK_EQUAL( Toki::Debug::tokenize_orths_newline(tok), std::string());
}

BOOST_FIXTURE_TEST_CASE( one_token, F )
{
	ss << "token";
	tok.set_input_source(ss);
	BOOST_CHECK_EQUAL( Toki::Debug::tokenize_orths_newline(tok), std::string("token\n"));
}

BOOST_FIXTURE_TEST_CASE( two_tokens, F )
{
	ss << "token nekot";
	tok.set_input_source(ss);
	BOOST_CHECK_EQUAL( Toki::Debug::tokenize_orths_newline(tok),
		std::string("token\nnekot\n"));
}

BOOST_FIXTURE_TEST_CASE( tokens_with_whitespace, F )
{
	ss << "  \t  token  nekot  \n \n";
	tok.set_input_source(ss);
	BOOST_CHECK_EQUAL( Toki::Debug::tokenize_orths_newline(tok),
		std::string("token\nnekot\n"));
}

BOOST_AUTO_TEST_SUITE_END()
