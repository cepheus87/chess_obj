EXEC = main
CO = g++

HEADER= Board.h Figure.h Interface.h

CFLAGS = -Wall 


#%.o: %.cpp $(HEADER)
#	$(CO) $(CFLAGS) -c $<


all: $(EXEC).o $(HEADER) $(FUNCTIONS)
	$(CO) $(CFLAGS) Board.cpp Figure.cpp Interface.cpp  $(EXEC).o -o $(EXEC).exe 

clean:
	rm -f *.o *~ $(EXEC).exe
