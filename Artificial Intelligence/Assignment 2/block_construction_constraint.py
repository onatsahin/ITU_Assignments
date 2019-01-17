#Onat Şahin - 150150129 - sahino15@itu.edu.tr

#This code include the Block class and the constraint function that is used for the csp problem.
#This code is imported from csp_str_1.py and csp_str_2.py which create the model and solve the problem.

blocklist = [] #A list that holds block objects. Filled in the other codes.

class Block: #Block class to define blocks
    def __init__(self, orientation, top, bottom):
        self.orientation = orientation  #Vertical of horizontal
        self.top = top  #Top part of the block in coordinates (block itself if horizontal)
        self.bottom = bottom #Bottom part of the block in coordinates (block itself if horizontal)

#For the coordinates, I assumed that the height of a horizontal block is 1 and its width is 6.
#The height of a vertical block is 3 and its width is 2. I put the whole structure in a coordinate system
#where left and downmost point of the structure is the point 0,0

def horizontal_center_check(block, placed): #Checks if the below of a horizontal block's center is filled
    return ( (block[2][0] - 1, block[2][1]) in placed ) and ( (block[3][0] - 1, block[3][1]) in placed )

def horizontal_two_over_three_check(block, placed): #Checks if at least 2/3 of a horizontal block's below is filled
    count = 0
    for piece in block:
        if (piece[0] - 1, piece[1]) in placed:
            count += 1

    return count >= (len(block) / 3 * 2)

def vertical_bottom_check(block_bottom, placed): #Checks if a vertical block's below is filled
    return ((block_bottom[0][0]-1, block_bottom[0][1]) in placed) and ((block_bottom[1][0]-1, block_bottom[1][1]) in placed)

#The function below uses the functions above to implement the constraints given in the assignment. Every variable's value
#comes to this function in argv list. The order of this list corresponds to the order of blocks in blocklist
def is_order_valid(*argv):
    block_count = len(argv)
    list_to_check = []

    for i in range(block_count): #For every block

        if blocklist[i].bottom[0][0] == 0: #If a block touches the ground, continue since it satisfies the constraints
            continue

        del list_to_check[:] #clear the checklist

        for j in range(block_count):
            if argv[j] < argv[i]:  #If a block j is placed before the block i, add block j to the checklist
                list_to_check = list_to_check + blocklist[j].top

        if blocklist[i].orientation == 'h': #Perform horizontal check if the block i is horizontal
            if not (horizontal_center_check(blocklist[i].bottom, list_to_check) or horizontal_two_over_three_check(blocklist[i].bottom, list_to_check)):
                return False

        elif blocklist[i].orientation == 'v': #Perform vertical check if the block i is vertical
            if not vertical_bottom_check(blocklist[i].bottom, list_to_check):
                return False

    return True #If no False is returned, the structure can be built with the given order. Return True.
