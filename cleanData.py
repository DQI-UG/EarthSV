import os
path=os.getcwd()
pathData=path + "/Data_test"
listOfFiles=os.listdir(pathData)
for file in listOfFiles:
    if(listOfFiles.count(file.split('.')[0]+'.xml') and listOfFiles.count(file.split('.')[0]+'.mseed')):
        print(file.split('.')[0])
    elif(listOfFiles.count(file.split('.')[0]+'.xml')): 
        os.remove(file.split('.')[0]+'.xml')
    elif(listOfFiles.count(file.split('.')[0]+'.mseed')): 
        os.remove(file.split('.')[0]+'.mseed')