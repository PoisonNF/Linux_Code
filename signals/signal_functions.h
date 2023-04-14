#ifndef __SIGNAL_FUNCTIONS_H
#define __SIGNAL_FUNCTIONS_H

#include "../lib/tlpi_hdr.h"

void PrintSigset(FILE *of,const char *prefix,const sigset_t *sigset);

int PrintSigMask(FILE *of,const char *msg);

int PrintPendingSigs(FILE *of,const char *msg);


#endif // !__SIGNAL_FUNCTIONS_H