#!/usr/bin/env python3
# -*- coding: utf-8 -*-
############### CRIPTOGRAFIA/ALEATORIEDAD: procesado data       ###############
############### Julio viveros carrasco   | juviveros@udec.cl    ###############
############### Alejandra Muñoz Jensen   |  amunozj@udec.cl     ###############
############### ultima mod: 18/11/2020. Comentarios al correo   ###############

from obspy import read, read_inventory
from obspy.core import UTCDateTime
import os
import glob
################################ PATHS    #####################################
path=os.getcwd()
pathData=path + "/Data_test"
if (len(os.listdir(pathData))==0):
    print("The Data folder is empty")
pathAsciiFolder=path+"/Data_ascii"

# We create the folder containing the seismograms
##############################################################################
pre_filt   = [0.5,1,15,20]
resampling = False
dhoras=os.listdir(pathData) # We enter the data folder
dhoras.sort()
horas=[]
for line in dhoras:
    type= line.split("_")
    x= type[0]
    y=type[1]
    horas.append(y)  
    del x,y
    #
os.chdir(pathData)  
for hfile in dhoras: # we select a time-folder
    f_HHZ=[] 
    Z=[] 
    path_hours = os.path.join(pathData,hfile)
    mseeds     = glob.glob(path_hours + '/'+'*'+'.mseed') 
    for mseed in mseeds:
        if(os.path.join(path_hours,mseed.split('/')[-1].split('.')[0]+'.xml')):
            st  = read(mseed,format='mseed')
            tr  = st[0]
            inv = read_inventory(os.path.join(path_hours,mseed.split('/')[-1].split('.')[0]+'.xml')) #Instrumental response
        # Note that here you have the option to transform the signal into DISP (displacement) or VEL (velocity)
            tr.remove_response(inventory=inv, pre_filt=pre_filt, output="ACC") 

        # Erase linear tendency
            tr.detrend

        # Sampling check 
            if tr.stats.delta > 0.25: print('Choose stations HH or BH')

        # Resampling (this is optional, you can also use all the data, without resampling) 
            if resampling == True:
                tr.resample(0.25)
            tr.write(pathAsciiFolder+'/'+mseed.split('/')[-1].split('.')[0]+'.ascii', format='TSPAIR')
            print("Trace "+mseed.split('/')[-1].split('.')[0]+" transcribed to ASCII")
        else:
            continue