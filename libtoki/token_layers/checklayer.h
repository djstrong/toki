#ifndef LIBTOKI_CHECKLAYER_H
#define LIBTOKI_CHECKLAYER_H

#include "tokenlayer.h"

namespace Toki {

	class CheckLayer : public TokenLayer
	{
	public:
		/**
		 * Constructor.
		 *
		 * Keys recognized in the configuration:
		 * - max_token_size      - token size to consider overly huge, defaults
		 *                         to 300 characters
		 * - max_sentence_size   - sentence size to consider overly huge,
		 *                         defaults to 1000 tokens
		 * - huge_token_warn     - set to 0 to disable huge token warnings
		 * - huge_sentence_warn  - set to 0 to disable huge sentence warnings
		 * - huge_sentence_split - set to 1 to force-split huge sentences
		 * - warn_format         - either 1 for a '1' char for every warning,
		 *                       - 01 to also emit '0' for tokens with no
		 *                         warnings, and text for a text message.
		 */
		CheckLayer(TokenSource* input, const Config::Node& props);

		/// Destrctor
		~CheckLayer();

		/// TokenLayer override
		Token* process_token(Token *t);

		/// TokenLayer override
		virtual std::string info() const;

		/// TokenLayer override
		std::string long_info() const;

		/// TokenLayer override
		void reset();

	private:
		bool warn(const std::string& msg);

		/// behavior flags
		int max_token_size_;
		int max_sentence_size_;
		bool huge_token_warn_;
		bool huge_sentence_warn_;
		bool huge_sentence_split_;

		bool emit_0_on_no_warnings_;
		bool emit_1_on_warnings_;

		int token_counter_;
		int sentence_size_counter_;
	};

} /* end ns Toki */

#endif // LIBTOKI_CHECKLAYER_H
