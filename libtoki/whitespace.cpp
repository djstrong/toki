#include <libtoki/whitespace.h>

namespace Toki {

	std::string Whitespace::to_string(Whitespace::Enum wa)
	{
		switch (wa) {
		case Whitespace::None:
			return "none";
		case Whitespace::Space:
			return "space";
		case Whitespace::ManySpaces:
			return "spaces";
		case Whitespace::Newline:
			return "newline";
		case Whitespace::ManyNewlines:
			return "newlines";
		default:
			return "???";
		}
	}

	Whitespace::Enum Whitespace::from_string(const std::string &s)
	{
		int w = Whitespace::None;
		while (w < Whitespace::PostLast && Whitespace::to_string((Whitespace::Enum)w) != s) ++w;
		return (Whitespace::Enum)w;
	}

} /* end namespace Toki */
