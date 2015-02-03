import random, sys

randfile = open("Randomnm" + sys.argv[1] + ".txt", "w" )

# for i in range(int(input('How many to generate?: '))):
    
for i in range(int(sys.argv[1])):
    
    line = str(random.randint(1, 50000)) + "\n"
    randfile.write(line)
#    print(line)

randfile.close()