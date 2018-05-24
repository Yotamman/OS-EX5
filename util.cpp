/*
 * Description:
 * 	This file contains declarations of utility functions
 *  
 */

#include "util.h"

int dnslookup(const char* hostname,
	      char* firstIPstr,
	      int maxSize)
{
  char* tempAddress = (char*)""; 
  int addressCount; 
  int status = dnslookupAll(hostname, &tempAddress, 1, &addressCount); 
  if((int)strlen(tempAddress) > maxSize)
  {
    printf("Error: address too long in dnslookup\n"); 
    return UTIL_FAILURE; 
  }
  if(addressCount == 1) 
  {
      strcpy(firstIPstr, tempAddress); 
  }
  return status; 
}

int dnslookupAll(const char* hostname, char** ipArray, int maxAddresses, int* addressCount){

  /* Local vars */
  struct addrinfo* headresult = NULL;
  struct addrinfo* result = NULL;
  struct sockaddr_in* ipv4sock = NULL;
  struct in_addr* ipv4addr = NULL;
  char ipv4str[INET_ADDRSTRLEN];
  char ipstr[INET6_ADDRSTRLEN] = "";
  int addrError = 0;
  *addressCount = 0; 

  /* DEBUG: Print Hostname*/
   #ifdef UTIL_DEBUG
   fprintf(stderr, "%s\n", hostname);
  #endif
   
    /* Lookup Hostname */
    addrError = getaddrinfo(hostname, NULL, NULL, &headresult);
    if(addrError){
	fprintf(stderr, "%s: Error looking up Address: %s\n",hostname, gai_strerror(addrError));
	return UTIL_FAILURE;
    }
    /* Loop Through result Linked List */
    for(result=headresult; result != NULL; result = result->ai_next){
	/* Extract IP Address and Convert to String */
	if(result->ai_addr->sa_family == AF_INET){
	    /* IPv4 Address Handling */
	    ipv4sock = (struct sockaddr_in*)(result->ai_addr);
	    ipv4addr = &(ipv4sock->sin_addr);
	    if(!inet_ntop(result->ai_family, ipv4addr,
			  ipv4str, sizeof(ipv4str))){
		perror("Error Converting IP to String");
		return UTIL_FAILURE;
	    }
	     #ifdef UTIL_DEBUG
	    fprintf(stdout, "%s\n", ipv4str);
	    #endif
	    if(strcmp(ipstr,ipv4str)!=0 && *addressCount < maxAddresses)
	    {
		ipArray[*addressCount] = strdup(ipv4str); 
		// New String
		(*addressCount)++; 
		
		#ifdef UTIL_DEBUG
		printf("Address: %s\n", ipv4str);
		#endif
	    }
	    
	    strncpy(ipstr, ipv4str, sizeof(ipstr));
	    ipstr[sizeof(ipstr)-1] = '\0';
	    
	    
	}
	else if(result->ai_addr->sa_family == AF_INET6){
	    /* IPv6 Handling */
	    #ifdef UTIL_DEBUG
	    fprintf(stdout, "IPv6 Address: Not Handled\n");
	    #endif
	    strncpy(ipstr, "UNHANDELED", sizeof(ipstr));
	    ipstr[sizeof(ipstr)-1] = '\0';
	}
	else{
	    /* Unhandlded Protocol Handling */
	    #ifdef UTIL_DEBUG
	    fprintf(stdout, "Unknown Protocol: Not Handled\n");
	    #endif
	    strncpy(ipstr, "UNHANDELED", sizeof(ipstr));
	    ipstr[sizeof(ipstr)-1] = '\0';
	}
    }

    /* Cleanup */
    freeaddrinfo(headresult);

    return UTIL_SUCCESS;
}
