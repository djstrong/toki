#ifndef LIBTOKI_TOKENIZER_H
#define LIBTOKI_TOKENIZER_H

#include "tokensource.h"
#include "config.h"
#include "unicodesource.h"

#include <vector>
#include <iosfwd>

#include <unicode/unistr.h>

#include <boost/shared_ptr.hpp>

namespace Toki {

	/**
	 * A tokenizer represents a class that grabs unicode characters from a
	 * UnicodeSource and returns Tokens.
	 */
	class Tokenizer : public TokenSource
	{
	public:
		/**
		 * Construct an empty Tokenizer. The input source will be a null object that
		 * will always claim there are no more characters, so get_next_token() will
		 * just return null.
		 */
		Tokenizer(const Config::Node& cfg = Config::default_config());

		/**
		 * Constructor shorthand -- start with the given UnicodeSource, and take
		 * ownership (through a shared pointer).
		 * @see set_input_source
		 */
		Tokenizer(UnicodeSource* input, const Config::Node& cfg = Config::default_config());

		/**
		 * Constructor shorthand -- start with the given UnicodeSource as a shared
		 * pointer
		 * @see set_input_source
		 */
		Tokenizer(boost::shared_ptr<UnicodeSource> input, const Config::Node& cfg = Config::default_config());

		/**
		 * Constructor shorthand -- start with the given std::istream. Note no
		 * ownership is taken and the stream must live long enough.
		 * @see set_input_source
		 */
		Tokenizer(std::istream& is, const Config::Node& cfg = Config::default_config());

		/**
		 * Constructor shorthand -- start with the given UnicodeString, which is
		 * copied.
		 * @see set_input_source
		 */
		Tokenizer(const UnicodeString& s, const Config::Node& cfg = Config::default_config());

		/**
		 * Destructor
		 */
		~Tokenizer();

		/**
		 * Explicitly set the input source to be a null object that never returns
		 * any unicode characters
		 */
		void set_null_input_source();

		/**
		 * Input source setter. The tokenizer takes ownership of the source
		 * (through a shared pointer)and will delete it.
		 * Note, however, that if the source is a UnicodeIstreamWrapper, the
		 * underlying istream object will *not* be deleted -- see
		 * UnicodeIstreamWrapper, which also requires that the istream lives for as
		 * long as the UnicodeIstreamWrapper lives.
		 * @param us a valid UnicodeSource to use and take ownership of. Behavior is
		 *           undefined if the pointer is invalid or NULL.
		 */
		void set_input_source(UnicodeSource* us);

		/**
		 * Input source setter -- as a shared pointer. See the are pointer version
		 * for info on what happens on the atcual destruction.
		 */
		void set_input_source(boost::shared_ptr<UnicodeSource> us);

		/**
		 * Input source setter. The stream must live for as long as the tokenizer
		 * lives.
		 */
		void set_input_source(std::istream& is, int bufsize = 1000);

		/**
		 * Input source setter. The string is copied.
		 */
		void set_input_source(const UnicodeString& s);

		/**
		 * Reset the tokenizer internal state (other than the input source).
		 * Call this when after setting a new input source if the processing should
		 * start from scratch.
		 *
		 * Derived classes should take care to always call the parent class' reset()
		 */
		virtual void reset();

		/**
		 * Accessor for the used input source
		 */
		boost::shared_ptr<UnicodeSource> get_input_source() {
			return input_;
		}

	protected:
		/**
		 * Shorthand to avoid derived classes having to explicitly use the pointer
		 */
		UnicodeSource& input() {
			return *input_;
		}

		/**
		 * Apply the configuration -- helper o avoid repeating code in ctors
		 */
		void apply_configuration(const Config::Node& cfg);

		/**
		 * Called when a new input source is created, derived classes might want to
		 * override this.
		 *
		 * WARNING: this will *NOT* be called during the initial construction of a
		 * Tokenizer, or rather, the overriden version will not be called, so
		 * derived classess should manually call their handler in constructors that
		 * cause an actual input source to be set.
		 */
		virtual void new_input_source() {}
	//private:
		/**
		 * The source of the text.
		 */
		boost::shared_ptr<UnicodeSource> input_;
	};

} /* end ns Toki */

#endif // LIBTOKI_TOKENIZER_H
