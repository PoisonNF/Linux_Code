#ifndef TLPI_HDR_H
#define TPLI_HDR_H  /*Prevent accidental double inclusion*/

#include <sys/types.h>  /*Type definitionos used by many programs*/
#include <stdio.h>  /*Standard I/O function*/
#include <stdlib.h> /**Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants*/

#include <unistd.h> /*Prototypes for many system calls*/
#include <errno.h>  /*Declares errno and defines error constants*/
#include <string.h> /*Commonly used string-handing functions*/

#include "get_num.h"    /*Declares our functions for handing numeric arguments (getInt(), getLong())*/

#include "error_functions.h"    /*Declars our error-handing functions*/

// typedef enum {
//     FALSE,
//     TRUE
// }Boolean;

#define min(m, n) ((m) < (n) ? (m) : (n))
#define max(m, n) ((m) > (n) ? (m) : (n))
#endif // !TLPI_HDR_H