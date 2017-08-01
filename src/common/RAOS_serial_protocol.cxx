/*
 * RAOS serial protocol
 *
 * Author:  Bing Luo
 * Date:    2017-07-30
 */

#include "RAOS_serial_protocol.h"

bool RAOS_serial_protocol_parser(uint8_t c, RAOS_SP_frame_t *frame)
{
    if (frame->state == RSP_STATE_IDLE) {
        if (c == RSP_BYTE_HEADER)
            frame->state = RSP_STATE_START;
    }
    else if (frame->state == RSP_STATE_START) {
        if (c == RSP_BYTE_START) {
            frame->state = RSP_STATE_CMD;
            frame->checksum = 0;
        }
        else
            frame->state = RSP_STATE_IDLE;
    }
    else if (frame->state == RSP_STATE_CMD) {
        frame->cmd = c;
        frame->checksum ^= c;
        frame->state = RSP_STATE_LEN;
    }
    else if (frame->state == RSP_STATE_LEN) {
        if (c > 0) { // data length must > 0
            frame->dlen = c;
            frame->count = 0;
            frame->checksum ^= c;
            frame->state = RSP_STATE_DATA;
        }
        else
            frame->state = RSP_STATE_IDLE;
    }
    else if (frame->state == RSP_STATE_DATA) {
        if (frame->count < frame->dlen) {
            frame->data[frame->count++] = c;
            frame->checksum ^= c;
        }
        else { // received the whole data
            frame->state = RSP_STATE_IDLE;
            if (frame->checksum == c)
                return true; // received whole frame
        }
    }
    return false;
}
