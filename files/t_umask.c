/* Code15-5 P250 */
/* ./t_umask */

#include <sys/stat.h>
#include <fcntl.h>
#include "file_perms.h"
#include "../lib/tlpi_hdr.h"

#define MYFILE "myfile"
#define MYDIR  "mydir"
#define FILE_PERMS  (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define DIR_PERMS   (S_IRWXU | S_IRWXG | S_IRWXO)
#define UMASK_SETTING   (S_IWGRP | S_IXGRP | S_IWOTH | S_IXOTH)

int main(int argc,char *argv[])
{
    int fd;
    struct stat sb;
    mode_t u;

    umask(UMASK_SETTING);

    fd = open(MYFILE,O_RDWR | O_CREAT | O_EXCL,FILE_PERMS);
    if(fd == -1)
        printf("open-%s",MYFILE);
    if(mkdir(MYDIR,DIR_PERMS) == -1)
        printf("mkdir-%s",MYDIR);

    u = umask(0);           /* Retrieves (and clears) umask value */

    if(stat(MYFILE,&sb) == -1)
        printf("stat-%s",MYFILE);
    
    printf("Requested file perms: %s\n",filePermStr(FILE_PERMS,0));
    printf("Process umask:        %s\n",filePermStr(u,0));
    printf("Actual file perms:    %s\n\n",filePermStr(sb.st_mode,0));

    if(stat(MYDIR,&sb) == -1)
        printf("stat-%s",MYDIR);

    printf("Requested dir perms:  %s\n",filePermStr(DIR_PERMS,0));
    printf("Process umask:        %s\n",filePermStr(u,0));
    printf("Actual dir perms:     %s\n\n",filePermStr(sb.st_mode,0));
    
    if(unlink(MYFILE) == -1)
        printf("unlink-%s",MYFILE);
    if(rmdir(MYDIR) == -1)
        printf("rmdir-%s",MYDIR);
    
    exit(EXIT_SUCCESS);
}