#ifndef H_FILE
#define H_FILE

bool ends_with( const char *str, const char *suffix );

// Adds a slash at the end of a directory name
char * fix_directory( const char * in_str );

// Gets the index of a character, like .
int get_strchar_index( char * in_str, char to_find, bool backwards );

int char_to_numb( char in_char );

#endif
