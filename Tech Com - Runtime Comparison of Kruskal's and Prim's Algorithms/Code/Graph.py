import random

class Graph():
    adjMatrix    = []   #Matrix that holds edges between nodes
    weightMatrix = []   #Matrix that holds weights of edges
    edgeList     = []   #Different representation of the edges for sorting

    def __init__(self, adj,weight):
        self.adjMatrix = adj
        self.weightMatrix = weight
        row = len(self.adjMatrix)
        col = len(self.adjMatrix[0])
        for i in range(row):
            for j in range(i,row):
                if self.adjMatrix[i][j] == 1:
                    self.edgeList.append((self.weightMatrix[i][j],i,j))

# This function write all edges to the file from given adjMatrix.
# First line gives number of the nodes of the each graphs in dataset.
# Each line represent one graph's adjacency matrix
    def writeToFile(self,filename):
        file = open(filename,"a")
        file.write(str(len(self.adjMatrix))+"\n")
        tmp = ""
        for i in self.adjMatrix:
            for j in i:
                tmp+= str(j) + " "
        tmp += "\n"
        file.write(tmp)
        tmp = ""
        for i in self.weightMatrix:
            for j in i:
                tmp+= str(j) + " "
        tmp += "\n"
        file.write(tmp)
        file.close()




def readFromFile(filename):
    dataset = []
    with open(filename,"r") as file:

        while True:
            list = [file.readline() for i in range(3)]
            if not list[0]:
                break
            list = [line.strip('\n') for line in list]
            Node = int(list[0])
            adjLine = list[1].split(" ")
            adjLine.pop()
            weightLine = list[2].split(" ")
            weightLine.pop()
            adjM    = [[0]*Node for i in range(Node)]
            weightM = [[0]*Node for i in range(Node)]
            i = 0
            for j in range(len(adjLine)):
                if j%Node == 0 and j!=0:
                    i+=1

                adjM[i][j%Node] = int(adjLine[j])
                weightM[i][j%Node] = int(weightLine[j])

            dataset.append(Graph(adjM,weightM))
    return dataset

# This function creates randomly connected and weighted graphs with ensuring the
# density is same with given density as argument.
# Basic idea is first connect each node one by one to the each other, it ensures connectivity.
# Then until density is satisfied, connect each nodes to the another that chosen randomly.
def graphGenerator(Node,Density):
    weightMatrix = [[0]*Node for i in range(Node)]
    adjMatrix    = [[0]*Node for i in range(Node)]

    for i in range(1,Node):
        j=random.randint(0,i-1)
        adjMatrix[i][j] = 1
        adjMatrix[j][i] = 1
        weightMatrix[i][j] = random.randint(1,100)
        weightMatrix[j][i] = weightMatrix[i][j]


    while getDensity(adjMatrix) < Density:
        flag=False
        while not flag:
            i = random.randint(0,Node-1)
            j = random.randint(0,Node-1)
            if adjMatrix[i][j] == 0 and i!=j:
                adjMatrix[i][j] = 1
                adjMatrix[j][i] = 1
                weightMatrix[i][j] = random.randint(1,100)
                weightMatrix[j][i] = weightMatrix[i][j]
                flag = True

    return Graph(adjMatrix,weightMatrix)

def getDensity(adjMatrix):
    node = len(adjMatrix)
    maxEdge = node*(node-1)/2

    edgeCounter = 0
    for i in range(node):
        for j in range(i,node):
            if adjMatrix[i][j] == 1:
                edgeCounter += 1

    return edgeCounter/maxEdge
