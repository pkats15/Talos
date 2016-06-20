import serial
import time
import struct
#
# class Robot:
#     def __init__(self, port):
#         self.port = port
#     def start_connection(self):
#         self.robot = serial.Serial(self.port)
#         print 'Starting...'
#     def receive_number(self):
#         try:
#             while True:
#                 n = self.robot.in_waiting
#                 if n != 0:
#
#                     # data = self.robot.read(n)
#                     # print("DATA:", round(struct.unpack('f', data[15:19])[0], 1))
#                     # return round(struct.unpack('f', data[15:19])[0], 1)
#         except:
#             self.robot.close()

ser = serial.Serial('COM14', 9600)
time.sleep(2)
try:
    while(1):
        d = True
        if ser.in_waiting and d:
            #print int(len(ser.read(1), base=16)
            size = ord(ser.read(1))
            # size = 0
            print ser.in_waiting, size
            d = False
            ser.close()
            break
            time.sleep(0.5)
except:
    ser.close()
#print int('656C6C', base=16)
