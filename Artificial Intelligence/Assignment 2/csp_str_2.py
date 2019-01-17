#Onat Şahin - 150150129 - sahino15@itu.edu.tr
#In this code, python-constraint module is used which should be installed. I used Python 3.
#Link to the module: https://pypi.org/project/python-constraint/

#The code also imports block_construction_constraint.py that I wrote, which includes
#the Block class and constraint functions I used for my csp model.

#This is the code for the second structure in the question

from constraint import *
from block_construction_constraint import *

if __name__== "__main__":

    #Add blocks of the second structure to the blocklist in "block_construction_constraint.py"
    #Details of the block class can be seen in that file

    blocklist.append(Block('h', [(7,3), (7,4), (7,5), (7,6), (7,7), (7,8)], [(7,3), (7,4), (7,5), (7,6), (7,7), (7,8)])) #variable a
    blocklist.append(Block('v', [(6,3), (6,4)], [(4,3), (4,4)])) #variable b
    blocklist.append(Block('v', [(6,7), (6,8)], [(4,7), (4,8)])) #variable c
    blocklist.append(Block('h', [(3,0), (3,1), (3,2), (3,3), (3,4), (3,5)], [(3,0), (3,1), (3,2), (3,3), (3,4), (3,5)])) #variable d
    blocklist.append(Block('h', [(3,6), (3,7), (3,8), (3,9), (3,10), (3,11)], [(3,6), (3,7), (3,8), (3,9), (3,10), (3,11)])) #variable e
    blocklist.append(Block('v', [(2,0), (2,1)], [(0,0), (0,1)])) #variable f
    blocklist.append(Block('v', [(2,10), (2,11)], [(0,10), (0,11)])) #variable g

    problem = Problem(BacktrackingSolver()) #Select backtracking algorithm to solve the problem

    #Add variables to the problem giving them names and domains
    #Domain is 1-7 because there are 7 blocks in this structure

    problem.addVariable("a", [1,2,3,4,5,6,7]) #Every variable corresponds to the block that is in the same index in blocklist
    problem.addVariable("b", [1,2,3,4,5,6,7])
    problem.addVariable("c", [1,2,3,4,5,6,7])
    problem.addVariable("d", [1,2,3,4,5,6,7])
    problem.addVariable("e", [1,2,3,4,5,6,7])
    problem.addVariable("f", [1,2,3,4,5,6,7])
    problem.addVariable("g", [1,2,3,4,5,6,7])

    problem.addConstraint(AllDifferentConstraint()) #Add a constraint to make each variable's value unique

    #Add a constraint that uses the is_order_valid function in "block_construction_constraint.py" to satisfy
    #the constraints given in the question and send every variable's value to the function
    problem.addConstraint(FunctionConstraint(is_order_valid), ("a","b","c","d","e","f","g"))

    solutions = problem.getSolutions() #Get solutions with every block's placement order and print them

    for solution in solutions:
        print(solution)

print("Number of solutions: ", len(solutions))
