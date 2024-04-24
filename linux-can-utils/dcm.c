#include "dem.h"
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
void send_diagnostic_request(int sock, const HardcodedDIDs *hardcoded_dids, int num_dids);
int receive_diagnostic_request(int sock);



// DCM logic
void dcm_main(int sock) {
    // Initialize DEM with predefined DIDs
    initialize_dem();
   
    const HardcodedDIDs* hardcoded_dids = get_hardcoded_dids_for_dcm();
    int num_dids = get_hardcoded_did_count(); // Get the number of DIDs

    // Main loop for handling diagnostic requests
    while (1) {
        // Send diagnostic response with the list of DIDs
        send_diagnostic_request(sock, hardcoded_dids, num_dids); 
        // Receive diagnostic request
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
void send_diagnostic_request(int sock, const HardcodedDIDs *hardcoded_dids, int num_dids) {
    int nbytes;
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;

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

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sock);
        return;
    }

    // Construct and send CAN frames for each DID
    for (int i = 0; i < num_dids; i++) {
        // Construct CAN frame for the current DID
        frame.can_id = hardcoded_dids[i].event_id;
        frame.can_dlc = 4; // Length of data (bytes)

        // Copy positive response data into the frame
        for (int j = 0; j < 4; j++) {
            frame.data[j] = hardcoded_dids[i].positive_response[j];
        }

        // Send the CAN frame
        if ((nbytes = write(sock, &frame, sizeof(frame))) != sizeof(frame)) {
            perror("write");
        }
    }

    close(sock);
}
