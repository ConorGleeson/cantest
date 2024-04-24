#include <stdio.h>
#include "dem.h"

#define MAX_EVENTS 100



// Hardcoded list of DIDs and their responses
const HardcodedDIDs hardcoded_dids[] = {
    {0x9A, {0x62, 0x00, 0x9A, 0x00}}, // EV Charging State: 0x9A, value: 0 (off)
};

HardcodedDIDs get_hardcoded_did(int index) {
    if (index >= 0 && index < sizeof(hardcoded_dids) / sizeof(hardcoded_dids[0])) {
        return hardcoded_dids[index];
    } else {
        HardcodedDIDs empty_did = {0, {0}}; // Return an empty struct if index is out of bounds
        return empty_did;
    }
}

int get_hardcoded_did_count() {
    // Calculate the size of the hardcoded_dids array
    return sizeof(hardcoded_dids) / sizeof(hardcoded_dids[0]);
}

const HardcodedDIDs* get_hardcoded_dids_for_dcm() {
    return hardcoded_dids;
}

DemEvent dem_events[MAX_EVENTS];
int dem_event_count = 0;

void add_event(uint32_t event_id, uint8_t status) {
    if (dem_event_count < MAX_EVENTS) {
        dem_events[dem_event_count].event_id = event_id;
        dem_events[dem_event_count].status = status;
        dem_event_count++;
    } else {
        printf("DEM storage is full\n");
    }
}

DemEvent* get_event(uint32_t event_id) {
    for (int i = 0; i < dem_event_count; i++) {
        if (dem_events[i].event_id == event_id) {
            return &dem_events[i];
        }
    }
    return NULL;
}

void clear_events() {
    dem_event_count = 0;
}

void print_events() {
    printf("Events stored in DEM:\n");
    for (int i = 0; i < dem_event_count; i++) {
        printf("Event ID: %u, Status: %u\n", dem_events[i].event_id, dem_events[i].status);
    }
}

void initialize_dem() {
    for (size_t i = 0; i < sizeof(hardcoded_dids) / sizeof(hardcoded_dids[0]); i++) {
        add_event(hardcoded_dids[i].event_id, 0); // Initialize status to 0
    }
}

void update_soc_value(uint32_t event_id, uint8_t new_status) {
    // Find the event with the specified ID and update its status
    DemEvent* event = get_event(event_id);
    if (event != NULL) {
        event->status = new_status;
    } else {
        printf("Event with ID 0x%02X not found\n", event_id);
    }
}