#include "Model.h"

Model::Model()
{
    testing = 0;
    //ctor
}

Model::Model(int testing): testing(testing)
{
    //ctor
}

Model::~Model()
{
    //dtor
}

void Model::processPacket(std::ofstream& out, unsigned char* buffer, int size) {
    // Your packet processing logic goes here
    // This function can analyze and print information about the packet
    // For simplicity, this example just prints the first few bytes of the packet
    // if (testing == 1) {
    //     return;
    // }
    unsigned char* data = (buffer + iphdrlen + sizeof(struct ethhdr) + sizeof(struct udphdr));
    out << "\nData\n";
    int remaining_data = size - (iphdrlen + sizeof(struct ethhdr) + sizeof(struct udphdr));
    for (int i = 0; i < remaining_data; i++) {
        if (i != 0 && i % 16 == 0)
            out << "\n";
         if (isprint(data[i])) {
            out << static_cast<char>(data[i]);
         }
    }

    out << "\n";
}

void Model::print_ethernet_header(ofstream&  out, unsigned char *buffer, int size) {
    struct ethhdr *eth = (struct ethhdr *)(buffer);

    out << "\nEthernet Header\n" << endl;
    out << "\t|-Source Address : ";
    for (int i = 0; i < 6; ++i) {
        out << hex << setw(2) << setfill('0') << (int)eth->h_source[i];
        if (i < 5) out << "-";
    }
    out << endl;

    out << "\t|-Destination Address : ";
    for (int i = 0; i < 6; ++i) {
        out << hex << setw(2) << setfill('0') << (int)eth->h_dest[i];
        if (i < 5) out << "-";
    }
    out << endl;

    out << "\t|-Protocol : " << (unsigned short)eth->h_proto << endl;
}

void Model::print_ip_header(ofstream&  out, unsigned char *buffer, int size) {
    struct sockaddr_in source, dest;

    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = ip->saddr;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = ip->daddr;
    iphdrlen =ip->ihl*4;

    out << "\nIP Header\n" << endl;
    out << "\t|-Version : " << (unsigned int)ip->version << endl;
    out << "\t|-Internet Header Length : " << (unsigned int)ip->ihl << " DWORDS or " << ((unsigned int)(ip->ihl)) * 4 << " Bytes" << endl;
    out << "\t|-Type Of Service : " << (unsigned int)ip->tos << endl;
    out << "\t|-Total Length : " << ntohs(ip->tot_len) << " Bytes" << endl;
    out << "\t|-Identification : " << ntohs(ip->id) << endl;
    out << "\t|-Time To Live : " << (unsigned int)ip->ttl << endl;
    out << "\t|-Protocol : " << (unsigned int)ip->protocol << endl;
    out << "\t|-Header Checksum : " << ntohs(ip->check) << endl;
    out << "\t|-Source IP : " << inet_ntoa(source.sin_addr) << endl;
    out << "\t|-Destination IP : " << inet_ntoa(dest.sin_addr) << endl;
}

