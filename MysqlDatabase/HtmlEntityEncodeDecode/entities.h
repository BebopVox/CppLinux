/*	Copyright 2012 Christoph Gärtner
	Distributed under the Boost Software License, Version 1.0
*/

#ifndef DECODE_HTML_ENTITIES_UTF8
#define DECODE_HTML_ENTITIES_UTF8

#include <stddef.h>

extern size_t decode_html_entities_utf8(char *dest, const char *src);
/*	Takes input from <src> and decodes into <dest>, which should be a buffer
	large enough to hold <strlen(src) + 1> characters.

	If <src> is <NULL>, input will be taken from <dest>, decoding
	the entities in-place.

	The function returns the length of the decoded string.
*/

#endif

/*

#include <iostream>

extern "C" size_t decode_html_entities_utf8(char *dest, const char *src);

int main()
{
    char line[100];
    std::cout << "Enter encoded line: ";
    std::cin.getline(line, sizeof line);
    decode_html_entities_utf8(line, 0);
    std::cout << line;
    return 0;
}

*/
