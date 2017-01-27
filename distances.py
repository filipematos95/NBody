import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("distances2.txt")
plt.scatter(data[:,0],data[:,1])
#plt.hist(data,bins=20)
plt.show()