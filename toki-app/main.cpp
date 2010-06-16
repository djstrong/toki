#include <libtoki/layertokenizer.h>
#include <libtoki/tokenlayer.h>
#include <libtoki/token.h>
#include <libtoki/unicodeistreamwrapper.h>
#include <libtoki/unicodeicustringwrapper.h>
#include <libtoki/util.h>
#include <libtoki/debug.h>
#include <libtoki/exception.h>
#include <libtoki/srx/srx.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <unicode/ustream.h>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>


struct nullstream : std::ostream {
	struct nullbuf : std::streambuf {
		int overflow(int c) { return traits_type::not_eof(c); }
	} m_sbuf;
	nullstream(): std::ios(&m_sbuf), std::ostream(&m_sbuf) {}
};

int main(int argc, char** argv)
{
	/*
	TokenizerConfig::Cfg global = TokenizerConfig::from_file("config.ini");
	TokenizerConfig::Cfg user = TokenizerConfig::from_file("user.ini");
	TokenizerConfig::merge(global, user);
	TokenizerConfig::write(global, "combined");
	*/

	std::string input_enc;
	std::string config_file;
	std::string config_path;
	std::string srx, srx_lang, srx_mode, srx_mark_start, srx_mark_end;
	int bufsize;
	bool orths;
	bool verbose;
	bool quiet;
	bool stats;
	bool no_output;
	int progress;
	using boost::program_options::value;
	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
			("input-encoding,e", value(&input_enc)->default_value("UTF8"),
			 "Input encoding (ICU string identifier), for example UTF8, cp1250")
			("config-file,c", value(&config_file)->default_value(""),
			 "Config file to use, default_configs to library-default config")
			("config-path,C", value(&config_path)->default_value(""),
			 "Override default_config config search path")
			("buffer-size,b", value(&bufsize)->default_value(1),
			 "Stream buffer size, set to 0 to convert the entire input "
			 "in-memory before processing and disregard the encoding, assuming UTF-8.")
			("orths,o", value(&orths)->default_value(false)->zero_tokens(),
			 "Only output orths, not entire token descriptions "
			 "(ignore debug.format in config file)")
			("verbose,v", value(&verbose)->default_value(false)->zero_tokens(),
			 "Verbose init info")
			("quiet,q", value(&quiet)->default_value(false)->zero_tokens(),
			 "Suppress info output")
			("srx,S", value(&srx)->default_value(""),
			 "Load SRX from file and only do SRX processing")
			("lang,l", value(&srx_lang)->default_value("pl"),
			 "SRX language selection")
			("srx-mode", value(&srx_mode)->default_value("icu"),
			 "SRX mode selection")
			("stats,s", value(&stats)->default_value(false)->zero_tokens(),
			 "Display tokenization stats (token count) at end")
			("no-output", value(&no_output)->default_value(false)->zero_tokens(),
			 "Disable tokenization output")
			("srx-begin-marker", value(&srx_mark_start)->default_value(""),
			 "SRX segment begin marker")
			("srx-end-marker", value(&srx_mark_end)->default_value("\n"),
			 "SRX segment end marker")
			("progress-only", value(&progress)->default_value(0),
			 "No output, progress display every N tokens")
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

	nullstream nullstr;
	std::ostream& out = no_output ? nullstr : std::cout;

	if (!srx.empty()) {
		Toki::Srx::Document doc;
		std::ifstream srx_ifs(srx.c_str());
		doc.load(srx_ifs);
		if (verbose) {
			std::cout << doc.info() << "\n";
		}
		Toki::Srx::Segmenter* segm;
		segm = Toki::Srx::Segmenter::get_segmenter_by_name(srx_mode);
		if (!segm) return 5;
		segm->load_rules(doc.get_rules_for_lang(srx_lang));
		Toki::Srx::SourceWrapper srx(new Toki::UnicodeIstreamWrapper(std::cin), segm, 65536, 256);
		int segments = 0;
		out << srx_mark_start;
		while (srx.has_more_chars()) {
			if (srx.peek_begins_sentence()) {
				++segments;
				out << srx_mark_end;
				out << srx_mark_start;
			}
			out << Toki::Util::to_utf8(srx.get_next_char());
		}
		out << srx_mark_end;
		std::cout << segments << "\n";
		return 0;
	}

	if (bufsize < 0) return 3;

	if (!config_path.empty()) {
		Toki::Config::set_library_config_path(config_path);
	}
	if (verbose) {
		std::cout << "Config search path: "
			<< boost::algorithm::join(Toki::Config::get_library_config_path(), ";")
			<< "\n";
	}
	int count = 0;
	int* cptr = 0;
	if (stats) {
		cptr = &count;
	}

	try {
		const Toki::Config::Node& conf = config_file.empty() ?
			Toki::Config::default_config() :
			Toki::Config::from_file(config_file);
		Toki::LayerTokenizer tok(conf);
		if (!quiet) {
			std::cout << "Available layer types: "
				<< boost::algorithm::join(Toki::TokenLayer::available_layer_types(), " ")
				<< "\n";
			if (verbose) {
				std::cout << "Tokenizer layers:\n";
				std::cout << tok.layers_long_info("\n");
			} else {
				std::cout << "Tokenizer: " << tok.layers_info() << "\n";
			}
			std::cout << "Tokenizer started. C-d or C-c to exit.\n";
		}
		tok.set_input_source(std::cin, bufsize);
		if (progress) {
			Toki::Debug::tokenize_progress(tok, std::cerr, progress, cptr);
		} else if (orths) {
			Toki::Debug::tokenize_orths_newline(tok, out, cptr);
		} else {
			std::string format = conf.get("debug.format", "[$orth]-$type-$ws-\n");
			format = Toki::Util::unescape_utf8(format);
			Toki::Debug::tokenize_formatted(tok, format, out, cptr);
		}
		if (stats) {
			std::cout << count << "\n";
		}
	} catch (Toki::TokenizerLibError& e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
}
