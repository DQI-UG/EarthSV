import re
import datetime
try:
    file = open("gmap-stations.txt", "r")
    fileS=open("stations.txt", "w")
    minData=[datetime.date.today().year,datetime.date.today().strftime("%j")]
    maxData=[datetime.date.today().year,datetime.date.today().strftime("%j")]
    channels=[]
    locCodes=[]
    #while True:
    channel=input(f"Input channel symbols separated by comma: " ).upper().strip()
    channels=channel.split(",")
        #if channel not in(channels):
        #    print("Wrong channel")
        #else:
        #    break
    #while True:
    locCode=input(f"Input location codes separated by comma: ").strip()
    locCodes=locCode.split(',')
        #if locCode not in(lcodes):
        #    print("Wrong location code")
        #else:
        #    break
    stations=[]
    station=[]
    channelsCodes=[]
    for channel in channels:
        for locCode in locCodes:
            channelsCodes.append([channel,locCode])
    for x in file:
        file = open("gmap-stations.txt", "r")
        line = re.search("^[#\r\n]", x)
        if line:
            continue
        else:
            element=x.strip().split("|")
            beginData=datetime.date.fromisoformat(element[6].split("T")[0])
            endData=datetime.date.fromisoformat(element[7].split("T")[0])
            if beginData.year<minData[0]:
                minData[0]=beginData.year
                minData[1]=beginData.strftime("%j")
                if beginData.year == minData[0] and beginData.strftime("%j") < minData[1]:
                    minData[0]=beginData.year
                    minData[1]=beginData.strftime("%j")
            if endData.year > maxData[0]:
                maxData[0]=endData.year
                maxData[1]=endData.strftime("%j")
                if endData.year >= datetime.date.today().year:
                    maxData[0]=datetime.date.today().year
                    maxData[1]=datetime.date.today().strftime("%j")
                    if endData.year == maxData[0] and endData.strftime("%j") > maxData[1]:
                        maxData[0]=endData.year
                        maxData[1]=endData.strftime("%j")
            for i in (1,5,0):
                #element[i]=re.sub("[ ]*,[ ]*|[ ]*-+[ ]*|[ ]*/[ ]*|[ ]*'[ ]*|[ ]+" ,"_",element[i])
                if (re.search("[\s]*[,]*", element[i])):
                    element[i]=re.sub("[\s]*[,]*","",element[i])
                else:
                    element[i]=re.sub("[\s]*,[\s]*|[\s]*-+[\s]*|[\s]*/[\s]*|[\s]*'[\s]*|[\s]+","_",element[i])
                station.append(element[i])
            for i in channelsCodes:
                stations.append(station+i)
        station=[]
    for item in stations:
        list(set(tuple(sorted(item))))#delete duplicates
    for s in stations:
        print(s[0]+" "+s[1]+" "+s[2]+" "+s[3]+" "+s[4],file=fileS)
    print("The earliest start date is::"+str(minData[0])+"."+str(minData[1]))
    print("The latest end date is:"+str(maxData[0])+"."+str(maxData[1]))
    print("Number of inputs:",len(stations))
    file.close()
    fileS.close()
except FileNotFoundError:
    print ("File gmap-stations.txt has not been found")