#include <stdio.h>
#include "dem.h"
#include "dcm.h"
#include "app.h"
#include "dem.c"




// Main logic of the simulation app
void display_menu() {
    printf("\nSimulation App Menu:\n");
    printf("1. Select DID to Change Status\n");
    printf("2. View Stored Events\n");
    printf("3. Send Diagnostic Request\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

void run_simulation_app() {
    int choice;
    uint32_t selected_did;
    uint8_t new_status;

    // Initialize DEM with predefined DIDs
    initialize_dem();

    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Select DID to change status
                printf("\nSelect a DID to change its status:\n");
                for (int i = 0; i < sizeof(hardcoded_dids) / sizeof(hardcoded_dids[0]); i++) {
                    printf("%d. DID 0x%02X\n", i + 1, hardcoded_dids[i].event_id);
                }
                printf("Enter your choice: ");
                scanf("%d", &choice);
                if (choice >= 1 && choice <= sizeof(hardcoded_dids) / sizeof(hardcoded_dids[0])) {
                    selected_did = hardcoded_dids[choice - 1].event_id;
                    printf("\nEnter new status value (0 or 1): ");
                    scanf("%hhu", &new_status);
                    update_soc_value(selected_did, new_status);
                } else {
                    printf("Invalid choice!\n");
                }
                break;
            case 2:
                // View Stored Events
                print_events();
                break;
            case 3:
                // Continuously receive diagnostic request until a message is received
                while (1) {
                    if (receive_diagnostic_request() != 0) {
                        // If a message is received, break the loop and proceed to sending the diagnostic request
                        break;
                    }
                }
                // Send diagnostic request
                send_diagnostic_request();
                break;
            case 4 :
                // Exit
                printf("\nExiting Simulation App.\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 4);
}
