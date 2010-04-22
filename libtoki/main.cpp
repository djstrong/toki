/* Code to display version info and greeting message when the .so is run */
#ifdef __GNUG__
#ifndef _WIN32
#ifdef __LP64__
extern "C" const char my_interp[] __attribute__((section(".interp"))) = "/lib/ld-linux-x86-64.so.2";
#else
extern "C" const char my_interp[] __attribute__((section(".interp"))) = "/lib/ld-linux.so.2";
#endif

#include <cstdlib>
#include <iostream>

#ifndef LIBTOKI_VERSION
#define LIBTOKI_VERSION "?"
#endif

extern "C" int LIBTOKI_entry_()
{
	std::cout << "This is libtoki-" LIBTOKI_VERSION "\n";
	exit(0);
}

#endif
#endif
