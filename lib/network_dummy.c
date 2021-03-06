/* A dummy network module for testing on machines without rf24 access */
#include "network.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct address {
    uint8_t addr;
} Address;

Address address = {.addr = 0};
Address broadcast = {.addr = 255};

int net_init(){
    printf("dummy>> Starting network layer...\n");
    /* spin off sensor/actuator threads? */
    printf("dummy>> Network layer started!\n");
    return 1;
}
void net_close() {}
int net_sendto(Address *addr, void *payload, int len){
    /*add to global message queue */
    return 1;
}

int net_recvfrom(void *payload, size_t len, Address *addr, int block){
    /* pull from global message queue or fake it */
    return 0;
}

char * net_ntoa(Address *addr){
    static char str[4];
    sprintf(str, "%d", addr->addr);
    return str;
}
int net_aton(char *addr_s, Address *addr){
    return sscanf(addr_s, "%3d", &(addr->addr));
}

void net_addrcpy(Address *dst, Address *src){
    dst->addr = src->addr;
}
Address *net_addralloc(char *addr_s){
    Address *addr = (Address*)malloc(sizeof(Address));
    if (addr) net_aton(addr_s, addr);
    return addr;
}
void net_addrfree(Address *addr){
    free(addr);
}
Address *net_addr(){
    return &address;
}
Address *net_broadaddr(){
    return &broadcast;
}