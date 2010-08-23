// gcc api-example.cpp -lpltagger -o api-test
#include <libtoki/tokenizer/layertokenizer.h>
#include <libtoki/sentencesplitter.h>
#include <libtoki/util/settings.h>
#include <libtoki/util/foreach.h>

#include <libpltagger/morph/dispatchanalyser.h>
#include <libpltagger/util/settings.h>

#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
	std::string config;
	if(argc > 1) config = argv[1];
	else config = "morfeusz.ini";	
	std::ifstream ifs;
	std::string fn = PlTagger::Path::Instance().find_file(config);
	if (fn.empty()) {
		std::cerr << "Config file open error for " << config << "\n";
		return 8;
	}
	ifs.open(fn.c_str());
	std::cerr << "Loading tagger configuration from " << fn << "\n";
	Toki::Config::Node cfg = Toki::Config::from_stream(ifs);
	
	Toki::LayerTokenizer tokr(std::cin);
	Toki::SentenceSplitter sentr(tokr);
	
	PlTagger::DispatchAnalyser analyser(cfg);
	
	while (sentr.has_more()) {
			std::vector<Toki::Token*> sentence = sentr.get_next_sentence();
			assert(!sentence.empty());
			std::vector<PlTagger::Token*> analysed_sentence = analyser.process_dispose(sentence);
			std::cout << "{\n";
			foreach (PlTagger::Token *tok, analysed_sentence)
			{
				std::cout << "\t" << tok->orth_utf8() << "\n";
				delete tok;
			};
			std::cout << "}\n";
		}
	return 0;
}
