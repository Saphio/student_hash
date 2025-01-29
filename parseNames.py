## fin = open ("first.txt", "r")
## fout = open ("fnames.txt", "w")

fin = open ("last.txt", "r") ## not a file in this repository
fout = open ("lnames.txt", "w") 

lines = fin.readlines();

print("starting")

for i in range(200):
    line = lines[i].split(" ")[0].lower()
    fout.write(line[0].upper() + line[1:] + "\n")

print("done")
