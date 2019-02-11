"""
INPUT STRUCTURE

problem_file_name
result_file_name

"""


import sys
import matplotlib.pyplot as plt
import matplotlib
import numpy as np

#matplotlib.use("wx")
from pylab import *

#plt = matplotlib.pyplot;



def main():
    inputlength = 2

    if len(sys.argv) != inputlength + 1:
        print("invalid input")
        exit(-1)

    #look in the data files folders if only a filename is given
    problemFileName = "../data_files/Data Files/" + sys.argv[1] if ("/" not in sys.argv[1] and "\\" not in sys.argv[1]) else sys.argv[1]
    solutionFilename = "../data_files/Solution Files/" + sys.argv[2] if ("/" not in sys.argv[2] and "\\" not in sys.argv[2]) else sys.argv[2]

    print("problemFilename: "+problemFileName + " solutionFilename: " + solutionFilename)


    #LOAD DATA FROM FILES
    fileo = open(problemFileName)
    [maxVehicles, customerCount, depotCount] = [int(x) for x in fileo.readline().split(' ')]
    filelines = fileo.readlines()
    fileo.close()

    fileo = open(solutionFilename)
    fitness = float(fileo.readline())
    solutionlines = fileo.readlines()
    fileo.close()

    #PLOT DEPOTS AND CUSTOMERS
    depotsCoords = getDepotCoords(filelines, depotCount)
    customersCoords = getCustomerCoords(filelines, depotCount, customerCount)

    plt.plot([x[0] for x in depotsCoords], [x[1] for x in depotsCoords], 'ro')
    plt.plot([x[0] for x in customersCoords], [x[1] for x in customersCoords], 'bo')



    #PLOT PATHS
    paths, depotIds = getPaths(solutionlines, depotsCoords, customersCoords)

    hsv = plt.get_cmap('hsv')
    colors = hsv(np.linspace(0, 1.0, len(depotsCoords)))


    for path, depotId in zip(paths, depotIds):
        if len(path) > 2:
            plt.plot([x[0] for x in path], [x[1] for x in path], color=colors[depotId-1])

    #PRINT STUFF
    print("fitness:", fitness)
    #print("depot coords: ", depotsCoords)
    #print("customer coords: ", customersCoords)
    print("depotCount: ", len(depotsCoords))
    print("customerCount: ", len(customersCoords))
    #print("paths", paths)

    plt.title(solutionFilename + "\nfitness: " + str(fitness))

    mngr = get_current_fig_manager()
    mngr.window.setGeometry(5, 50, 640, 545)
    plt.show()


def getDepotCoords(problemFileLines, depotCount):
    # get the lines with depot coordinate info
    depotCoordLines = problemFileLines[-depotCount:]
    # split the lines and retrieve coloumn 1 and 2 with coordinate info. Then convert coordinates to int
    depotsCoords = [[int(y) for y in x.split()[1:3]] for x in depotCoordLines]
    # result like this: [[20, 20], [30, 40], [50, 30], [60, 50]]
    return depotsCoords

def getCustomerCoords(problemFileLines, depotCount, customerCount):
    # get the lines with customer coordinate info
    customerCoordLines = problemFileLines[depotCount:depotCount + customerCount]
    # split the lines and retrieve coloumn 1 and 2 with coordinate info. Then convert coordinates to int
    customersCoords = [[int(y) for y in x.split()[1:3]] for x in customerCoordLines]
    # result like this: [[20, 20], [30, 40], [50, 30], [60, 50]]
    return customersCoords

def getPaths(solutionlines, depotsCoords, customersCoords):

    paths = []
    startDepots = []
    for line in solutionlines:
        lineVals = line.split()

        path = []

        startDepot = int(lineVals[0])
        endDepot = int(lineVals[4])
        customers = [int(x) for x in lineVals[5:]]

        path.append(depotsCoords[startDepot-1]) #append start depot coordinates
        startDepots.append(startDepot)

        for customer in customers:
            path.append(customersCoords[customer-1]) #customer coords

        path.append(depotsCoords[endDepot-1]) #end depot coordinates
        paths.append(path)
    return paths, startDepots

main()