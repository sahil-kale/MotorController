def motion_profile(dt, distance, increment):
    v_avg = distance/dt
    v_max = 2 * v_avg
    run = dt/2
    slope = v_max/run

    vels = []

    x = 0.0
    while x <= run:
        vels.append(x*slope)
        x = x + increment
    while x <= dt+increment:
        vels.append((x-dt)*-slope)
        x  = x + increment

    return vels

import matplotlib
import matplotlib.pyplot as plt 
import numpy as np

dist = -1.25
time = 0.75 #sec
inc = 0.001 #this is like resolution
x = np.arange(0.0,time+inc, inc)
y = motion_profile(time, dist, inc)

fig, ax = plt.subplots()
ax.plot(x,y)

#plt.xticks(x)

ax.set(xlabel="time(s)", ylabel="vel unit/s", title="triangle motion profile")
ax.grid()

plt.show()
