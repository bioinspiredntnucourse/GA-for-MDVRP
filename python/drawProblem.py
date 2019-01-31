"""
INPUT STRUCTURE

problem_file_name
result_file_name

"""


import sys
import matplotlib.pyplot as plt
import numpy as np

inputlength = 2

if len(sys.argv) != inputlength + 1:
    print("no given input")
    exit(-1)

#look in the data files folders if only a filename is given
problemFileName = "../data_files/Data Files/" + sys.argv[1] if "/" not in sys.argv[1] else sys.argv[1]
resultFileName = "../data_files/Solution Files/" + sys.argv[2] if "/" not in sys.argv[2] else sys.argv[2]

depotsCoords = [] #array of tuples
customersCoords = [] #array of tuples

vehiclePaths = [] #index in depots for first and last element, index in customerCoords for inbetween

fileo = open(problemFileName)
[maxVehicles, customerCount, depotCount] = fileo.readline().split(' ')
depotsCoords = fileo.readlines()[-4:]

print(depotsCoords)