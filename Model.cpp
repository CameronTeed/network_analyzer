#include "Model.h"

Model::Model()
{
    //ctor
}

Model::~Model()
{
    //dtor
}

void Model::processPacket(unsigned char *buffer, int size) {
    // Your packet processing logic goes here
    // This function can analyze and print information about the packet
    // For simplicity, this example just prints the first few bytes of the packet

    
}

void Model::print_ethernet_header(unsigned char *buffer, int size) {
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

void Model::print_ip_header(unsigned char *buffer, int size) {
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

void Model::printProtocol(int prot){

    switch(prot) {
    case 0: cout << "	HOPOPT	IPv6 Hop-by-Hop Option	Y	[RFC8200] " << endl; break;
    case 1: cout << "	ICMP	Internet Control Message		[RFC792] " << endl; break;
    case 2: cout << "	IGMP	Internet Group Management		[RFC1112] " << endl; break;
    case 3: cout << "	GGP	Gateway-to-Gateway		[RFC823] " << endl; break;
    case 4: cout << "	IPv4	IPv4 encapsulation		[RFC2003] " << endl; break;
    case 5: cout << "	ST	Stream		[RFC1190][RFC1819] " << endl; break;
    case 6: cout << "	TCP	Transmission Control		[RFC9293] " << endl; break;
    case 7: cout << "	CBT	CBT		[Tony_Ballardie] " << endl; break;
    case 8: cout << "	EGP	Exterior Gateway Protocol		[RFC888][David_Mills] " << endl; break;
    case 9: cout << "	IGP	any private interior gateway (used by Cisco for their IGRP)		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 10: cout << " 	BBN-RCC-MON	BBN RCC Monitoring		[Steve_Chipman] " << endl; break;
    case 11: cout << " 	NVP-II	Network Voice Protocol		[RFC741][Steve_Casner] " << endl; break;
    case 12: cout << " 	PUP	PUP		[Boggs, D., J. Shoch, E. Taft, and R. Metcalfe, 'PUP: An Internetwork Architecture', XEROX Palo Alto Research Center, CSL-79-10, July 1979; also in IEEE Transactions on Communication, Volume COM-28, Number 4, April 1980.][[XEROX]] " << endl; break;
    case 13: cout << " 	ARGUS (deprecated)	ARGUS		[Robert_W_Scheifler] " << endl; break;
    case 14: cout << " 	EMCON	EMCON		[Bich_Nguyen] " << endl; break;
    case 15: cout << " 	XNET	Cross Net Debugger		[Haverty, J., 'XNET Formats for Internet Protocol Version 4', IEN 158, October 1980.][Jack_Haverty] " << endl; break;
    case 16: cout << " 	CHAOS	Chaos		[J_Noel_Chiappa] " << endl; break;
    case 17: cout << " 	UDP	User Datagram		[RFC768][Jon_Postel] " << endl; break;
    case 18: cout << " 	MUX	Multiplexing		[Cohen, D. and J. Postel, 'Multiplexing Protocol', IEN 90, USC/Information Sciences Institute, May 1979.][Jon_Postel] " << endl; break;
    case 19: cout << " 	DCN-MEAS	DCN Measurement Subsystems		[David_Mills] " << endl; break;
    case 20: cout << " 	HMP	Host Monitoring		[RFC869][Bob_Hinden] " << endl; break;
    case 21: cout << " 	PRM	Packet Radio Measurement		[Zaw_Sing_Su] " << endl; break;
    case 22: cout << " 	XNS-IDP	XEROX NS IDP		['The Ethernet, A Local Area Network: Data Link Layer and Physical Layer Specification', AA-K759B-TK, Digital Equipment Corporation, Maynard, MA. Also as: 'The Ethernet - A Local Area Network', Version 1.0, Digital Equipment Corporation, Intel Corporation, Xerox Corporation, September 1980. And: 'The Ethernet, A Local Area Network: Data Link Layer and Physical Layer Specifications', Digital, Intel and Xerox, November 1982. And: XEROX, 'The Ethernet, A Local Area Network: Data Link Layer and Physical Layer Specification', X3T51/80-50, Xerox Corporation, Stamford, CT., October 1980.][[XEROX]] " << endl; break;
    case 23: cout << " 	TRUNK-1	Trunk-1		[Barry_Boehm] " << endl; break;
    case 24: cout << " 	TRUNK-2	Trunk-2		[Barry_Boehm] " << endl; break;
    case 25: cout << " 	LEAF-1	Leaf-1		[Barry_Boehm] " << endl; break;
    case 26: cout << " 	LEAF-2	Leaf-2		[Barry_Boehm] " << endl; break;
    case 27: cout << " 	RDP	Reliable Data Protocol		[RFC908][Bob_Hinden] " << endl; break;
    case 28: cout << " 	IRTP	Internet Reliable Transaction		[RFC938][Trudy_Miller] " << endl; break;
    case 29: cout << " 	ISO-TP4	ISO Transport Protocol Class 4		[RFC905][Robert_Cole] " << endl; break;
    case 30: cout << " 	NETBLT	Bulk Data Transfer Protocol		[RFC969][David_Clark] " << endl; break;
    case 31: cout << " 	MFE-NSP	MFE Network Services Protocol		[Shuttleworth, B., 'A Documentary of MFENet, a National Computer Network', UCRL-52317, Lawrence Livermore Labs, Livermore, California, June 1977.][Barry_Howard] " << endl; break;
    case 32: cout << " 	MERIT-INP	MERIT Internodal Protocol		[Hans_Werner_Braun] " << endl; break;
    case 33: cout << " 	DCCP	Datagram Congestion Control Protocol		[RFC4340] " << endl; break;
    case 34: cout << " 	3PC	Third Party Connect Protocol		[Stuart_A_Friedberg] " << endl; break;
    case 35: cout << " 	IDPR	Inter-Domain Policy Routing Protocol		[Martha_Steenstrup] " << endl; break;
    case 36: cout << " 	XTP	XTP		[Greg_Chesson] " << endl; break;
    case 37: cout << " 	DDP	Datagram Delivery Protocol		[Wesley_Craig] " << endl; break;
    case 38: cout << " 	IDPR-CMTP	IDPR Control Message Transport Proto		[Martha_Steenstrup] " << endl; break;
    case 39: cout << " 	TP++	TP++ Transport Protocol		[Dirk_Fromhein] " << endl; break;
    case 40: cout << " 	IL	IL Transport Protocol		[Dave_Presotto] " << endl; break;
    case 41: cout << " 	IPv6	IPv6 encapsulation		[RFC2473] " << endl; break;
    case 42: cout << " 	SDRP	Source Demand Routing Protocol		[Deborah_Estrin] " << endl; break;
    case 43: cout << " 	IPv6-Route	Routing Header for IPv6	Y	[Steve_Deering] " << endl; break;
    case 44: cout << " 	IPv6-Frag	Fragment Header for IPv6	Y	[Steve_Deering] " << endl; break;
    case 45: cout << " 	IDRP	Inter-Domain Routing Protocol		[Sue_Hares] " << endl; break;
    case 46: cout << " 	RSVP	Reservation Protocol		[RFC2205][RFC3209][Bob_Braden] " << endl; break;
    case 47: cout << " 	GRE	Generic Routing Encapsulation		[RFC2784][Tony_Li] " << endl; break;
    case 48: cout << " 	DSR	Dynamic Source Routing Protocol		[RFC4728] " << endl; break;
    case 49: cout << " 	BNA	BNA		[Gary Salamon] " << endl; break;
    case 50: cout << " 	ESP	Encap Security Payload	Y	[RFC4303] " << endl; break;
    case 51: cout << " 	AH	Authentication Header	Y	[RFC4302] " << endl; break;
    case 52: cout << " 	I-NLSP	Integrated Net Layer Security TUBA		[K_Robert_Glenn] " << endl; break;
    case 53: cout << " 	SWIPE (deprecated)	IP with Encryption		[John_Ioannidis] " << endl; break;
    case 54: cout << " 	NARP	NBMA Address Resolution Protocol		[RFC1735] " << endl; break;
    case 55: cout << " 	Min-IPv4	Minimal IPv4 Encapsulation		[RFC2004][Charlie_Perkins] " << endl; break;
    case 56: cout << " 	TLSP	Transport Layer Security Protocol using Kryptonet key management		[Christer_Oberg] " << endl; break;
    case 57: cout << " 	SKIP	SKIP		[Tom_Markson] " << endl; break;
    case 58: cout << " 	IPv6-ICMP	ICMP for IPv6		[RFC8200] " << endl; break;
    case 59: cout << " 	IPv6-NoNxt	No Next Header for IPv6		[RFC8200] " << endl; break;
    case 60: cout << " 	IPv6-Opts	Destination Options for IPv6	Y	[RFC8200] " << endl; break;
    case 61: cout << " 		any host internal protocol		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 62: cout << " 	CFTP	CFTP		[Forsdick, H., 'CFTP', Network Message, Bolt Beranek and Newman, January 1982.][Harry_Forsdick] " << endl; break;
    case 63: cout << " 		any local network		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 64: cout << " 	SAT-EXPAK	SATNET and Backroom EXPAK		[Steven_Blumenthal] " << endl; break;
    case 65: cout << " 	KRYPTOLAN	Kryptolan		[Paul Liu] " << endl; break;
    case 66: cout << " 	RVD	MIT Remote Virtual Disk Protocol		[Michael_Greenwald] " << endl; break;
    case 67: cout << " 	IPPC	Internet Pluribus Packet Core		[Steven_Blumenthal] " << endl; break;
    case 68: cout << " 		any distributed file system		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 69: cout << " 	SAT-MON	SATNET Monitoring		[Steven_Blumenthal] " << endl; break;
    case 70: cout << " 	VISA	VISA Protocol		[Gene_Tsudik] " << endl; break;
    case 71: cout << " 	IPCV	Internet Packet Core Utility		[Steven_Blumenthal] " << endl; break;
    case 72: cout << " 	CPNX	Computer Protocol Network Executive		[David Mittnacht] " << endl; break;
    case 73: cout << " 	CPHB	Computer Protocol Heart Beat		[David Mittnacht] " << endl; break;
    case 74: cout << " 	WSN	Wang Span Network		[Victor Dafoulas] " << endl; break;
    case 75: cout << " 	PVP	Packet Video Protocol		[Steve_Casner] " << endl; break;
    case 76: cout << " 	BR-SAT-MON	Backroom SATNET Monitoring		[Steven_Blumenthal] " << endl; break;
    case 77: cout << " 	SUN-ND	SUN ND PROTOCOL-Temporary		[William_Melohn] " << endl; break;
    case 78: cout << " 	WB-MON	WIDEBAND Monitoring		[Steven_Blumenthal] " << endl; break;
    case 79: cout << " 	WB-EXPAK	WIDEBAND EXPAK		[Steven_Blumenthal] " << endl; break;
    case 80: cout << " 	ISO-IP	ISO Internet Protocol		[Marshall_T_Rose] " << endl; break;
    case 81: cout << " 	VMTP	VMTP		[Dave_Cheriton] " << endl; break;
    case 82: cout << " 	SECURE-VMTP	SECURE-VMTP		[Dave_Cheriton] " << endl; break;
    case 83: cout << " 	VINES	VINES		[Brian Horn] " << endl; break;
    case 84: cout << " 	IPTM	Internet Protocol Traffic Manager		[Jim_Stevens][1] " << endl; break;
    case 85: cout << " 	NSFNET-IGP	NSFNET-IGP		[Hans_Werner_Braun] " << endl; break;
    case 86: cout << " 	DGP	Dissimilar Gateway Protocol		[M/A-COM Government Systems, 'Dissimilar Gateway Protocol Specification, Draft Version', Contract no. CS901145, November 16, 1987.][Mike_Little] " << endl; break;
    case 87: cout << " 	TCF	TCF		[Guillermo_A_Loyola] " << endl; break;
    case 88: cout << " 	EIGRP	EIGRP		[RFC7868] " << endl; break;
    case 89: cout << " 	OSPFIGP	OSPFIGP		[RFC1583][RFC2328][RFC5340][John_Moy] " << endl; break;
    case 90: cout << " 	Sprite-RPC	Sprite RPC Protocol		[Welch, B., 'The Sprite Remote Procedure Call System', Technical Report, UCB/Computer Science Dept., 86/302, University of California at Berkeley, June 1986.][Bruce Willins] " << endl; break;
    case 91: cout << " 	LARP	Locus Address Resolution Protocol		[Brian Horn] " << endl; break;
    case 92: cout << " 	MTP	Multicast Transport Protocol		[Susie_Armstrong] " << endl; break;
    case 93: cout << " 	AX.25	AX.25 Frames		[Brian_Kantor] " << endl; break;
    case 94: cout << " 	IPIP	IP-within-IP Encapsulation Protocol		[John_Ioannidis] " << endl; break;
    case 95: cout << " 	MICP (deprecated)	Mobile Internetworking Control Pro.		[John_Ioannidis] " << endl; break;
    case 96: cout << " 	SCC-SP	Semaphore Communications Sec. Pro.		[Howard_Hart] " << endl; break;
    case 97: cout << " 	ETHERIP	Ethernet-within-IP Encapsulation		[RFC3378] " << endl; break;
    case 98: cout << " 	ENCAP	Encapsulation Header		[RFC1241][Robert_Woodburn] " << endl; break;
    case 99: cout << " 		any private encryption scheme		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 100: cout << " 	GMTP	GMTP		[[RXB5]] " << endl; break;
    case 101: cout << " 	IFMP	Ipsilon Flow Management Protocol		[Bob_Hinden][November 1995, 1997.] " << endl; break;
    case 102: cout << " 	PNNI	PNNI over IP		[Ross_Callon] " << endl; break;
    case 103: cout << " 	PIM	Protocol Independent Multicast		[RFC7761][Dino_Farinacci] " << endl; break;
    case 104: cout << " 	ARIS	ARIS		[Nancy_Feldman] " << endl; break;
    case 105: cout << " 	SCPS	SCPS		[Robert_Durst] " << endl; break;
    case 106: cout << " 	QNX	QNX		[Michael_Hunter] " << endl; break;
    case 107: cout << " 	A/N	Active Networks		[Bob_Braden] " << endl; break;
    case 108: cout << " 	IPComp	IP Payload Compression Protocol		[RFC2393] " << endl; break;
    case 109: cout << " 	SNP	Sitara Networks Protocol		[Manickam_R_Sridhar] " << endl; break;
    case 110: cout << " 	Compaq-Peer	Compaq Peer Protocol		[Victor_Volpe] " << endl; break;
    case 111: cout << " 	IPX-in-IP	IPX in IP		[CJ_Lee] " << endl; break;
    case 112: cout << " 	VRRP	Virtual Router Redundancy Protocol		[RFC5798] " << endl; break;
    case 113: cout << " 	PGM	PGM Reliable Transport Protocol		[Tony_Speakman] " << endl; break;
    case 114: cout << " 		any 0-hop protocol		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 115: cout << " 	L2TP	Layer Two Tunneling Protocol		[RFC3931][Bernard_Aboba] " << endl; break;
    case 116: cout << " 	DDX	D-II Data Exchange (DDX)		[John_Worley] " << endl; break;
    case 117: cout << " 	IATP	Interactive Agent Transfer Protocol		[John_Murphy] " << endl; break;
    case 118: cout << " 	STP	Schedule Transfer Protocol		[Jean_Michel_Pittet] " << endl; break;
    case 119: cout << " 	SRP	SpectraLink Radio Protocol		[Mark_Hamilton] " << endl; break;
    case 120: cout << " 	UTI	UTI		[Peter_Lothberg] " << endl; break;
    case 121: cout << " 	SMP	Simple Message Protocol		[Leif_Ekblad] " << endl; break;
    case 122: cout << " 	SM (deprecated)	Simple Multicast Protocol		[Jon_Crowcroft][draft-perlman-simple-multicast] " << endl; break;
    case 123: cout << " 	PTP	Performance Transparency Protocol		[Michael_Welzl] " << endl; break;
    case 124: cout << " 	ISIS over IPv4			[Tony_Przygienda] " << endl; break;
    case 125: cout << " 	FIRE			[Criag_Partridge] " << endl; break;
    case 126: cout << " 	CRTP	Combat Radio Transport Protocol		[Robert_Sautter] " << endl; break;
    case 127: cout << " 	CRUDP	Combat Radio User Datagram		[Robert_Sautter] " << endl; break;
    case 128: cout << " 	SSCOPMCE			[Kurt_Waber] " << endl; break;
    case 129: cout << " 	IPLT			[[Hollbach]] " << endl; break;
    case 130: cout << " 	SPS	Secure Packet Shield		[Bill_McIntosh] " << endl; break;
    case 131: cout << " 	PIPE	Private IP Encapsulation within IP		[Bernhard_Petri] " << endl; break;
    case 132: cout << " 	SCTP	Stream Control Transmission Protocol		[Randall_R_Stewart] " << endl; break;
    case 133: cout << " 	FC	Fibre Channel		[Murali_Rajagopal][RFC6172] " << endl; break;
    case 134: cout << " 	RSVP-E2E-IGNORE			[RFC3175] " << endl; break;
    case 135: cout << " 	Mobility Header		Y	[RFC6275] " << endl; break;
    case 136: cout << " 	UDPLite			[RFC3828] " << endl; break;
    case 137: cout << " 	MPLS-in-IP			[RFC4023] " << endl; break;
    case 138: cout << " 	manet	MANET Protocols		[RFC5498] " << endl; break;
    case 139: cout << " 	HIP	Host Identity Protocol	Y	[RFC7401] " << endl; break;
    case 140: cout << " 	Shim6	Shim6 Protocol	Y	[RFC5533] " << endl; break;
    case 141: cout << " 	WESP	Wrapped Encapsulating Security Payload		[RFC5840] " << endl; break;
    case 142: cout << " 	ROHC	Robust Header Compression		[RFC5858] " << endl; break;
    case 143: cout << " 	Ethernet	Ethernet		[RFC8986] " << endl; break;
    case 144: cout << " 	AGGFRAG	AGGFRAG encapsulation payload for ESP		[RFC9347] " << endl; break;
    case 145: cout << " 	NSH	Network Service Header	N	[RFC9491] " << endl; break;
    case 146: cout << "		Unassigned		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 253: cout << " 		Use for experimentation and testing	Y	[RFC3692] " << endl; break;
    case 254: cout << " 		Use for experimentation and testing	Y	[RFC3692] " << endl; break;
    case 255: cout << " 	Reserved	 "  << endl; break;
    default: 

        if (prot >= 146 || prot <= 252) {
            cout << "Unassigned		[Internet_Assigned_Numbers_Authority]"  << endl; 
            break;
        }

        cout << " 	Unknown	 "  << endl; break;
    }
}

void Model::print_udp_header(unsigned char *buffer, int size) {
    // getting actual size of IP header

    // getting pointer to udp header
    struct udphdr *udp = (struct udphdr *)(buffer + size + sizeof(struct ethhdr));
    cout << "\t|-Source Port : " << ntohs(udp->source) << endl;
    cout << "\t|-Destination Port : " << ntohs(udp->dest) << endl;
    cout << "\t|-UDP Length : " << ntohs(udp->len) << endl;
    cout << "\t|-UDP Checksum : " << ntohs(udp->check) << endl;  //  ntohs() function converts the unsigned short integer netshort from network byte order to host byte order.
}

void Model::print_tcp_header(unsigned char *buffer, int size) {
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

void Model::protoclSwitch(unsigned char *buffer) {
    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    unsigned short iphdrlen;
    iphdrlen = ip->ihl * 4;

    int protocol = ip->protocol;
    cout << "Protocol: " << protocol << endl;   
    switch(protocol){
        case 6:
            print_udp_header(buffer, iphdrlen);
            break;
        case 17:
            print_tcp_header(buffer, iphdrlen);
            break;
        default:
            printProtocol(protocol);
    }
}

