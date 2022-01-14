# -*- coding: utf-8 -*-
"""
Created on Thu Jan 13 18:42:25 2022

@author: Malachi
"""

import os
import pandas as pd
import matplotlib.pyplot as plt

directory = r"C:\Users\Malachi\OneDrive - University of Idaho\pvCellData"
header = ["Time(s)", "Voltage(mV)", "Current(mA)", "solar", "Temp(C)"]

contents = pd.DataFrame()
for file in os.listdir(directory):
    line = pd.read_csv(os.path.join(directory,file), header=None)
    print(line)
    contents = contents.append(line)

#save contents to csv
#add column names
contents.columns = header
contents = contents.apply(pd.to_numeric)
contents = contents.sort_values('Time(s)')
contents.to_csv('pvData.csv', index=False)
    
"Time, Voltage(mV), Current(mA), solar, temp(C)"

