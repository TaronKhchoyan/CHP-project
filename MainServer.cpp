/*
    UDP Server routine
*/

#include "UDPServer.h"
#include <stdio.h>
#include <string.h>

#define BUFLEN 1024
#define PORT 8888

int main()
{
    struct sockaddr_in si_me, si_other;
    int slen = sizeof(si_other);
    char buf[BUFLEN];

    // Create socket
    UDPServer server_sock;

    // Setup address structure
    memset((char*)&si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind socket
    server_sock.bindSocket(si_me);

    printf("Սերվերը աշխատում է. Սպասում է հաղորդագրությունների...\n");

    while (1)
    {
        memset(buf, 0, BUFLEN);

        // Receive a message
        server_sock.recvFrom(buf, BUFLEN, si_other);
        printf("Ստացված հաղորդագրություն՝ %s\n", buf);

        // Send response back
        char response[BUFLEN];
        sprintf(response, "Հաղորդագրություն ստացվեց: %s", buf);
        server_sock.sendTo(response, strlen(response), si_other);
    }

    return 0;
}