void Model::printProtocol(ofstream&  out, int prot){

    switch(prot) {
    case 0: out << "	HOPOPT	IPv6 Hop-by-Hop Option	Y	[RFC8200] " << endl; break;
    case 1: out << "	ICMP	Internet Control Message		[RFC792] " << endl; break;
    case 2: out << "	IGMP	Internet Group Management		[RFC1112] " << endl; break;
    case 3: out << "	GGP	Gateway-to-Gateway		[RFC823] " << endl; break;
    case 4: out << "	IPv4	IPv4 encapsulation		[RFC2003] " << endl; break;
    case 5: out << "	ST	Stream		[RFC1190][RFC1819] " << endl; break;
    case 6: out << "	TCP	Transmission Control		[RFC9293] " << endl; break;
    case 7: out << "	CBT	CBT		[Tony_Ballardie] " << endl; break;
    case 8: out << "	EGP	Exterior Gateway Protocol		[RFC888][David_Mills] " << endl; break;
    case 9: out << "	IGP	any private interior gateway (used by Cisco for their IGRP)		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 10: out << " 	BBN-RCC-MON	BBN RCC Monitoring		[Steve_Chipman] " << endl; break;
    case 11: out << " 	NVP-II	Network Voice Protocol		[RFC741][Steve_Casner] " << endl; break;
    case 12: out << " 	PUP	PUP		[Boggs, D., J. Shoch, E. Taft, and R. Metcalfe, 'PUP: An Internetwork Architecture', XEROX Palo Alto Research Center, CSL-79-10, July 1979; also in IEEE Transactions on Communication, Volume COM-28, Number 4, April 1980.][[XEROX]] " << endl; break;
    case 13: out << " 	ARGUS (deprecated)	ARGUS		[Robert_W_Scheifler] " << endl; break;
    case 14: out << " 	EMCON	EMCON		[Bich_Nguyen] " << endl; break;
    case 15: out << " 	XNET	Cross Net Debugger		[Haverty, J., 'XNET Formats for Internet Protocol Version 4', IEN 158, October 1980.][Jack_Haverty] " << endl; break;
    case 16: out << " 	CHAOS	Chaos		[J_Noel_Chiappa] " << endl; break;
    case 17: out << " 	UDP	User Datagram		[RFC768][Jon_Postel] " << endl; break;
    case 18: out << " 	MUX	Multiplexing		[Cohen, D. and J. Postel, 'Multiplexing Protocol', IEN 90, USC/Information Sciences Institute, May 1979.][Jon_Postel] " << endl; break;
    case 19: out << " 	DCN-MEAS	DCN Measurement Subsystems		[David_Mills] " << endl; break;
    case 20: out << " 	HMP	Host Monitoring		[RFC869][Bob_Hinden] " << endl; break;
    case 21: out << " 	PRM	Packet Radio Measurement		[Zaw_Sing_Su] " << endl; break;
    case 22: out << " 	XNS-IDP	XEROX NS IDP		['The Ethernet, A Local Area Network: Data Link Layer and Physical Layer Specification', AA-K759B-TK, Digital Equipment Corporation, Maynard, MA. Also as: 'The Ethernet - A Local Area Network', Version 1.0, Digital Equipment Corporation, Intel Corporation, Xerox Corporation, September 1980. And: 'The Ethernet, A Local Area Network: Data Link Layer and Physical Layer Specifications', Digital, Intel and Xerox, November 1982. And: XEROX, 'The Ethernet, A Local Area Network: Data Link Layer and Physical Layer Specification', X3T51/80-50, Xerox Corporation, Stamford, CT., October 1980.][[XEROX]] " << endl; break;
    case 23: out << " 	TRUNK-1	Trunk-1		[Barry_Boehm] " << endl; break;
    case 24: out << " 	TRUNK-2	Trunk-2		[Barry_Boehm] " << endl; break;
    case 25: out << " 	LEAF-1	Leaf-1		[Barry_Boehm] " << endl; break;
    case 26: out << " 	LEAF-2	Leaf-2		[Barry_Boehm] " << endl; break;
    case 27: out << " 	RDP	Reliable Data Protocol		[RFC908][Bob_Hinden] " << endl; break;
    case 28: out << " 	IRTP	Internet Reliable Transaction		[RFC938][Trudy_Miller] " << endl; break;
    case 29: out << " 	ISO-TP4	ISO Transport Protocol Class 4		[RFC905][Robert_Cole] " << endl; break;
    case 30: out << " 	NETBLT	Bulk Data Transfer Protocol		[RFC969][David_Clark] " << endl; break;
    case 31: out << " 	MFE-NSP	MFE Network Services Protocol		[Shuttleworth, B., 'A Documentary of MFENet, a National Computer Network', UCRL-52317, Lawrence Livermore Labs, Livermore, California, June 1977.][Barry_Howard] " << endl; break;
    case 32: out << " 	MERIT-INP	MERIT Internodal Protocol		[Hans_Werner_Braun] " << endl; break;
    case 33: out << " 	DCCP	Datagram Congestion Control Protocol		[RFC4340] " << endl; break;
    case 34: out << " 	3PC	Third Party Connect Protocol		[Stuart_A_Friedberg] " << endl; break;
    case 35: out << " 	IDPR	Inter-Domain Policy Routing Protocol		[Martha_Steenstrup] " << endl; break;
    case 36: out << " 	XTP	XTP		[Greg_Chesson] " << endl; break;
    case 37: out << " 	DDP	Datagram Delivery Protocol		[Wesley_Craig] " << endl; break;
    case 38: out << " 	IDPR-CMTP	IDPR Control Message Transport Proto		[Martha_Steenstrup] " << endl; break;
    case 39: out << " 	TP++	TP++ Transport Protocol		[Dirk_Fromhein] " << endl; break;
    case 40: out << " 	IL	IL Transport Protocol		[Dave_Presotto] " << endl; break;
    case 41: out << " 	IPv6	IPv6 encapsulation		[RFC2473] " << endl; break;
    case 42: out << " 	SDRP	Source Demand Routing Protocol		[Deborah_Estrin] " << endl; break;
    case 43: out << " 	IPv6-Route	Routing Header for IPv6	Y	[Steve_Deering] " << endl; break;
    case 44: out << " 	IPv6-Frag	Fragment Header for IPv6	Y	[Steve_Deering] " << endl; break;
    case 45: out << " 	IDRP	Inter-Domain Routing Protocol		[Sue_Hares] " << endl; break;
    case 46: out << " 	RSVP	Reservation Protocol		[RFC2205][RFC3209][Bob_Braden] " << endl; break;
    case 47: out << " 	GRE	Generic Routing Encapsulation		[RFC2784][Tony_Li] " << endl; break;
    case 48: out << " 	DSR	Dynamic Source Routing Protocol		[RFC4728] " << endl; break;
    case 49: out << " 	BNA	BNA		[Gary Salamon] " << endl; break;
    case 50: out << " 	ESP	Encap Security Payload	Y	[RFC4303] " << endl; break;
    case 51: out << " 	AH	Authentication Header	Y	[RFC4302] " << endl; break;
    case 52: out << " 	I-NLSP	Integrated Net Layer Security TUBA		[K_Robert_Glenn] " << endl; break;
    case 53: out << " 	SWIPE (deprecated)	IP with Encryption		[John_Ioannidis] " << endl; break;
    case 54: out << " 	NARP	NBMA Address Resolution Protocol		[RFC1735] " << endl; break;
    case 55: out << " 	Min-IPv4	Minimal IPv4 Encapsulation		[RFC2004][Charlie_Perkins] " << endl; break;
    case 56: out << " 	TLSP	Transport Layer Security Protocol using Kryptonet key management		[Christer_Oberg] " << endl; break;
    case 57: out << " 	SKIP	SKIP		[Tom_Markson] " << endl; break;
    case 58: out << " 	IPv6-ICMP	ICMP for IPv6		[RFC8200] " << endl; break;
    case 59: out << " 	IPv6-NoNxt	No Next Header for IPv6		[RFC8200] " << endl; break;
    case 60: out << " 	IPv6-Opts	Destination Options for IPv6	Y	[RFC8200] " << endl; break;
    case 61: out << " 		any host internal protocol		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 62: out << " 	CFTP	CFTP		[Forsdick, H., 'CFTP', Network Message, Bolt Beranek and Newman, January 1982.][Harry_Forsdick] " << endl; break;
    case 63: out << " 		any local network		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 64: out << " 	SAT-EXPAK	SATNET and Backroom EXPAK		[Steven_Blumenthal] " << endl; break;
    case 65: out << " 	KRYPTOLAN	Kryptolan		[Paul Liu] " << endl; break;
    case 66: out << " 	RVD	MIT Remote Virtual Disk Protocol		[Michael_Greenwald] " << endl; break;
    case 67: out << " 	IPPC	Internet Pluribus Packet Core		[Steven_Blumenthal] " << endl; break;
    case 68: out << " 		any distributed file system		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 69: out << " 	SAT-MON	SATNET Monitoring		[Steven_Blumenthal] " << endl; break;
    case 70: out << " 	VISA	VISA Protocol		[Gene_Tsudik] " << endl; break;
    case 71: out << " 	IPCV	Internet Packet Core Utility		[Steven_Blumenthal] " << endl; break;
    case 72: out << " 	CPNX	Computer Protocol Network Executive		[David Mittnacht] " << endl; break;
    case 73: out << " 	CPHB	Computer Protocol Heart Beat		[David Mittnacht] " << endl; break;
    case 74: out << " 	WSN	Wang Span Network		[Victor Dafoulas] " << endl; break;
    case 75: out << " 	PVP	Packet Video Protocol		[Steve_Casner] " << endl; break;
    case 76: out << " 	BR-SAT-MON	Backroom SATNET Monitoring		[Steven_Blumenthal] " << endl; break;
    case 77: out << " 	SUN-ND	SUN ND PROTOCOL-Temporary		[William_Melohn] " << endl; break;
    case 78: out << " 	WB-MON	WIDEBAND Monitoring		[Steven_Blumenthal] " << endl; break;
    case 79: out << " 	WB-EXPAK	WIDEBAND EXPAK		[Steven_Blumenthal] " << endl; break;
    case 80: out << " 	ISO-IP	ISO Internet Protocol		[Marshall_T_Rose] " << endl; break;
    case 81: out << " 	VMTP	VMTP		[Dave_Cheriton] " << endl; break;
    case 82: out << " 	SECURE-VMTP	SECURE-VMTP		[Dave_Cheriton] " << endl; break;
    case 83: out << " 	VINES	VINES		[Brian Horn] " << endl; break;
    case 84: out << " 	IPTM	Internet Protocol Traffic Manager		[Jim_Stevens][1] " << endl; break;
    case 85: out << " 	NSFNET-IGP	NSFNET-IGP		[Hans_Werner_Braun] " << endl; break;
    case 86: out << " 	DGP	Dissimilar Gateway Protocol		[M/A-COM Government Systems, 'Dissimilar Gateway Protocol Specification, Draft Version', Contract no. CS901145, November 16, 1987.][Mike_Little] " << endl; break;
    case 87: out << " 	TCF	TCF		[Guillermo_A_Loyola] " << endl; break;
    case 88: out << " 	EIGRP	EIGRP		[RFC7868] " << endl; break;
    case 89: out << " 	OSPFIGP	OSPFIGP		[RFC1583][RFC2328][RFC5340][John_Moy] " << endl; break;
    case 90: out << " 	Sprite-RPC	Sprite RPC Protocol		[Welch, B., 'The Sprite Remote Procedure Call System', Technical Report, UCB/Computer Science Dept., 86/302, University of California at Berkeley, June 1986.][Bruce Willins] " << endl; break;
    case 91: out << " 	LARP	Locus Address Resolution Protocol		[Brian Horn] " << endl; break;
    case 92: out << " 	MTP	Multicast Transport Protocol		[Susie_Armstrong] " << endl; break;
    case 93: out << " 	AX.25	AX.25 Frames		[Brian_Kantor] " << endl; break;
    case 94: out << " 	IPIP	IP-within-IP Encapsulation Protocol		[John_Ioannidis] " << endl; break;
    case 95: out << " 	MICP (deprecated)	Mobile Internetworking Control Pro.		[John_Ioannidis] " << endl; break;
    case 96: out << " 	SCC-SP	Semaphore Communications Sec. Pro.		[Howard_Hart] " << endl; break;
    case 97: out << " 	ETHERIP	Ethernet-within-IP Encapsulation		[RFC3378] " << endl; break;
    case 98: out << " 	ENCAP	Encapsulation Header		[RFC1241][Robert_Woodburn] " << endl; break;
    case 99: out << " 		any private encryption scheme		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 100: out << " 	GMTP	GMTP		[[RXB5]] " << endl; break;
    case 101: out << " 	IFMP	Ipsilon Flow Management Protocol		[Bob_Hinden][November 1995, 1997.] " << endl; break;
    case 102: out << " 	PNNI	PNNI over IP		[Ross_Callon] " << endl; break;
    case 103: out << " 	PIM	Protocol Independent Multicast		[RFC7761][Dino_Farinacci] " << endl; break;
    case 104: out << " 	ARIS	ARIS		[Nancy_Feldman] " << endl; break;
    case 105: out << " 	SCPS	SCPS		[Robert_Durst] " << endl; break;
    case 106: out << " 	QNX	QNX		[Michael_Hunter] " << endl; break;
    case 107: out << " 	A/N	Active Networks		[Bob_Braden] " << endl; break;
    case 108: out << " 	IPComp	IP Payload Compression Protocol		[RFC2393] " << endl; break;
    case 109: out << " 	SNP	Sitara Networks Protocol		[Manickam_R_Sridhar] " << endl; break;
    case 110: out << " 	Compaq-Peer	Compaq Peer Protocol		[Victor_Volpe] " << endl; break;
    case 111: out << " 	IPX-in-IP	IPX in IP		[CJ_Lee] " << endl; break;
    case 112: out << " 	VRRP	Virtual Router Redundancy Protocol		[RFC5798] " << endl; break;
    case 113: out << " 	PGM	PGM Reliable Transport Protocol		[Tony_Speakman] " << endl; break;
    case 114: out << " 		any 0-hop protocol		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 115: out << " 	L2TP	Layer Two Tunneling Protocol		[RFC3931][Bernard_Aboba] " << endl; break;
    case 116: out << " 	DDX	D-II Data Exchange (DDX)		[John_Worley] " << endl; break;
    case 117: out << " 	IATP	Interactive Agent Transfer Protocol		[John_Murphy] " << endl; break;
    case 118: out << " 	STP	Schedule Transfer Protocol		[Jean_Michel_Pittet] " << endl; break;
    case 119: out << " 	SRP	SpectraLink Radio Protocol		[Mark_Hamilton] " << endl; break;
    case 120: out << " 	UTI	UTI		[Peter_Lothberg] " << endl; break;
    case 121: out << " 	SMP	Simple Message Protocol		[Leif_Ekblad] " << endl; break;
    case 122: out << " 	SM (deprecated)	Simple Multicast Protocol		[Jon_Crowcroft][draft-perlman-simple-multicast] " << endl; break;
    case 123: out << " 	PTP	Performance Transparency Protocol		[Michael_Welzl] " << endl; break;
    case 124: out << " 	ISIS over IPv4			[Tony_Przygienda] " << endl; break;
    case 125: out << " 	FIRE			[Criag_Partridge] " << endl; break;
    case 126: out << " 	CRTP	Combat Radio Transport Protocol		[Robert_Sautter] " << endl; break;
    case 127: out << " 	CRUDP	Combat Radio User Datagram		[Robert_Sautter] " << endl; break;
    case 128: out << " 	SSCOPMCE			[Kurt_Waber] " << endl; break;
    case 129: out << " 	IPLT			[[Hollbach]] " << endl; break;
    case 130: out << " 	SPS	Secure Packet Shield		[Bill_McIntosh] " << endl; break;
    case 131: out << " 	PIPE	Private IP Encapsulation within IP		[Bernhard_Petri] " << endl; break;
    case 132: out << " 	SCTP	Stream Control Transmission Protocol		[Randall_R_Stewart] " << endl; break;
    case 133: out << " 	FC	Fibre Channel		[Murali_Rajagopal][RFC6172] " << endl; break;
    case 134: out << " 	RSVP-E2E-IGNORE			[RFC3175] " << endl; break;
    case 135: out << " 	Mobility Header		Y	[RFC6275] " << endl; break;
    case 136: out << " 	UDPLite			[RFC3828] " << endl; break;
    case 137: out << " 	MPLS-in-IP			[RFC4023] " << endl; break;
    case 138: out << " 	manet	MANET Protocols		[RFC5498] " << endl; break;
    case 139: out << " 	HIP	Host Identity Protocol	Y	[RFC7401] " << endl; break;
    case 140: out << " 	Shim6	Shim6 Protocol	Y	[RFC5533] " << endl; break;
    case 141: out << " 	WESP	Wrapped Encapsulating Security Payload		[RFC5840] " << endl; break;
    case 142: out << " 	ROHC	Robust Header Compression		[RFC5858] " << endl; break;
    case 143: out << " 	Ethernet	Ethernet		[RFC8986] " << endl; break;
    case 144: out << " 	AGGFRAG	AGGFRAG encapsulation payload for ESP		[RFC9347] " << endl; break;
    case 145: out << " 	NSH	Network Service Header	N	[RFC9491] " << endl; break;
    case 146: out << "		Unassigned		[Internet_Assigned_Numbers_Authority] " << endl; break;
    case 253: out << " 		Use for experimentation and testing	Y	[RFC3692] " << endl; break;
    case 254: out << " 		Use for experimentation and testing	Y	[RFC3692] " << endl; break;
    case 255: out << " 	Reserved	 "  << endl; break;
    default: 

        if (prot >= 146 || prot <= 252) {
            out << "Unassigned		[Internet_Assigned_Numbers_Authority]"  << endl; 
            break;
        }

        out << " 	Unknown	 "  << endl; break;
    }
}

