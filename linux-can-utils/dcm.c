#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/if.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <stdint.h> // Include the header file for uint8_t

#include "lib.h"

#define CAN_INTERFACE "can0"
#define CAN_ID 0x123 // Example CAN ID for diagnostic messages

// Function prototypes
void send_diagnostic_request(int sock);
int receive_diagnostic_request(int sock);

// DCM logic
void dcm_main(int sock) {
    // Main loop for handling diagnostic requests
    while (1) {
        // Wait for diagnostic request from CANoe simulation
        

        // Send diagnostic response
        send_diagnostic_request(sock);

        // Receive diagnostic request
        struct can_frame response_frame;
        receive_diagnostic_request(sock);

    }
}


// Function to receive diagnostic request over CAN
int receive_diagnostic_request(int sock) {
    int nbytes;
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;

    if ((sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("socket");
        return 0;
    }

    strcpy(ifr.ifr_name, CAN_INTERFACE);
    ioctl(sock, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 0;
    }

    nbytes = read(sock, &frame, sizeof(struct can_frame));

    if (nbytes < 0) {
        perror("read");
        return 0;
    }

    // Process received CAN frame
    printf("Received CAN Frame: ID=%X DLC=%d Data=", frame.can_id, frame.can_dlc);
    for (int i = 0; i < frame.can_dlc; i++) {
        printf("%02X ", frame.data[i]);
    }
    printf("\n");

   // close(sock);
    return 1; // Message received
}
// Function to send diagnostic request over CAN
void send_diagnostic_request(int sock) {
    //int sock; /* can raw socket */ 
    int nbytes;
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;

    /* CAN message to be sent out */
    unsigned char buff[] = "7DF#0201050000000000";

    /* parse CAN frame */
    if (parse_canframe(buff, &frame)) {
        fprintf(stderr, "\nWrong CAN-frame format!\n\n");
        return;
    }

    /* open socket */
    if ((sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("socket");
        return;
    }

    addr.can_family = AF_CAN;

    strcpy(ifr.ifr_name, CAN_INTERFACE);
    if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
        perror("SIOCGIFINDEX");
        close(sock);
        return;
    }
    addr.can_ifindex = ifr.ifr_ifindex;

    /* disable default receive filter on this RAW socket */
    //setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sock);
        return;
    }

    int i =0;

    /* send frame */
	for(i=0;i<100;i++)
	{
		if ((nbytes = write(sock, &frame, sizeof(frame))) != sizeof(frame)) {
			perror("write");
			//return 1;
		}
		
		fprintf(stderr, "%d \n", i);

		usleep(10000); /* Delay before next loop */
	}
    close(sock);
}
