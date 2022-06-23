import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

    # Creates dictionary, fills with data from file, and returns dictionary
def CreateGrocDict():
    dict = {}
    file = open("InputFile.txt", "r")
    for line in file:
        line = line.strip()
        if line in dict:
            dict[line] = dict[line] + 1 # Updates the count of specific items for each occurance in file
        else:
            dict[line] = 1 # If specific item is not in the dictionary it is added and the value is set to 1
    file.close()
    return dict

    # Outputs the contents of input file
def PrintItemsPurchased():
    dict = CreateGrocDict() # dict is assigned with a dictionary created by the CreateGrocDict function
    print("{:~<64}+".format("+"))
    print("|{:^63}|".format("List of Items Purchased"))
    print("{:~<64}+".format("+"))
    print("{:-<64}+".format("+"))
    print("|{:^31}|{:^31}|".format("Item", "Quantity"))
    print("{:-<64}+".format("+"))

    # Iterates through dict, formats, and outputs data
    for key, value in dict.items():
        print("| {:<30}| {:<30}|".format(key, value))
        print("{:-<64}+".format("+"))
    return

    # Checks if variable item is in file
def CheckIfItemInList(item):
    item_count = 0
    file = open("InputFile.txt", "r")

    # Iterates through file looking for variable item. If item is found updates variable item_count. Returns item_count value.
    for line in file:
        line = line.strip()
        if item == line:
            item_count += 1;
    file.close()
    return item_count

    # Creates a file with the values from dict.
def CreateListFile():
    file = open("frequency.dat", "w") # Creating file
    dict = CreateGrocDict() # dict is assigned with a dictionary created by the CreateGrocDict function
    
    # Iterates through dict, formats, and writes to file
    for key, value in dict.items():
        file.write("{}: {}\n".format(key,value))
    file.close()
    return