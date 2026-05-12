#include "xcp.h"

void Xcp_negative_response(uint8_t error_code) {
    xcp_send_frame.Len = 2; // Example length for negative response
    xcp_send_frame.Ctr = frame_count++;
    xcp_send_frame.Data[0] = Error_Packet_ID; // Using error packet ID for negative response
    xcp_send_frame.Data[1] = error_code; // Set the error code in the response
    xcp_send_frame.Cs = Checksum(); // Calculate checksum if needed
}

uint8_t Checksum(){
    uint8_t checksum = 0;
    checksum += xcp_send_frame.Len;
    checksum += xcp_send_frame.Ctr;
    for (int i = 0; i < xcp_send_frame.Len - 2; i++) { // Exclude Len and Ctr from checksum calculation
        checksum += xcp_send_frame.Data[i];
    }
    return checksum;
}

void Xcp_connect() {
        xcp_send_frame.Len = CONNECT_Packet_Length;
        xcp_send_frame.Ctr = frame_count++;
        xcp_send_frame.Data[0] = R_POS_PID ;
        xcp_send_frame.Data[1] = RES;
        xcp_send_frame.Data[2] = COMM_MODE_BASIC;
        xcp_send_frame.Data[3] = MAX_CTO;
        xcp_send_frame.Data[4] = (MAX_DTO >> 8 ) & 0xFF;
        xcp_send_frame.Data[5] = MAX_DTO & 0xFF;
        xcp_send_frame.Data[6] = PROT_VER;
        xcp_send_frame.Data[7] = TL_VER;
        xcp_send_frame.Cs = Checksum(); // Calculate checksum for the connect packet
        xcp_com_status = Connected;
}

void Xcp_disconnect() {
    xcp_com_status = Disconnected;
    xcp_send_frame.Len = 0;
    xcp_send_frame.Ctr = 0;
    for (int i = 0; i < XCP_MAX_DATA_LENGTH; i++) {
        xcp_send_frame.Data[i] = 0;
    }
    xcp_send_frame.Cs = Checksum(); // Calculate checksum for the disconnect packet if needed
}

void Xcp_synch() {
    // Implementation of synchronization logic
    if(xcp_com_status == Connected) {
        xcp_send_frame.Len = 2; // Example length for synchronization packet
        xcp_send_frame.Ctr = frame_count++;
        xcp_send_frame.Data[0] = Synch_Packet_ID;
        xcp_send_frame.Data[1] = ERR_CMD_SYNCH; // Example error code for synchronization
        xcp_send_frame.Cs = Checksum(); // Calculate checksum if needed
    }else {
        Xcp_negative_response(ERR_CMD_UNKNOWN); // Send negative response if not connected
    }
}

void Xcp_get_status() {
    // Implementation of get status logic
    if(xcp_com_status == Connected) {
        xcp_send_frame.Len = 4; // Example length for get status packet
        xcp_send_frame.Ctr = frame_count++;
        xcp_send_frame.Data[0] = CurrenT_SESSION_STATUS;
        xcp_send_frame.Data[1] = CURRENT_SESSION_STATUS;
        xcp_send_frame.Data[2] = STATE_NUMBER;
        xcp_send_frame.Data[3] = (SESSION_CONFIGURATION_ID >> 8) & 0xFF; // High byte of session configuration ID
        xcp_send_frame.Data[4] = SESSION_CONFIGURATION_ID & 0xFF; // Low byte of session configuration ID
        xcp_send_frame.Cs = Checksum(); // Calculate checksum for the get status packet
    } else {
        Xcp_negative_response(ERR_CMD_UNKNOWN); // Send negative response if not connected
    }
}
