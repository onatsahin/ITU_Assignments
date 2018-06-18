def kruskal(graph):
    graph.edgeList.sort(reverse=True) #Sorting with nlogn according to the weights
    NodeCount = len(graph.adjMatrix)

    mstList = []                        #List that will hold final minimum spanning tree
    mstAdj = [[0]*NodeCount for i in range(NodeCount)] #Adjacency matrix

    edgeCounter = 0

    while edgeCounter < NodeCount-1:    #While all nodes are not in minimum spanning tree
        cur = graph.edgeList.pop()

        if cycleDetection(mstAdj,cur): #If edge will create cycle then don't add to mst
            continue

        edgeCounter+=1
        mstList.append(cur)

    return mstList

#For cycle detection we used depth first search in graph.
def cycleDetection(mstAdjList,currentEdge):
    mstAdjList[currentEdge[1]][currentEdge[2]] = 1
    mstAdjList[currentEdge[2]][currentEdge[1]] = 1

    visited =[False for i in range(len(mstAdjList))]
    stack = []

    tmp = -1
    stack.append((currentEdge[1],-1))   #Stack is used for depth first search implementation.
    while(len(stack) != 0):
        tmp = stack.pop()
        visited[tmp[0]] = True
        for i in range(len(mstAdjList)):
            if mstAdjList[tmp[0]][i] == 1:
                if visited[i] == True and tmp[1] != i:     # If this node don't have any connection to the mst
                    mstAdjList[currentEdge[1]][currentEdge[2]] = 0
                    mstAdjList[currentEdge[2]][currentEdge[1]] = 0

                    return True
                if visited[i] == False:                   # If node never visited before add to the stack
                    stack.append((i,tmp[0]))
    return False



def prim(graph):
    NodeCount = len(graph.adjMatrix)
    mstSet    = [0]                 #Nodes in the mst with assuming 1 node in the mst set
    mstNotSet = [i for i in range(1,NodeCount)] #Nodes that are not in mst starts with all nodes except 1
    mst = []
    while len(mstNotSet) != 0:      #While minimum spanning tree doesn't cover all nodes
        min = 10e9
        minEdge = (-1,-1)           #Undefined edge for initialization
        for i in mstSet:
            for j in mstNotSet:
                if graph.adjMatrix[i][j] == 1:
                    if graph.weightMatrix[i][j] < min:  #If this edge weight is minimum then make this as new minumum edge
                        min = graph.weightMatrix[i][j]
                        minEdge = (i,j)
        mstSet.append(minEdge[1])
        mstNotSet.remove(minEdge[1])
        mst.append( (min,minEdge[0],minEdge[1]))

    return mst
