#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/sysinfo.h>

int main(){
    char struser[256];
    char strdist[256];
    char strkernel[256];
    char strhn[256];
    char *strscrp;
    char strde[256];

    printf("scrapfetch\n");

    FILE *user = popen("whoami", "r");
    fgets(struser, sizeof(struser), user);
    pclose(user);
    struser[strcspn(struser, "\n")] = 0;

    FILE *hn = popen("hostname", "r");
    fgets(strhn, sizeof(strhn), hn);
    pclose(hn);
    strhn[strcspn(strhn, "\n")] = 0;

    FILE *dist = popen("grep '^NAME=' /etc/os-release | cut -d'=' -f2 | tr -d '\"'", "r");
    fgets(strdist, sizeof(strdist), dist);
    pclose(dist);
    strdist[strcspn(strdist, "\n")] = 0;

    FILE *kernel = popen("uname -r", "r");
    fgets(strkernel, sizeof(strkernel), kernel);
    pclose(kernel);
    strkernel[strcspn(strkernel, "\n")] = 0;

    FILE *scrp = popen("which scrap 2>/dev/null", "r");
    if(scrp == NULL){
        strscrp = "not installed";
    }else{
        strscrp = "installed";
    }

    FILE *de = popen("echo $XDG_CURRENT_DESKTOP", "r");
    fgets(strde, sizeof(strde), de);
    pclose(de);
    strde[strcspn(strde, "\n")] = 0;
    printf(
        "\033[32m@@@@@@@@@::.....:@@@\n"
        "@: :..... ......:@@@   %s@%s\n"
        ":  ....:-===++++@@@@   -------------\n"
        ":. .=++++++++===::@@   Kernel - %s\n"
        "@.  :+===-..... ..:@   OS - %s\n"
        "@ .. .....:-==+:  .@   DE - %s\n"
        "@@..====+++++++=. .:   Scrap is %s on your %s\n!"
        "@@@@++=+==--:.... .:\n"
        "@@@::..... ......:@@\n"
        "@@@:... ..:@@@@@@@@@\n\033[0m"
        , struser, strhn, strkernel, strdist, strde, strscrp, strdist
    );


}

