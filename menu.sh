#!/bin/bash
CP=python3
CC=gcc
CB=bash
echo "What to you want to do:" 
echo "1) Create stations.txt file from gmap-stations.txt"
echo "2) Fetch data from stations in stations.txt"
echo "3) Transform mseed files to ascii files and" 
echo "4) Create dataNoise.ascii file"
read choice
case $choice in 
    1) 
	$CP stationsFileCreator.py
	;;
    2) 
	$CB fetch_data_script.sh
	;;
	3) 
	find ./Data_test -size 0 -delete
	$CP cleanData.py
	$CP transf_mseed_ascii.py
	;;
	4) 
	$CP asciiNoise.py
	;;
	*)
    clear
	;;
	esac