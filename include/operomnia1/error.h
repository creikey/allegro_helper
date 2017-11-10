#ifndef H_ERROR
#define H_ERROR

#define ERR_NULL_PTR 0

void raise_error( int err_code, const char * function );

void check_if_null ( void * in_ptr, const char * in_func );

#endif