void Model::print_udp_header(ofstream&  out, unsigned char *buffer, int size) {
    // getting actual size of IP header

    // getting pointer to udp header
    struct udphdr *udp = (struct udphdr *)(buffer + size + sizeof(struct ethhdr));
    out << "\t|-Source Port : " << ntohs(udp->source) << endl;
    out << "\t|-Destination Port : " << ntohs(udp->dest) << endl;
    out << "\t|-UDP Length : " << ntohs(udp->len) << endl;
    out << "\t|-UDP Checksum : " << ntohs(udp->check) << endl;  //  ntohs() function converts the unsigned short integer netshort from network byte order to host byte order.
}

void Model::print_tcp_header(ofstream&  out, unsigned char *buffer, int size) {
    // getting pointer to tcp header
    struct tcphdr *tcp = (struct tcphdr *)(buffer + size + sizeof(struct ethhdr));
    out << "\nTCP Header\n";
    out << "\t|-Source Port          : " << ntohs(tcp->source) << endl;
    out << "\t|-Destination Port     : " << ntohs(tcp->dest) << endl;
    out << "\t|-Sequence Number      : " << ntohl(tcp->seq) << endl;
    out << "\t|-Acknowledge Number   : " << ntohl(tcp->ack_seq) << endl;
    out << "\t|-Header Length        : " << (unsigned int)tcp->doff << " DWORDS or " << (unsigned int)tcp->doff * 4 << " BYTES" << endl;
    out << "\t|----------Flags-----------\n";
    out << "\t\t|-Urgent Flag          : " << (unsigned int)tcp->urg << endl;
    out << "\t\t|-Acknowledgement Flag : " << (unsigned int)tcp->ack << endl;
    out << "\t\t|-Push Flag            : " << (unsigned int)tcp->psh << endl;
    out << "\t\t|-Reset Flag           : " << (unsigned int)tcp->rst << endl;
    out << "\t\t|-Synchronise Flag     : " << (unsigned int)tcp->syn << endl;
    out << "\t\t|-Finish Flag          : " << (unsigned int)tcp->fin << endl;
    out << "\t|-Window size          : " << ntohs(tcp->window) << endl;
    out << "\t|-Checksum             : " << ntohs(tcp->check) << endl;
    out << "\t|-Urgent Pointer       : " << tcp->urg_ptr << endl;    
}

void Model::protocolSwitch(ofstream& out, unsigned char *buffer) {
    struct iphdr *ip = (struct iphdr*)(buffer + sizeof (struct ethhdr));

    protocol = static_cast<unsigned int>(ip->protocol);
    out << "\nProtocol : "; 
    out << protocol << endl;
    printProtocol(out, protocol);
    switch(protocol){
        case 6:
            print_tcp_header(out, buffer, iphdrlen);
            break;
        case 17:
            print_udp_header(out, buffer, iphdrlen);
            break;
        default:
            printProtocol(out, protocol);
            break;
    }
}

