#ifndef LIBTOKI_SENTENCE_H
#define LIBTOKI_SENTENCE_H

#include <libtoki/token.h>

#include <libpwrutils/sentence.h>

namespace Toki {

/// typedef for a sentence of Toki tokens
typedef PwrNlp::SentenceTemplate<Token> Sentence;

} /* end ns Toki */

#endif // LIBTOKI_SENTENCE_H
