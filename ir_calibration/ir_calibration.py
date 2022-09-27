import serial

arduino_port = "/dev/ttyACM0"
baud_rate = 9600
serial_port = serial.Serial(arduino_port, baud_rate, timeout=1)


while True:

  lineOfData = serial_port.readline().decode()

  if len(lineOfData) > 0:
  
    print(lineOfData)
