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
class _Getch:
    """Gets a single character from standard input.  Does not echo to the
screen."""
    def __init__(self):
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self): return self.impl()


class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


class _GetchWindows:
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getch()


getch = _Getch()

import serial
import time
ser = serial.Serial('COM10', 9600)
time.sleep(0.8)
i = 0
while 1:
    if getch() == 'l' and i<100:
        i+=1
    if getch() == 'k' and i>0:
        i+=-1
    ser.write(str(i)+NEWLINE)
    time.sleep(0.05)
ser.write(str(0)+NEWLINE)

# while 1:
#     # noinspection PyBroadException
#     try:
#         var = raw_input("Enter on or off: ")
#         if var == 'on':
#             ser.write('O')
#         elif var == 'off':
#             ser.write('C')
#         time.sleep(0.3)
#     except:
#         print('Data could not be read')
