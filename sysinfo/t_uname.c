/* Code12-2 P189 */
/* ./t_uname */

#define _GUN_SOURCE
#include <sys/utsname.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    struct utsname uts;

    if(uname(&uts) == -1)
        printf("uname");
    
    printf("Node name:  %s\n",uts.nodename);
    printf("System name:%s\n",uts.sysname);
    printf("Release     %s\n",uts.release);
    printf("Version:    %s\n",uts.version);
    printf("Machine:    %s\n",uts.machine);

#ifdef _GUN_SOURCE
    printf("Domain name:%s\n",uts.__domainname);
#endif //_GUN_SOURCE
    exit(EXIT_SUCCESS);
}
