
OBJS 	= diseaseMonitor.o functions.o
SOURCE	= diseaseMonitor.c functions.c
HEADER  = functions.h
OUT  	= diseaseMonitor
CC	= gcc
FLAGS   = -g3 -c 
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g3 $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<< 
diseaseMonitor.o: diseaseMonitor.c
	$(CC) $(FLAGS) diseaseMonitor.c

functions.o: functions.c
	$(CC) $(FLAGS) functions.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)
