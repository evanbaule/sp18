#Binghamton University
#CS350 - Operating System
#Programming Assignment 1
#Evan M. Baule
all:	link_all

#Links build/*.o into bin/driver executable
link_all: comp_all generator.o sorter.o
	gcc -o prog1generator generator.o
	gcc -o prog1sorter sorter.o
	
#Compiles src files into object in build/*.o
comp_all: generator.c sorter.c
	gcc -c generator.c
	gcc -c sorter.c 
	
#Removes object files build/*.o and executable bin/drive(.exe), build afterwards to replace those files
clean:
	rm -f *.o prog1sorter prog1generator *.txt

#Runs the bin/drive(.exe) executable
run:
	./prog1generator

#Cat | input files to check cases
test: 
	./prog1generator -o sample.txt -s 12194194018
	./prog1sorter -i sample.txt -o sorted.txt -c asciic.txt

test2: 
	./prog1generator -o sample2.txt -s 9945312
	./prog1sorter -i sample2.txt -o sorted2.txt -c asciic2.txt

#Reformat file structure, copy, and compress files for submission
submit: