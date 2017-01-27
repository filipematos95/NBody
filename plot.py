import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("data2.txt")
n = 100
plt.plot(data[:,1],data[:,2],color="yellow")
plt.plot(data[:,3],data[:,4],color="red")
i = 5
while i < (n*2+5):
	plt.plot(data[:,i],data[:,i+1],color="green")
	i+=2


#plt.scatter(data[1,1],data[1,2],color="k")

plt.gca().set_aspect('equal')
plt.show()