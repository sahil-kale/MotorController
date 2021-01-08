def motion_profile(vel, accel, jerk, distance, increment):

    if distance < 0:
        vel = -vel 
        accel = -accel
        jerk = -jerk
    ta = accel / jerk
    tb = (vel - ta*accel) / accel
    

    vels = []
    accels = []
    times = []
    x = 0.0
    lastVel = 0.0 
    while x <= ta:
        vels.append((jerk * x)*x/2)
        accels.append(jerk * x)
        times.append(x)
        x += increment
    lastVel = jerk*ta*ta/2
    while  x <= tb + ta:
        vels.append(jerk*(x-ta)+lastVel)
        accels.append(accel)
        times.append(x)
        x += increment
    lastVel = lastVel + jerk*tb
    while x <= tb+ta+ta:
        vels.append(((x-ta-tb-ta)*-jerk)*(x-ta-tb-ta)/2 + jerk*ta*ta/2 + lastVel)
        accels.append((x-ta-tb-ta)*-jerk)
        times.append(x)
        x += increment

    return vels,times,accels

import matplotlib
import matplotlib.pyplot as plt 
import numpy as np

dist = -20
vel = 5
accel = 2
jerk = 1.5
inc = 0.001 #this is like resolution
y,x,a = motion_profile(vel, accel, jerk, dist, inc)
#x = np.arange(0.0,time, inc)

fig, ax = plt.subplots()
ax.plot(x,y)
ax.plot(x,a)

plt.legend(["vel","accel"])
#plt.xticks(x)

ax.set(xlabel="time(s)", ylabel="vel unit/s", title="triangle motion profile")
ax.grid()

plt.show()
