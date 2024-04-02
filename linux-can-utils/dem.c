#include <stdio.h>
#include "dem.h"

DemEvent dem_events[MAX_EVENTS];
int dem_event_count = 0;

void add_event(uint32_t event_id, uint8_t severity, uint8_t status) {
    if (dem_event_count < MAX_EVENTS) {
        dem_events[dem_event_count].event_id = event_id;
        dem_events[dem_event_count].severity = severity;
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
        printf("Event ID: %u, Severity: %u, Status: %u\n", dem_events[i].event_id, dem_events[i].severity, dem_events[i].status);
    }
}