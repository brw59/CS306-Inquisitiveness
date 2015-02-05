import random, sys

randfile = open("in/reverse-" + sys.argv[1] + ".txt", "w" )

# for i in range(int(input('How many to generate?: '))):
    
for i in reversed(range(int(sys.argv[1]))):
    
    line = str(i) + "\n"
    randfile.write(line)
#    print(line)

randfile.close()
