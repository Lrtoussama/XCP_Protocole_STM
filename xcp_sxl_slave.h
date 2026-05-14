#include <stdint.h>
// CTO 

#define R_POS_PID 0xFF

// Connect 
#define CONNECT_Packet_Length 8
// Pos 1
uint8_t CAL = 0x00; // 0x01 if calibration page is available
uint8_t DAQ = 0x00; // or 0x04 if DAQ is available

#define RES CAL | DAQ 
// Pos 2
#define ADD_GRA_BYTE 0x00
#define LITTLE_ENDIAN 0x00
#define COMM_MODE_BASIC LITTLE_ENDIAN
// Pos 3
#define MAX_CTO 0x08
// Pos 4
#define MAX_DTO 0x0800
// Pos 6
#define PROT_VER 0x01
// Pos 7
#define TL_VER 0x01


// synch 

#define Synch_Packet_ID 0xFE
#define ERR_CMD_SYNCH 0x00

// Get status
#define GET_STATUS_Packet_LENGTH 6
//Pos 1
uint8_t DAQ_RUNNING = 0x00; // or 0x40 if DAQ is running
#define CURRENT_SESSION_STATUS DAQ_RUNNING
//pos 2
uint8_t CalRes = 0x00; // or 0x10 if calibration page is unlocked
uint8_t DaqRes = 0x00; // or 0x40 if DAQ is running
#define PGM_RES 0x00
#define DBG_RES 0x00
#define CURRENT_RESOURCE_PROTECTION_STATUS (CalRes | DaqRes | PGM_RES | DBG_RES)
//Pos 3
#define STATE_NUMBER 0x00 // No special state 
//Pos 4
#define SESSION_CONFIGURATION_ID 0x0000 // Default session configuration ID

Com_status xcp_com_status = Disconnected;
int frame_count = 0;
XCP_sxl_Frame xcp_recv_frame;
XCP_sxl_Frame xcp_send_frame;
uint8_t received_frame[XCP_MAX_DATA_LENGTH + 4]; // Buffer to hold the raw received frame (Len + Ctr + Data + Cs)

