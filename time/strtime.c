/* Code10-3 P161 */
/* ./strtime "9:39:46pm 1 Feb 2011" "%I:%M:%S%p %d %b %y" */
/* ./strtime "9:39:46pm 1 Feb 2011" "%I:%M:%S%p %d %b %y" "%F %T" */
#define _XOPEN_SOURCE
#include <time.h>
#include <locale.h>
#include "../lib/tlpi_hdr.h"

#define SBUF_SIZE 1000

int main(int argc,char *argv[])
{
    struct tm tm;
    char sbuf[SBUF_SIZE];
    char *ofmt;

    if(argc < 3 || strcmp(argv[1],"--help") == 0)
        printf("%s input-date-time in-format [out-format]",argv[0]);

    if(setlocale(LC_ALL,"") == NULL)
        printf("setlocale");    /* Use locale settings in conversions */

    memset(&tm,0,sizeof(struct tm));
    if(strptime(argv[1],argv[2],&tm) == NULL)
        printf("strptime");
    
    tm.tm_isdst = -1;       /* Not set by strptime();tells mktime() 
                                to determine if DST is in effect*/
    printf("calendar time (seconds since Epoch): %ld\n",(long)mktime(&tm));

    /* if agrc > 3 use argv[3] ,else use default */
    ofmt = (argc > 3) ? argv[3] : "%H:%M:%S %A, %d %B %Y %Z";
    if(strftime(sbuf,SBUF_SIZE,ofmt,&tm) == 0)
        printf("strftime returned 0");
    printf("strftime() yields: %s\n",sbuf);
    
    exit(EXIT_SUCCESS);
}