/* Code10-4 P162 */
/* ./show_time
    TZ=":Pacific/Auckland ./show_time"
*/

#include <time.h>
#include <locale.h>
#include "../lib/tlpi_hdr.h"

#define BUF_SIZE 200

int main(int argc,char *argv[])
{
    time_t t;
    struct tm *loc;
    char buf[BUF_SIZE];

    if(setlocale(LC_ALL,"") == NULL)
        printf("setlocale");
    
    t = time(NULL);
    printf("ctime() of time() value is:%s",ctime(&t));

    loc = localtime(&t);
    if(loc == NULL)
        printf("localtime");

    printf("asctime() of loacl time is: %s",asctime(loc));

    if(strftime(buf,BUF_SIZE,"%A,%d %B %Y,%H:%M:%S %Z",loc) == 0)
        printf("strftime returned 0");
    
    printf("strftime() of local time is:%s\n",buf);

    exit(EXIT_SUCCESS);

}