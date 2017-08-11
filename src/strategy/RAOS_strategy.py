import nnpy
import time
import numpy as np
import struct

sock = nnpy.Socket(nnpy.AF_SP, nnpy.PAIR)
sock.connect('ws://127.0.0.1:5555')

pos_ref = np.array([0,0,0], dtype=np.float32)
heading_ref = np.float32(0)

checksum = np.uint8(0)

data = bytearray()
data.append('$')
data.append('R')
data.append(90)    # cmd
data.append(18)    # dlen
data.append(3)     # robot type
data.append(0)     # robot id
string = struct.pack('<ffff', pos_ref[0], pos_ref[1], pos_ref[2], heading_ref)
for i in range(len(string)):
    data.append(string[i])
for i in range(2, len(data)):
    checksum ^= data[i]
data.append(checksum)

while True:
    sock.send(data)
    time.sleep(0.01)

sock.close()
