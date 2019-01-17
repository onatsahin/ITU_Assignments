#Onat Şahin - 150150129 - sahino15@itu.edu.tr
#In this code, python-constraint module is used which should be installed. Also, I used Python 3
#Link to the module: https://pypi.org/project/python-constraint/

#The code also imports block_construction_constraint.py that I wrote, which includes
#the Block class and constraint functions I used for my csp model.

#This is the code for the first structure in the question

from constraint import *
from block_construction_constraint import *

if __name__== "__main__":

    #Add blocks of the first structure to the blocklist in "block_construction_constraint.py"
    #Details of the block class can be seen in that file

    blocklist.append(Block('h', [(5,5), (5,6), (5,7), (5,8), (5,9), (5,10)], [(5,5), (5,6), (5,7), (5,8), (5,9), (5,10)])) #variable a
    blocklist.append(Block('h', [(4,2), (4,3), (4,4), (4,5), (4,6), (4,7)], [(4,2), (4,3), (4,4), (4,5), (4,6), (4,7)])) #variable b
    blocklist.append(Block('h', [(4,8), (4,9), (4,10), (4,11), (4,12), (4,13)], [(4,8), (4,9), (4,10), (4,11), (4,12), (4,13)])) #variable c
    blocklist.append(Block('v', [(3,2), (3,3)], [(1,2),(1,3)])) #variable d
    blocklist.append(Block('h', [(3,4), (3,5), (3,6), (3,7), (3,8), (3,9)], [(3,4), (3,5), (3,6), (3,7), (3,8), (3,9)])) #variable e
    blocklist.append(Block('h', [(3,10), (3,11), (3,12), (3,13), (3,14), (3,15)], [(3,10), (3,11), (3,12), (3,13), (3,14), (3,15)])) #variable f
    blocklist.append(Block('h', [(0,0), (0,1), (0,2), (0,3), (0,4), (0,5)], [(0,0), (0,1), (0,2), (0,3), (0,4), (0,5)])) #variable g
    blocklist.append(Block('v', [(2,6), (2,7)], [(0,6),(0,7)])) #variable h
    blocklist.append(Block('v', [(2,12), (2,13)], [(0,12),(0,13)])) #variable i

    problem = Problem(BacktrackingSolver())  #Select backtracking algorithm to solve the problem

    #Add variables to the problem giving them names and domains
    #Domain is 1-9 because there are 9 blocks in this structure

    problem.addVariable("a", [1,2,3,4,5,6,7,8,9]) #Every variable corresponds to the block that is in the same index in blocklist
    problem.addVariable("b", [1,2,3,4,5,6,7,8,9])
    problem.addVariable("c", [1,2,3,4,5,6,7,8,9])
    problem.addVariable("d", [1,2,3,4,5,6,7,8,9])
    problem.addVariable("e", [1,2,3,4,5,6,7,8,9])
    problem.addVariable("f", [1,2,3,4,5,6,7,8,9])
    problem.addVariable("g", [1,2,3,4,5,6,7,8,9])
    problem.addVariable("h", [1,2,3,4,5,6,7,8,9])
    problem.addVariable("i", [1,2,3,4,5,6,7,8,9])

    problem.addConstraint(AllDifferentConstraint()) #Add a constraint to make each variable's value unique

    #Add a constraint that uses the is_order_valid function in "block_construction_constraint.py" to satisfy
    #the constraints given in the question and send every variable's value to the function
    problem.addConstraint(FunctionConstraint(is_order_valid), ("a","b","c","d","e","f","g","h","i"))

    solutions = problem.getSolutions() #Get solutions with every block's placement order and print them

    for solution in solutions:
        print(solution)

print("Number of solutions: ", len(solutions))
