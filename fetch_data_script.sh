#!/bin/bash
# archivo para descargar datos IRIS automaticamente desde red c1
#----------------------------------------------------------------------
#	1)INGRESO DATOS:
#echo 'Ingrese red sismologica'
#read red
#echo 'Ingrese estacion'
#read stations
#echo 'Ingrese canales'
#read canales
#echo 'Ingrese fecha INICIO (yyy-mm-dd hh:mm:ss)'
#read finicio
#finicio=${finicio// /T}
#echo 'Ingrese fecha TERMINO (yyy-mm-dd hh:mm:ss)'
#read ftermino
#ftermino=${ftermino// /T}
#

path=./
echo -e "\e[5mREMEMBER TO RUN THIS SCRIPT IN THE DIRECTORY THAT CONTAINS THE fetch_dayloop.sh and stations.txt FILES \e[0m"
echo "Do you want to turn off the computer after downloading data? (Y/N)"
read sino
#--------------------------------------------------------------------
#	2)EXTRACCION HORAS # Define Time download format by calling aux. script.
#  
/bin/bash ./fetch_dayloop.sh
#--------------------------------------------------------------------
#	3) FETCHDATA  # We call aux.txt(stations.txt in this case) with required parameters in order to download using fetchdata. This is a loop containing N rows(stations) between 2 dates. 
#
estredcan=$(awk '{print $1,$3,$4,$5}' ${path}/stations.txt)
estredcan=$(printf '%s %s\n' "$estredcan") #station/network/channel
mkdir ${path}/Data

# Download loop for every Hour/Day/interval.
while IFS=" " read -r finicio ftermino
do 
# Folder-interval creation
#hoy=$(date +"%F_%T")
mkdir ${path}/Data/Download_${finicio}
path2=${path}/Data/Download_${finicio}

#  Now we execute fetchdata with the selected row(from .txt file).
	while IFS=" " read -r stations red can loc
	do 
		can1=${can//,/ }
		for canales in $can1
		do
#	echo -e "\e[34m${finicio} ${ftermino}\e[0m \e[1m${red}\e[0m \e[1m${stations}\e[0m \e[33m${canales}\e[0m"
#	./fetch_data -F -N ${red} -S ${stations} -C ${canales} -L ${loc} -s ${finicio} -e ${ftermino} -o ${path2}/data_${red}_${stations}_${canales}_${finicio}.mseed -m ${path2}/meta_${red}_${stations}_${canales}_${finicio}.metadata -sd ${path2}
	
	echo -e "\e[34m${finicio} ${ftermino}\e[0m \e[1m${red}\e[0m \e[1m${stations}\e[0m \e[33m${canales}\e[0m"
	./fetch_data -F -N ${red} -S ${stations} -C ${canales} -L ${loc} -s ${finicio} -e ${ftermino} -o ${path2}/data_${red}_${stations}_${canales}_${finicio}.mseed -m ${path2}/meta_${red}_${stations}_${canales}_${finicio}.metadata -sd ${path2} -X ${path2}/data_${red}_${stations}_${canales}_${finicio}.xml
#	./fetchdata -F -N ${red} -S ${stations} -C ${canales} -L ${loc} -s ${finicio} -e ${ftermino} -o ${path2}/data_${red}_${stations}_${canales}_${finicio}.mseed -X ${path2}/data_${red}_${stations}_${canales}_${finicio}.xml
#only .mseed and .xml files are downloaded
		done
	done <<< "${estredcan}"
echo " "
echo -e "\e[1mOne hour of downloaded data for all stations on the channels \e[31m$can\e[0m"
echo "################################################################ "
done <date.txt
rm date.txt
#----------------------------------------------------------------------
#	4)APAGADO OPCIONAL    #  Also we can turn off our computer after the download if we wish to .
if [ $sino = Y ];then
echo "#"
echo "#"
echo -e "\e[5mDownload lista\e[0m"
echo    "Turning off the computer"
echo "227984bbl" | sudo -S shutdown  -P  -t 20 
#
elif [ $sino = N ];then
echo "#"
echo "#"
echo -e "\e[5mDownload lista\e[0m"
fi
find ./Data -type d -empty -delete






