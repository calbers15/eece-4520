# pyserial-test.py
# test serial communication with Arduino
#
# require pip install pyserial
#
# Usage: python3 pyserial-test.py
#
# yluo
#
import serial 

# serial port dev file name
# need to change based on the particular host machine
serialDevFile = 'COM3'
ser=serial.Serial('COM3', 9600, timeout=1)

while True:
    line = ser.readline()
    decodeLine = line.decode('utf-8')
    print(decodeLine)
    #ser.write(b'E')
