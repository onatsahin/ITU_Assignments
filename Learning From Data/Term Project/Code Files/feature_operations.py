#We have used these functions to clear our data.
from datetime import date,timedelta

def normalize(data):
    maxes = [0 for i in data[0]]
    mins = [10E9 for i in data[0]]

    for i in range(len(data)):
        for j in range(len(data[0])):
            if(data[i][j] > maxes[j]):
                maxes[j] = data[i][j]
            if(data[i][j] < mins[j]):
                mins[j] = data[i][j]

    for i in range(len(data)):
        for j in range(len(data[0])):
            data[i][j] = (data[i][j] - mins[j]) / (maxes[j] - mins[j] + 0.0001)

    return data
def map_size(sizeStr):
    if sizeStr == 'xs' or sizeStr == 'XS':
        return 101
    elif sizeStr == 'S' or sizeStr == 's':
        return 102
    elif sizeStr == 'm' or sizeStr == 'M':
        return 103
    elif sizeStr == 'l' or sizeStr == 'L':
        return 104
    elif sizeStr == 'xl' or sizeStr == 'XL':
        return 105
    elif sizeStr == 'XXL' or sizeStr == 'xxl':
        return 106
    elif sizeStr == 'XXL' or sizeStr == 'xxl':
        return 107
    elif sizeStr == 'XXXL' or sizeStr == 'xxxl':
        return 108
    elif sizeStr[len(sizeStr) -1] == '+':
        return int(sizeStr[0:(len(sizeStr)-1)])
    elif len(sizeStr) == 7:
        return 0
    elif len(sizeStr) == 4:
        return int(sizeStr[-2:])
    else:
        return int(sizeStr)

def find_index_of(arr,x):
    iter = 0
    for color in arr:
        if x == color:
            return iter
        iter += 1

def diff_two_date(order,deliver):
    orderStr = order.split('-')
    deliverStr = deliver.split('-')
    delta =  date(int(deliverStr[0]),int(deliverStr[1]),int(deliverStr[2])) - date(int(orderStr[0]),int(orderStr[1]),int(orderStr[2]))
    return delta.days

def makeDeliverAfter1Day(order):
    orderStr = order.split('-')
    day = date(int(orderStr[0]),int(orderStr[1]),int(orderStr[2]))
    day = day + timedelta(days=1)
    return str(day)

def map_ages(age):
    ageList = [10,20,30,40,50,60,70,80]
    for i in range(len(ageList)):
        if age < ageList[i]:
            return i
    return 8

def creationYear(date):
    parsed = date.split('-')
    if(parsed[0] == "2011"):
        return 1
    elif(parsed[0] == "2012"):
        return 2
    elif(parsed[0] == "2013"):
        return 3

def idProcess(data,index,strName):
    res = []

    for i in range(len(data)):
        num_of_returns = 0
        num_total = 0
        for j in range(len(data)):
            if int(data[i][index]) == int(data[j][index]):
                num_total += 1
            if int(data[i][index]) == int(data[j][index]) and int(data[j][13]) == 1:
                num_of_returns += 1
        res.append(num_of_returns / num_total)

    writeReturnNumByID(res,data,strName)
    return res

def writeReturnNumByID(res,data,strName):
    file = open(strName + ".txt","w")
    for i in range(len(res)):
        str_row = data[i][0] + ", "+ str(res[i]) + "\n"
        file.write(str_row)
    file.close()


def readReturnNum(strFile):
    file = open(strFile ,"r")
    data = [line.strip('\n') for line in file.readlines()]
    data = [line.split(',') for line in data]
    file.close()
    dataDict = {}
    for row in data:
        dataDict[row[0]] = row[1]
    return dataDict

def findValByIndex(data,id):
    for row in data:
        if id == row[0]:
            return row[1]
