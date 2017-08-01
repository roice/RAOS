/*
 * Pioneer robot model
 *
 * Author:  Roice Luo
 * Date:    2017-07-28  create this file
 */

#include "cstdint"
#include "model_robot_pioneer.h"
#include "common/RAOS_serial_protocol.h"
#include "common/endian/little_endian.hpp"

model_robot_pioneer_c::model_robot_pioneer_c(void)
{
}

void model_robot_pioneer_c::update(void)
{
}

int model_robot_pioneer_c::encode_info2string(uint8_t *buf)
{
    int idx = 0;

    buf[0] = '$';
    buf[1] = 'R';
    buf[2] = RSP_INFO_ROBOT_PIONEER;
    buf[3] = 2+3*4+3*4;  // data bytes
    idx += 4;
    // robot type and id
    buf[idx++] = type;
    buf[idx++] = id;
    // robot pos,att
    for (int i = 0; i < 3; i++) {
        endian::little_endian::put32(*(int32_t*)(&pos[i]), (uint8_t*)(buf+idx));
        idx += 4;
    }
    for (int i = 0; i < 3; i++) {
        endian::little_endian::put32(*(int32_t*)(&att[i]), (uint8_t*)(buf+idx));
        idx += 4;
    }
    // checksum
    char checksum = 0;
    for (int i = 2; i < idx; i++)
        checksum ^= buf[i];
    buf[idx++] = checksum;

    return idx;
}
