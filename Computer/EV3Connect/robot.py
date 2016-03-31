import serial
import time
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

ser = serial.Serial('COM10', 9600)
time.sleep(2)
while(1):
    if ser.in_waiting:
        print ser.in_waiting, int(ser.read(ser.in_waiting).encode('hex'),base=16)
        time.sleep(0.5)
#print int('656C6C', base=16)
