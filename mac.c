#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>

main()
{
    int s;
    struct ifdevea ifd;

    s = socket(2, 2, 0);
    if (s < 0) {
        perror("socket");
        exit(1);
    }

    strcpy(ifd.ifr_name, "qe0");

    if (ioctl(s, SIOCRPHYSADDR, &ifd) < 0) {
        perror("ioctl");
        close(s);
        exit(1);
    }

    printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        ifd.current_pa[0], ifd.current_pa[1], ifd.current_pa[2],
        ifd.current_pa[3], ifd.current_pa[4], ifd.current_pa[5]);

    close(s);
    exit(0);
}