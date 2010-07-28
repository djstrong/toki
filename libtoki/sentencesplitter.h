#ifndef SENTENCESPLITTER_H
#define SENTENCESPLITTER_H

#include <libtoki/tokensource.h>
#include <libtoki/token.h>

#include <vector>

namespace Toki {

	/**
	 * Helper class to get sentences from the tokenizer as separate vectors
	 * of Tokens.
	 */
	class SentenceSplitter
	{
	public:
		/// Create an empty splitter working with a source
		SentenceSplitter(TokenSource& ts);

		/// Destructor
		~SentenceSplitter();

		/// Source setter
		void set_source(TokenSource& ts);

		/// Source getter
		TokenSource& source() {
			return *ts_;
		}

		/// Source getter, const version
		const TokenSource& source() const {
			return *ts_;
		}

		/**
		 * Returns true if there will be more sentences, false if the source
		 * has been exhausted. May result in a token being taken from the source.
		 */
		bool has_more();

		/**
		 * Returns the next sentence, or an empty vector if the source has been
		 * exhausted.
		 */
		std::vector<Token*> get_next_sentence();

		/// Buffer accesor
		Token* get_buf();

	private:
		/// The used source
		TokenSource* ts_;

		/// Buffer for the sigle token that needs to be kept around between
		/// get_next_sentence calls, this is always the token that begins
		/// the next sentence.
		Token* buf_;
	};

} /* end ns Toki */

#endif // SENTENCESPLITTER_H
