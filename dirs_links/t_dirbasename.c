/* Code18-5 P308 */
/* ./t_dirbasename  /home/bcl/Linux_Code/dirs_links/x */

#include <libgen.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    char *t1,*t2;
    int j;

    for(j = 1;j < argc ;j++)
    {
        t1 = strdup(argv[j]);
        if(t1 == NULL)
            printf("strdup");

        t2 = strdup(argv[j]);
        if(t2 == NULL)
            printf("strdup");
        
        printf("%s ==> %s + %s\n",
                argv[j],dirname(argv[j]),basename(argv[j]));

        free(t1);
        free(t2);
    }
    exit(EXIT_SUCCESS);
}