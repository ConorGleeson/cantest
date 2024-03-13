#include <stdio.h>
#include "app.h"
#include "dcm.h"
#include "dem.h"

int main() {
    // Initialize DCM and DEM modules
    initialize_dcm();
    initialize_dem();

    // Run simulation app
    main_app_logic();

    // Clean up resources
    cleanup_dcm();
    cleanup_dem();

    return 0;
}