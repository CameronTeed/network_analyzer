#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <iomanip>
#include <netinet/udp.h>
#include <netinet/tcp.h>

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

void print_ethernet_header(unsigned char *buffer, int size) {
    struct ethhdr *eth = (struct ethhdr *)(buffer);

    cout << "\nEthernet Header\n" << endl;
    cout << "\t|-Source Address : ";
    for (int i = 0; i < 6; ++i) {
        cout << hex << setw(2) << setfill('0') << (int)eth->h_source[i];
        if (i < 5) cout << "-";
    }
    cout << endl;

    cout << "\t|-Destination Address : ";
    for (int i = 0; i < 6; ++i) {
        cout << hex << setw(2) << setfill('0') << (int)eth->h_dest[i];
        if (i < 5) cout << "-";
    }
    cout << endl;

    cout << "\t|-Protocol : " << (unsigned short)eth->h_proto << endl;
}

void print_ip_header(unsigned char *buffer, int size) {
    struct sockaddr_in source, dest;

    unsigned short iphdrlen;

    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = ip->saddr;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = ip->daddr;

    cout << "\nIP Header\n" << endl;
    cout << "\t|-Version : " << (unsigned int)ip->version << endl;
    cout << "\t|-Internet Header Length : " << (unsigned int)ip->ihl << " DWORDS or " << ((unsigned int)(ip->ihl)) * 4 << " Bytes" << endl;
    cout << "\t|-Type Of Service : " << (unsigned int)ip->tos << endl;
    cout << "\t|-Total Length : " << ntohs(ip->tot_len) << " Bytes" << endl;
    cout << "\t|-Identification : " << ntohs(ip->id) << endl;
    cout << "\t|-Time To Live : " << (unsigned int)ip->ttl << endl;
    cout << "\t|-Protocol : " << (unsigned int)ip->protocol << endl;
    cout << "\t|-Header Checksum : " << ntohs(ip->check) << endl;
    cout << "\t|-Source IP : " << inet_ntoa(source.sin_addr) << endl;
    cout << "\t|-Destination IP : " << inet_ntoa(dest.sin_addr) << endl;
}

void print_udp_header(unsigned char *buffer, int size) {
    // getting actual size of IP header

    // getting pointer to udp header
    struct udphdr *udp = (struct udphdr *)(buffer + size + sizeof(struct ethhdr));
    cout << "\t|-Source Port : " << ntohs(udp->source) << endl;
    cout << "\t|-Destination Port : " << ntohs(udp->dest) << endl;
    cout << "\t|-UDP Length : " << ntohs(udp->len) << endl;
    cout << "\t|-UDP Checksum : " << ntohs(udp->check) << endl;  //  ntohs() function converts the unsigned short integer netshort from network byte order to host byte order.
}

void print_tcp_header(unsigned char *buffer, int size) {
    // getting pointer to tcp header
    struct tcphdr *tcp = (struct tcphdr *)(buffer + size + sizeof(struct ethhdr));
    cout << "\nTCP Header\n";
    cout << "\t|-Source Port          : " << ntohs(tcp->source) << endl;
    cout << "\t|-Destination Port     : " << ntohs(tcp->dest) << endl;
    cout << "\t|-Sequence Number      : " << ntohl(tcp->seq) << endl;
    cout << "\t|-Acknowledge Number   : " << ntohl(tcp->ack_seq) << endl;
    cout << "\t|-Header Length        : " << (unsigned int)tcp->doff << " DWORDS or " << (unsigned int)tcp->doff * 4 << " BYTES" << endl;
    cout << "\t|----------Flags-----------\n";
    cout << "\t\t|-Urgent Flag          : " << (unsigned int)tcp->urg << endl;
    cout << "\t\t|-Acknowledgement Flag : " << (unsigned int)tcp->ack << endl;
    cout << "\t\t|-Push Flag            : " << (unsigned int)tcp->psh << endl;
    cout << "\t\t|-Reset Flag           : " << (unsigned int)tcp->rst << endl;
    cout << "\t\t|-Synchronise Flag     : " << (unsigned int)tcp->syn << endl;
    cout << "\t\t|-Finish Flag          : " << (unsigned int)tcp->fin << endl;
    cout << "\t|-Window size          : " << ntohs(tcp->window) << endl;
    cout << "\t|-Checksum             : " << ntohs(tcp->check) << endl;
    cout << "\t|-Urgent Pointer       : " << tcp->urg_ptr << endl;    
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

int is_tcp(unsigned char *buffer, int size) {
    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    return ip->protocol;
}

int main() {

    int status;
    struct addrinfo *hints;
    struct addrinfo *servinfo;
    struct sockaddr_in source, dest;

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
        int saddr_len = sizeof(saddr);

        int recv_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, &saddr, (socklen_t *)&saddr_len);

        if (recv_bytes < 0) {
            perror("Error receiving packet");
            return 1;
        }

        print_ethernet_header(buffer, recv_bytes);

        print_ip_header(buffer, sizeof(struct ethhdr));

        struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
        unsigned short iphdrlen;
        iphdrlen = ip->ihl * 4;

        int protocol = is_tcp(buffer, recv_bytes);

        switch(protocol){
            case 6:
                print_udp_header(buffer, iphdrlen);
                break;
            case 17:
                print_tcp_header(buffer, iphdrlen);
                break;
            default:
                cout << "Error: neither TCP nor UDP" << endl;
        }


        print_tcp_header(buffer, iphdrlen);
        print_udp_header(buffer, iphdrlen);
    }

    close(sock);

    return 0;
}