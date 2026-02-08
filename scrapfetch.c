#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_LEN 256
#define shell_read_arr(cmd, arr) shell_read(cmd, arr, sizeof(arr))

void shell_read(const char* command, char* buf, size_t buf_len){
    FILE *f = popen(command, "r");
    fgets(buf, buf_len, f);
    pclose(f);
    buf[strcspn(buf, "\n")] = 0;
}
int main(){
    char user[BUF_LEN],
        dist[BUF_LEN],
        kernel[BUF_LEN],
        hn[BUF_LEN],
        de[BUF_LEN],
        scrp[BUF_LEN];

    printf("scrapfetch\n");

    shell_read_arr("whoami", user);
    shell_read_arr("uname -n", hn);
    shell_read_arr("grep '^NAME=' /etc/os-release | cut -d'=' -f2 | tr -d '\"'", dist);
    shell_read_arr("uname -r", kernel);
    shell_read_arr("echo $XDG_CURRENT_DESKTOP", de);
    shell_read_arr("type scrap >/dev/null 2>&1 && echo 1 || echo 0", scrp);
    
    char* scrp_status = (atoi(scrp)==1) ? "installed" : "not installed";
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
        , user, hn, kernel, dist, de, scrp_status, dist
    );


}

