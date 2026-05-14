#include <stdint.h>
#define XCP_MAX_DATA_LENGTH 255

// error packet
#define Error_Packet_ID 0xFE
#define ERR_CMD_UNKNOWN 0x20

typedef struct XCP_sxl_Frame {
    uint8_t Len;
    uint8_t Ctr;
    uint8_t Data[XCP_MAX_DATA_LENGTH];
    uint8_t Cs;

}XCP_sxl_Frame;

typedef enum Com_status {
    Connected = 1,
    Disconnected = 0
}Com_status;

 
void Xcp_connect();
uint8_t Checksum(XCP_sxl_Frame xcp_sxl_Frame);
void Xcp_disconnect();
void Xcp_synch();
void Xcp_get_status();
void Xcp_slave_handle_request();
void Xcp_negative_response(uint8_t error_code);
void recv_xcp_frame();

