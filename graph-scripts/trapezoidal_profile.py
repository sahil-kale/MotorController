import math


def motion_profile(vel, accel, distance, increment):
    #calculating time segments based on math in the notes
    tb=distance/vel - 1/accel
    ta=vel/accel

    vels = []
    times = []
    x = 0.0

    if ta*vel > distance:
       #calculating a new ta
       ta = math.sqrt(distance/accel)

       #first section of triangle
       while x <= ta:
           vels.append(x*accel)
           times.append(x)
           x = x + increment
       #second section of triangle 
       while x <= 2*ta:
           vels.append((x-2*ta)*-accel)
           times.append(x)
           x = x + increment

       print(ta*2)
       print(ta*accel)
       return vels, times 

    #first triangle 0->ta
    while x < ta:
       vels.append(x*accel)
       times.append(x)
       x = x + increment
    #rectange section ta-> ta+tb
    while x < ta+tb:
       vels.append(vel)
       times.append(x)
       x = x + increment
    #second triangle ta+tb->ta+tb+tc
    while x <= 2*ta + tb:
       vels.append((x - 2*ta - tb)*-accel)
       times.append(x)
       x = x + increment

    return vels, times

import matplotlib
import matplotlib.pyplot as plt 
import numpy as np

dist = 2
vel = 3
accel = 1
inc = 0.001 #this is like resolution

#calling profile generation algorithm
y,x = motion_profile(vel, accel, dist, inc)

#plotting
fig, ax = plt.subplots()
ax.plot(x,y)

#plt.xticks(x)

ax.set(xlabel="time(s)", ylabel="vel unit/s", title="triangle motion profile")
ax.grid()

plt.show()
