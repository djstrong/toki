#include "layertokenizer.h"
#include "tokenlayer.h"
#include "token.h"
#include "unicodeistreamwrapper.h"
#include "unicodeicustringwrapper.h"
#include "debug.h"

#include <iostream>
#include <sstream>
#include <unicode/ustream.h>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>


int main(int argc, char** argv)
{
	/*
	TokenizerConfig::Cfg global = TokenizerConfig::fromFile("config.ini");
	TokenizerConfig::Cfg user = TokenizerConfig::fromFile("user.ini");
	TokenizerConfig::merge(global, user);
	TokenizerConfig::write(global, "combined");
	*/

	std::string input_enc;
	std::string config_file;
	int bufsize;
	bool orths;
	using boost::program_options::value;
	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
			("input-encoding,e", value(&input_enc)->default_value("UTF8"),
			 "Input encoding (ICU string identifier), for example UTF8, cp1250")
			("config-file,c", value(&config_file)->default_value(""),
			 "Config file to use, defaults to library-default config")
			("buffer-size,b", value(&bufsize)->default_value(1),
			 "Stream buffer size, set to 0 to convert the entire input "
			 "in-memory before processing and disregard the encoding, assuming UTF-8.")
			("orths,o", value(&orths)->default_value(false)->zero_tokens(),
			 "Only output orths, not entire token descriptions")
			("help,h", "Show help")
			;
	boost::program_options::variables_map vm;

	try {
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), vm);
	} catch (boost::program_options::error& e) {
		std::cerr << e.what() << "\n";
		return 2;
	}
	boost::program_options::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}

	if (bufsize < 0) return 3;

	const Config::Node& conf = config_file.empty() ?
		Config::Default() :
		Config::fromFile(config_file);
	LayerTokenizer tok(conf);
	std::cout << "Available layer types: "
		<< boost::algorithm::join(TokenLayer::available_layer_types(), ", ")
		<< "\n";
	std::cout << "Tokenizer started. C-d or C-c to exit.\n";
	tok.setInputSource(std::cin, bufsize);
	if (orths) {
		Debug::tokenize_orths_newline(tok, std::cout);
	} else {
		std::string format = conf.get("debug.format", "[$orth]-$type-$ws-\n");
		Debug::tokenize_formatted(tok, format, std::cout);
	}
}
