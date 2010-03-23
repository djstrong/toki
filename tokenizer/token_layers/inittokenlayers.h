#ifndef INITTOKENLAYERS_H
#define INITTOKENLAYERS_H

/**
 * Classes derived from TokenLayer in the library that want to be avaliable via
 * the factory should add relevant register calls in the implementation of this
 * function. @see TokenLayer for details.
 */
bool init_token_layers();

#endif // INITTOKENLAYERS_H
