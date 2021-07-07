import glob, os
os.chdir(".")
for file in glob.glob("*.c"):
    print(file)