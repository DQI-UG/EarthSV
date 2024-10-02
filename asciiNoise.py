#the following part of code clears out headers(text) from .ascii files and creates the file dataNoise.ascii file
import os
path=os.getcwd()
pathAsciiFolder=path+"/Data_ascii"
pathFileOut=path+"/Data_noise_ascii"+'/'+'dataNoise.ascii'
if not os.path.exists(pathAsciiFolder):
    os.mkdir(pathAsciiFolder)
if os.path.exists(pathFileOut):
    os.remove(pathFileOut)
data_processed_files=os.listdir(pathAsciiFolder)
fileOut = open(pathFileOut, "a")
for file in data_processed_files:
    pathToFiles=pathAsciiFolder+'/'+file
    data=open(pathToFiles, "r")
    lines = data.readlines()
    for line in lines[1:]:
        dataPure=line.split()[1]
        print(dataPure, file=fileOut)
    data.close()
print('dataNoise.ascii file has been created in the folder '+pathFileOut)
fileOut.close()