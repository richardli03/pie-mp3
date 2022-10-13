"""
Accept and clean serial data from the Arduino, then plot the IR sensor
readings with the motor torque requests.
"""

import serial
import csv
import pandas as pd
import matplotlib.pyplot as plt

FIELD_NAMES = ["l_m","r_m", "l_ir", "r_ir"]

# IR_SENSOR_PORT = "/dev/ttyACM1"
# BAUD_RATE = 9600
# serial_port = serial.Serial(IR_SENSOR_PORT, BAUD_RATE, timeout=1)

def add_data(data,path):
    """
    Given a string of data over Serial, add it to the appropriate column
    in the csv

    Args:
        data (str): a string of 4 numbers separated by spaces
        path (str): the path to the datafile that this data will be written to
    """
    
    split_data = data.split(" ")
    print(split_data)
    
    with open(f"{path}.csv","a") as f:
        writer = csv.DictWriter(f, fieldnames = FIELD_NAMES)
        new_entry = {"l_m" : split_data[0], "r_m" : split_data[1],
                     "l_ir" : split_data[2], "r_ir": split_data[3]}
        writer.writerow(new_entry)
       
        
def visualize(path):
    """
    Visualize the data in a csv

    Args:
        path (str): path to the datafile we want visualized
    """
    display = pd.read_csv(f"{path}.csv")
    display.columns = ["l_m","r_m","l_ir","r_ir"]
    display.plot()
    plt.show()
        
def main(path):
    """
    Run the main data collection and visualization pipeline

    Args:
        path (str): path to the csv where this data will be stored
    """
    
    # Clear the csv
    with open(f"{path}.csv", "w") as f:
        f.truncate() 
    # starting = False_description_
    # while starting is False:
    #     data = serial_port.readline().decode()
    #     if len(data) > 0:
    #         if data == "starting\r\n":
    #             starting = True
    i = 0
    while True:         
        i += 10
        data = f"{2*i} {10+i} {30+i} {50+i}"
        # data = serial_port.readline().decode()
        if len(data)>0:
            add_data(data, path)
    
    visualize(path)
            
if __name__ == "__main__":
    main("display")