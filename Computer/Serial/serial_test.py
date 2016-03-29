import serial
import time
NEWLINE = '\n'

#ard = serial.Serial('COM10', 9600, timeout=0.2)
# c = raw_input()
# while c != '':
#     ard.write((c + NEWLINE).encode())
#     c = raw_input()
# print(ard.read(ard.in_waiting+1))
# ch = []
# i = 0
# for s in 'abc\n':
#     ch.insert(i,ord(s))
#     i += 1
# print ch
import serial
import time
ser = serial.Serial('COM10', 9600, timeout=0)
time.sleep(2)
while 1:
    # noinspection PyBroadException
    try:
        var = raw_input("Enter on or off: ")
        if var == 'on':
            ser.write('O')
        elif var == 'off':
            ser.write('C')
        time.sleep(0.3)
    except:
        print('Data could not be read')