#!/bin/bash
CP=python3
CC=gcc
CB=bash
echo "What to you want to do:" 
echo "1) Create stations.txt file from gmap-stations.txt"
echo "2) Fetch data from stations in stations.txt"
echo "3) Transform mseed files to ascii files and create dataNoise.ascii file"
read choice
case $choice in 
    1) 
	$CP stationsFileCreator.py
	;;
    2) 
	$CB fetch_data_script.sh
	;;
	3) 
	$CP transf_mseed_ascii.py
	;;
	*)
    clear
	;;
	esac