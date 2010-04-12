#ifndef INITTOKENLAYERS_H
#define INITTOKENLAYERS_H

namespace Toki {

	/**
	 * Classes derived from TokenLayer in the library that want to be avaliable via
	 * the factory should add relevant register calls in the implementation of this
	 * function. @see TokenLayer for details.
	 */
	bool init_token_layers();

} //end namespace Toki

#endif // INITTOKENLAYERS_H
