import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from math import sin
import time


seconds = time.time()

f= open("output.txt","r")
if f.mode == 'r':
    contents =f.readlines()

Processes = contents[1]
Duration = contents[0]
Processes = Processes.strip()
Processes = Processes.rstrip()
Processes = Processes.lstrip()

Duration = Duration.strip()
Duration = Duration.rstrip()
Duration = Duration.lstrip()




Processes = Processes.split(" ")
Duration = Duration.split(" ")

for i in range(len(Processes)):
    Processes[i] = float(Processes[i])

for i in range(len(Duration)):
    Duration[i] = float(Duration[i])


seed = abs(sin(time.localtime(seconds).tm_sec/60*180))
plt.figure(figsize=(30,30))
plt.ylabel('Processes Id')
plt.xlabel('Time')
plt.step(Duration, Processes , color="black", alpha = 0)
plt.axis([0,max(Duration)+10,0,max(Processes)+1])
plt.xticks(np.arange(0,max(Duration)+10,5))
plt.yticks(np.arange(0,max(Processes)+2,1))
plt.fill_between(Duration,Processes , color="black", alpha = 1)
# plt.plot(Duration, Processes, 'C0o', alpha=0.5)
plt.show()
