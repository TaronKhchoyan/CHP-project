/*
    UDP Client routine
*/

#include "UDPSocket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFLEN 1024

int main(int argc, char* argv[])
{
    struct sockaddr_in si_other;
    int slen = sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
    
    unsigned short srv_port = 8888; // Server port
    char srv_ip_addr[] = "127.0.0.1"; // Server IP

    // Create socket
    UDPSocket client_sock;

    // Setup address structure
    memset((char*)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(srv_port);
    si_other.sin_addr.s_addr = inet_addr(srv_ip_addr);

    while (1)
    {
        printf("Մուտքագրեք հաղորդագրություն (կամ 'exit'՝ դուրս գալու համար): ");
        fgets(message, BUFLEN, stdin);

        if (strncmp(message, "exit", 4) == 0) {
            printf("Հաճախորդի ծրագիրը փակվեց.\n");
            break;
        }

        // Send the message
        client_sock.sendTo(message, strlen(message), si_other);

        // Receive a reply from the server
        memset(buf, 0, BUFLEN);
        client_sock.recvFrom(buf, BUFLEN, si_other);
        printf("Սերվերի պատասխան՝ %s\n", buf);
    }

    return 0;
}
