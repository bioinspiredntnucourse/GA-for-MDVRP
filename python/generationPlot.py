import sys
import matplotlib.pyplot as plt
import numpy as np

"""
input:
bestGen1,bestGen2, ...
"""

def main():
    inputlength = 1

    if len(sys.argv) != inputlength + 1:
        print("invalid input")
        exit(-1)
genTopFile = sys.argv[1]

fileo = open(genTopFile)
content = fileo.read()
genTops = [float(x) for x in content.split(",")]

plt.plot(genTops)
plt.show()