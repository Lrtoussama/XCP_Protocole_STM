
#include "xcp.h"
#include <stdio.h>
extern uint8_t received_frame[];
extern XCP_sxl_Frame xcp_send_frame;
void recv_xcp_frame() {
    received_frame[0] = 2;
    received_frame[1] = 1;
    received_frame[2] = 0xFF; // Example data byte 1
    received_frame[3] = 0x00; // Example data byte 2
    for (int i=0 ; i<4 ; i++){
        received_frame[4] =+ received_frame[i];
    }
    Xcp_slave_handle_request();
}

void send_xcp_frame(){
    printf("len = %d \n",xcp_send_frame.Len);
    printf("Ctr = %d \n",xcp_send_frame.Ctr);
    for(int i=0 ; i < xcp_send_frame.Len ; i++){
        printf("data[%d] = %d \n",i,xcp_send_frame.Data[i]);
    }
    printf("len = %d \n",xcp_send_frame.Len);
    printf("Cs= %d \n",xcp_send_frame.Cs);
}
int main() {
    recv_xcp_frame();
    return 0;
}