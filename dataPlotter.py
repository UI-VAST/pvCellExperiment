# -*- coding: utf-8 -*-
"""
Created on Thu Jan 13 19:51:50 2022

@author: Malachi
"""


import matplotlib.pyplot as plt
import pandas as pd
import os

directory = r"C:\Users\Malachi\OneDrive - University of Idaho\VAST\OUR GRANT\pvCellExperiment"
file = 'pvData.csv'
markerSize = .5

#read pv Experiment Data File
data = pd.read_csv(os.path.join(directory,file))
t = data['Time(s)']
v = data['Voltage(mV)'] / 1000 #volts
i = data['Current(mA)'] / 1000 #amps
solar = data['solar']
temp = data['Temp(C)']

#sondData = pd.

#power measured
P = i * v      #watts


fig, ax1 = plt.subplots()
ax1.set_xlim([0,10500])

color = 'tab:red'
ax1.set_xlabel('Time (s)')
ax1.set_ylabel('Temperature (C)', color=color)
ax1.plot(t, temp, color=color)
ax1.tick_params(axis='y', labelcolor=color)

ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis

color = 'tab:blue'
ax2.set_ylabel('Solar Irradiance (W/m^2)', color=color)  # we already handled the x-label with ax1
ax2.scatter(t, solar, color=color, s=markerSize)
ax2.tick_params(axis='y', labelcolor=color)

fig.tight_layout()  # otherwise the right y-label is slightly clipped
plt.show()

### Voltage, Current, Power Plots
fig2, ax3 = plt.subplots()
ax3.set_xlim([0,10500])

color = 'tab:red'
ax3.set_xlabel('Time (s)')
ax3.set_ylabel('Voltage (V)', color=color)
ax3.plot(t, v, color=color)
ax3.plot(t,P, color='Green')
ax3.tick_params(axis='y', labelcolor=color)

ax4 = ax3.twinx()  # instantiate a second axes that shares the same x-axis

color = 'tab:blue'
ax4.set_ylabel('Current (Amps)', color=color)  # we already handled the x-label with ax1
ax4.scatter(t, i, color=color, s=markerSize)
ax4.tick_params(axis='y', labelcolor=color)

fig2.tight_layout()  # otherwise the right y-label is slightly clipped
plt.show()

