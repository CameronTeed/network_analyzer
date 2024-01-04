#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <iomanip>

using namespace std;

// sources: https://www.opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/
//  https://beej.us/guide/bgnet/html/split/
//  https://www.binarytides.com/packet-sniffer-code-c-linux/

void processPacket(unsigned char *buffer, int size) {
    // Your packet processing logic goes here
    // This function can analyze and print information about the packet
    // For simplicity, this example just prints the first few bytes of the packet

    for (int i = 0; i < size; ++i) {
        printf("%02x ", buffer[i]);
        if ((i + 1) % 16 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

char *get_ip_str(const struct sockaddr *sa, char *s, size_t maxlen)
{
    switch(sa->sa_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr),
                    s, maxlen);
            break;

        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr),
                    s, maxlen);
            break;

        default:
            strncpy(s, "Unknown AF", maxlen);
            return NULL;
    }

    return s;
}

// NOTE: MUST RUN AS SUDO (sudo ./main)

int main() {

    int status;
    struct addrinfo *hints;
    struct addrinfo *servinfo;

    // ipv4 socket with raw protocol
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

    if (sock < 0) {
        perror("Error creating socket");
        return 1;
    }

    while (true) {
        // 65535 is max packet size
        unsigned char buffer[65535];
        memset(buffer, 0, sizeof(buffer));

        struct sockaddr saddr;
        int saddr_len = sizeof (saddr);

        int recv_bytes = recvfrom(sock, buffer, sizeof(buffer), 0,&saddr, (socklen_t *) &saddr_len);

        if (recv_bytes < 0) {
            perror("Error receiving packet");
            return 1;
        }

        struct ethhdr *eth = (struct ethhdr *)(buffer);
        // outputting the mac address
        cout << "\nEthernet Header\n" << endl;
        cout << "\t|-Source Address : " << std::hex << std::setfill('0') 
        << std::setw(2) << (int)eth->h_source[0] << "-"
        << std::setw(2) << (int)eth->h_source[1] <<  "-"
        << std::setw(2) << (int)eth->h_source[2] <<  "-"
        << std::setw(2) << (int)eth->h_source[3] <<  "-"
        << std::setw(2) << (int)eth->h_source[4] <<  "-"
        << std::setw(2) << (int)eth->h_source[5] << endl;
        cout << "\t|-Destination Address : " << std::hex << std::setfill('0')
        << std::setw(2) << (int)eth->h_dest[0] << "-"
        << std::setw(2) << (int)eth->h_dest[1] <<  "-"
        << std::setw(2) << (int)eth->h_dest[2] <<  "-"
        << std::setw(2) << (int)eth->h_dest[3] <<  "-"
        << std::setw(2) << (int)eth->h_dest[4] <<  "-"
        << std::setw(2) << (int)eth->h_dest[5] << endl;
        cout << "\t|-Protocol : " << (unsigned short)eth->h_proto << endl;

    }
    close(sock);


    return 0;
}