/*
    Copyright (C) 2010 Tomasz Śniatowski, Adam Radziszewski
    Part of the libtoki project

    This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3 of the License, or (at your option)
any later version.

    This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. 

    See the LICENSE and COPYING files for more details.
*/

/* Code to display version info and greeting message when the .so is run */

#ifdef __GNUG__
#ifdef __linux__

#ifndef LIBTOKI_INTERP
#ifdef __LP64__
#define LIBTOKI_INTERP "/lib/ld-linux-x86-64.so.2";
#else
#define LIBTOKI_INTERP "/lib/ld-linux.so.2";
#endif
#endif

#ifdef LIBTOKI_INTERP
extern "C"
const char my_interp[] __attribute__((section(".interp"))) = LIBTOKI_INTERP;
#endif

#ifdef HAVE_CONFIG_D_H
#include <libtoki/config_d.h>
#endif
#include <libtoki/tokenlayer.h>
#include <libtoki/token_layers/inittokenlayers.h>
#include <libtoki/layertokenizer.h>
#include <cstdlib>
#include <iostream>
#include <boost/algorithm/string.hpp>

#ifndef LIBTOKI_VERSION
#define LIBTOKI_VERSION "?"
#endif

extern "C"
int LIBTOKI_entry_()
{
	std::cout << "This is libtoki-" LIBTOKI_VERSION ", a configurable tokenization library.\n";
	std::cout << "Default config file path: " LIBTOKI_DATA_DIR "\n";
	Toki::init_token_layers();
	std::cout << "Available layer types: "
		<< boost::algorithm::join(Toki::TokenLayer::available_layer_types(), " ")
		<< "\n";
	exit(0);
}

#endif
#endif
