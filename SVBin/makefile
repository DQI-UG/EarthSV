CP=python3
CC=gcc
CB=bash
data:
	$(CB) menu.sh
ascii:
	$(CP) transf_mseed_ascii.py
cleanData:
	find ./Data_test -size 0 -delete
	$(CP) cleanData.py	
asciiNoise:
	$(CP) asciiNoise.py
rand:
	$(CC) -Wall *.c -lm -o main.out
#	./main.out ./Data_ascii/IRISDMC-data_IC_LSA_BHZ_2016-03-01T00:00:00.ascii -i -l20
#	./main.out ./Data_noise_ascii/dataNoise.ascii -i -l20
	./main.out ./Data_noise_ascii/dataNoise.ascii -i -l20 -n267890440
#	./main.out ./Data_noise_ascii/dataNoise.ascii -i -l20 -n267890437
#	./main.out --help
clean:
	@clear
	@rm *.out