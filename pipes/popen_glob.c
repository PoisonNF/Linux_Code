/* Code44-5 P741 */
/* ./popen_glob
    popen_glob*
    x*
 */

#define _GNU_SOURCE
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include "../procexec/print_wait_status.h"
#include "../lib/tlpi_hdr.h"

#define POPEN_FMT "/bin/ls -d %s 2> /dev/null"
#define PAT_SIZE 50
#define PCMD_BUF_SIZE (sizeof(POPEN_FMT) + PAT_SIZE)

int main(int argc,char *argv[])
{
    char pat[PAT_SIZE]; /* Pattern for globbing */
    char popenCmd[PCMD_BUF_SIZE];
    FILE *fp;
    bool badPattern;    /* Invalid characters in 'pat'? */
    int len,status,fileCnt,j;
    char pathname[PATH_MAX];

    for(;;)
    {
        printf("pattern:");
        fflush(stdout);
        if(fgets(pat,PAT_SIZE,stdin) == NULL)
            break;  /* EOF */

        len = strlen(pat);
        if(len <= 1)
            continue;
        
        if(pat[len -1] == '\n') /* Strip trailing newline */
            pat[len - 1] = '\0';
        
        for(j = 0,badPattern = false;j < len && !badPattern;j++)
            if(!isalnum((unsigned char)pat[j])&&
                    strchr("_*?[^-].",pat[j]) == NULL)
                badPattern = true;
        
        if(badPattern)  /* Invalid characters */
        {
            printf("Bad pattern character: %c\n",pat[j - 1]);
            continue;
        }

        snprintf(popenCmd,PCMD_BUF_SIZE,POPEN_FMT,pat);
        popenCmd[PCMD_BUF_SIZE - 1] = '\0';

        fp = popen(popenCmd,"r");
        if(fp == NULL)
        {
            printf("popen() failed\n");
            continue;
        }

        /* Read resulting list of pathnames until EOF */
        fileCnt = 0;
        while(fgets(pathname,PATH_MAX,fp) != NULL)
        {
            printf("%s",pathname);
            fileCnt++;
        }

        /* Close pipe,fetch and display termination status */
        status = pclose(fp);
        printf("    %d matching file%s\n",fileCnt,(fileCnt != 1)?"s":"");
        printf("    pclose() status == %#x\n",(unsigned int) status);
        if(status != -1)
            printWaitStatus("\t",status);
    }
    exit(EXIT_SUCCESS);
}