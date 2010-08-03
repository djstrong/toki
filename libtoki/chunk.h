#ifndef LIBPLTAGGER_CHUNK_H
#define LIBPLTAGGER_CHUNK_H

#include <libtoki/token.h>

#include <string>
#include <vector>

namespace Toki {

	class Chunk
	{
	public:
		Chunk();

		virtual ~Chunk();

		void set_xlink(const std::string& href);

		const std::string xlink() const {
			return xlink_;
		}

	private:
		std::string xlink_;
	};

	class TextChunk : public Chunk
	{
	public:
		TextChunk();

		void set_data(const UnicodeString& data);

		const UnicodeString& data() const {
			return data_;
		}

	private:
		UnicodeString data_;
	};

	class TokenChunk : public Chunk
	{
	public:
		TokenChunk();

		const std::vector<Token*> tokens() const {
			return tokens_;
		}
	private:
		std::vector<Token*> tokens_;
	};

} /* end ns PlTagger */

#endif // LIBPLTAGGER_CHUNK_H
