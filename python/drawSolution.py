"""
INPUT STRUCTURE

problem_file_name
result_file_name

"""


import sys
import matplotlib.pyplot as plt
import numpy as np

def main():
    inputlength = 2

    if len(sys.argv) != inputlength + 1:
        print("invalid input")
        exit(-1)

    #look in the data files folders if only a filename is given
    problemFileName = "../data_files/Data Files/" + sys.argv[1] if "/" not in sys.argv[1] else sys.argv[1]
    solutionFilename = "../data_files/Solution Files/" + sys.argv[2] if "/" not in sys.argv[2] else sys.argv[2]

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
    paths = getPaths(solutionlines, depotsCoords, customersCoords)
    for path in paths:
        plt.plot([x[0] for x in path], [x[1] for x in path], 'y')

    #PRINT STUFF
    print("fitness:", fitness)
    #print("depot coords: ", depotsCoords)
    #print("customer coords: ", customersCoords)
    print("depotCount: ", len(depotsCoords))
    print("customerCount: ", len(customersCoords))
    #print("paths", paths)

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

    for line in solutionlines:
        lineVals = line.split()

        path = []

        startDepot = int(lineVals[0])
        endDepot = int(lineVals[4])
        customers = [int(x) for x in lineVals[5:]]

        path.append(depotsCoords[startDepot-1]) #append start depot coordinates

        for customer in customers:
            path.append(customersCoords[customer-1]) #customer coords

        path.append(depotsCoords[endDepot-1]) #end depot coordinates
        paths.append(path)
    return paths

main()