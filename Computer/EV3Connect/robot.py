import serial
import time
import struct
from pprint import *
#
class Robot:
    def __init__(self, port):
        self.port = port

    def start_connection(self):
        self.robot = serial.Serial(self.port)
        print 'Starting serial port...'
        time.sleep(1)
        print 'OK'

    def receive_data(self):
        # try:
        data = []
        tmp = []
        while(not self.robot.in_waiting):
            time.sleep(0.05)
        # while(self.robot.in_waiting):
        #     data.append(ord(self.robot.read(1)))
        tmp = self.robot.read(self.robot.in_waiting)
        for i in range(len(tmp)):
            data.append(ord(tmp[i]))
        title_spot = 7
        title_size = data[title_spot-1]
        value_spot = title_spot+title_size+2
        title = ''
        for i in range(title_size-1):
            a = chr(data[title_spot + i])
            title += a
        value = bool(data[value_spot])
        return title,value
        # except:
        #     print 'ERROR OCCURED'
        #     self.robot.close()
        #     return -1, -1

    def send_data(self, title, value):
        tmp1 = []
        tmp1.insert(1, 0) #Second byte = useless
        tmp1.insert(2, 1) #<some_data>
        tmp1.insert(3, 0)
        tmp1.insert(4, 129)
        tmp1.insert(5, 158) #</some_data>
        tmp1.insert(12, 1) #Bool size
        tmp1.insert(13, 0)
        tmp2 = []
        title_spot = 7
        title_size = len(title) + 1
        value_spot = title_spot + title_size + 2
        tmp1.insert(0, 8 + title_size)
        tmp1.insert(6, title_size)
        lst = -1
        for i in range(title_size - 1):
            tmp1.insert(title_spot + i, title[i])
            lst = title_spot + i + 1
        tmp1.insert(lst, 0)
        tmp1.insert(value_spot, int(value))
        tmp2 = bytearray(tmp1)
        self.robot.write(tmp2)

    def stop(self):
        self.robot.close()

# try:
r = Robot('COM14')
r.start_connection()
t,v = r.receive_data()
time.sleep(0.3)
r.send_data(t, v)
