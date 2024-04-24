/* dcm.h */

#ifndef DCM_H
#define DCM_H


#include <stdint.h>


// Function prototypes
void initialize_dcm();
void inform_dcm(uint32_t event_id);
void dcm_main(int sock);
void send_diagnostic_request();
int receive_diagnostic_request();
void cleanup_dcm();



#endif /* DCM_H */
