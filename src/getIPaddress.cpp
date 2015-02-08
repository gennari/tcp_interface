#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/if_link.h>


bool getIPaddress(const char *netif, char * host) {
 
    struct ifaddrs *ifaddr, *ifa;
    int family, s, n;
    

    if (getifaddrs(&ifaddr) == -1) {
	perror("getifaddrs");
	return false;
    }

    /* Walk through linked list, maintaining head pointer so we
      can free list later */

    for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
	if (ifa->ifa_addr == NULL)
	    continue;

	family = ifa->ifa_addr->sa_family;

	/* Display interface name and family (including symbolic
	  form of the latter for the common families) */

	/* printf("%-8s %s (%d)\n",
	      ifa->ifa_name,
	      (family == AF_PACKET) ? "AF_PACKET" :
	      (family == AF_INET) ? "AF_INET" :
	      (family == AF_INET6) ? "AF_INET6" : "???",
	      family); */

	/* For an AF_INET* interface address, display the address */

	if ( (family == AF_INET /*|| family == AF_INET6*/ ) && 
	     (strcmp(ifa->ifa_name,netif)==0) )
	{
	    s = getnameinfo(ifa->ifa_addr,
		    (family == AF_INET) ? sizeof(struct sockaddr_in) :
					  sizeof(struct sockaddr_in6),
		    host, NI_MAXHOST,
		    NULL, 0, NI_NUMERICHOST);
	    if (s != 0) {
		printf("getnameinfo() failed: %s\n", gai_strerror(s));
		return false;
	    }

	    // printf("%-8s %s\n", ifa->ifa_name,host);
	    
	} 
	/*else if (family == AF_PACKET && ifa->ifa_data != NULL) {
	    struct rtnl_link_stats *stats = ifa->ifa_data;

	    printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
		  "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
		  stats->tx_packets, stats->rx_packets,
		  stats->tx_bytes, stats->rx_bytes);
	}*/
    }

    freeifaddrs(ifaddr);
    return true;
}

int main(int argc, char *argv[])
{
    if (argc<2) {
      printf(" Use: %s <network interface>\ne.g.: %s eth0\n",argv[0],argv[0]
      );
      exit(-1);
    }
    
    char host[NI_MAXHOST]; strcpy(host,"<<<NOT FOUND>>>");
    getIPaddress(argv[1], host);
    printf("%s\n",host);
    
    exit(EXIT_SUCCESS);
}
       
       