import sys
import matplotlib.pyplot as plt
import numpy as np

if len(sys.argv) < 2:
    print("no given input")
    exit(-1)

data = [float(x) for x in sys.argv[1].split(",")]
x = np.arange(0, len(data), 1)
y = data
plt.plot(x, y)

plt.show()