/* Code18-2 P295 */
/* mkdir sub
    touch sub/a sub/b
    ./list_files sub
*/

#include <dirent.h>
#include "../lib/tlpi_hdr.h"

static void listFiles(const char *dirpath)
{
    DIR *dirp;
    struct dirent *dp;
    Boolean isCurrent;  /* True if 'dirpath' is "." */

    isCurrent = strcmp(dirpath,".") == 0;

    dirp = opendir(dirpath);
    if(dirp == NULL)
    {
        printf("opendir failed on '%s'\n",dirpath);
        return;
    }

    /* For each entry in this directory,print directory +filename */

    for(;;)
    {
        errno = 0;
        dp = readdir(dirp);
        if(dp == NULL)
            break;
        
        if(strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0)
            continue;   /* Skip . and .. */
        
        if(!isCurrent)
            printf("%s/",dirpath);
        printf("%s\n",dp->d_name); 
    }
    
    if(errno != 0)
        printf("readdir");
    
    if(closedir(dirp) == -1)
        printf("closedir");
}

int main(int argc,char *argv[])
{
    if(argc > 1 && strcmp(argv[1],"--help") == 0)
        printf("%s [dir...]\n",argv[0]);
    
    if(argc == 1)
        listFiles(".");
    else
        for(argv++;*argv;argv++);
        listFiles(*argv);

    exit(EXIT_SUCCESS);
}

