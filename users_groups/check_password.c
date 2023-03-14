/* Code8-2 P133 */
/*  su
    ./check_password
*/

#define _DEFAULT_SOURCE     /* Get getpass() from <unistd.h>*/
#define _XPOEN_SOURCE   /* Get crypt() from <unistd.h> */
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    char *username,*password,*encryped,*p;
    struct passwd *pwd;
    struct spwd *spwd;
    Boolean authOk;
    size_t len;
    long lnmax;
    lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    if(lnmax == -1)         /* If limit is indeterminate */
        lnmax = 256;        /* make a guess */

    username = malloc(lnmax);
    if(username == NULL)
        printf("malloc");
    
    printf("Username:");
    fflush(stdout);
    if(fgets(username,lnmax,stdin) == NULL)
        exit(EXIT_FAILURE);

    len = strlen(username);
    if(username[len - 1] == '\n')
        username[len - 1] = '\0';

    pwd = getpwnam(username);
    if(pwd == NULL)
        printf("couldn't get password record");
    
    spwd = getspnam(username);
    if(spwd == NULL)
        printf("no permission to read shadow password file");
    
    if(spwd != NULL)
        pwd->pw_passwd = spwd->sp_pwdp;

    password = getpass("Password: ");

    /* Encrypt password and erase cleartext version version immediately */

    encryped = crypt(password,pwd->pw_passwd);

    for(p = password;*p != '\0';p++)
        *p = '\0';

    if(encryped == NULL)
        printf("crypt");
    
    authOk = strcmp(encryped,pwd->pw_passwd) == 0;

    if(!authOk)
    {
        printf("Incorrect password\n");
        exit(EXIT_FAILURE);
    }
    printf("Successfully authenticated:UID=%ld\n",(long)pwd->pw_uid);

    /* Now do authenticated work */
    exit(EXIT_SUCCESS);
}