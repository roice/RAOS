#ifndef RAOS_SERIAL_PROTOCOL_H
#define RAOS_SERIAL_PROTOCOL_H

#define RSP_BYTE_HEADER             '$'
#define RSP_BYTE_START              'R'

#define RSP_INFO_SENSOR_WIND        70
#define RSP_INFO_SENSOR_ODOR        71

#define RSP_INFO_ROBOT_PIONEER      80
#define RSP_INFO_ROBOT_MICROBEE     81
#define RSP_INFO_ROBOT_QINGLUAN     82

#define RSP_CMD_ROBOT_GOTO          90

#include <cstdint>

typedef enum {
    RSP_STATE_IDLE,
    RSP_STATE_START,
    RSP_STATE_CMD,
    RSP_STATE_LEN,
    RSP_STATE_DATA,
} RSP_state_e;

typedef struct {
    // info in the frame
    uint8_t     cmd;
    uint8_t     dlen;
    uint8_t     id;
    uint8_t     data[256];
    // parser related
    RSP_state_e state;
    uint8_t     checksum;
    uint8_t     count;
} RAOS_SP_frame_t;

bool RAOS_serial_protocol_parser(uint8_t, RAOS_SP_frame_t*);

#endif
