#include "xcp.h"
#include "xcp_sxl_master_req_handler.h"
extern uint8_t received_frame[];
extern XCP_sxl_Frame xcp_send_frame;
extern XCP_sxl_Frame xcp_recv_frame;

void Xcp_decode_frame_server(){
    xcp_recv_frame.Len = received_frame[0];
    xcp_recv_frame.Ctr = received_frame[1];
    for (int i = 0; i < xcp_recv_frame.Len ; i++) {
        xcp_recv_frame.Data[i] = received_frame[i + 2];
    }
    xcp_recv_frame.Cs = received_frame[xcp_recv_frame.Len + 1]; // Checksum is after data
}

void Xcp_slave_handle_request(){
    Xcp_decode_frame_server(); // Decode the received frame into xcp_recv_frame structure
    switch (xcp_recv_frame.Data[0]) { // Assuming the first byte of Data is the command ID
        case CONNECT_CMD: // Connect command
            Xcp_connect(); // Send the response frame after handling the connect command
            break;
        case SYNCH_CMD: // Synchronization command
            Xcp_synch();
            break;
        case GET_STATUS_CMD: // Get status command
            Xcp_get_status();
            break;
        case DISCONNECT_CMD: // Disconnect command
            Xcp_disconnect();
            break;
        default:
            Xcp_negative_response(ERR_CMD_UNKNOWN); // Send negative response for unknown command
            break;
    }    
    send_xcp_frame();
}
