COURSE = cs240
SEMESTER = spring2022

# Update the CP_NUMBER if you adapt this makefile for future assignments
CP_NUMBER = 5

# Change the following to your own information
LASTNAME = Chen
GITUSERID = JennyChen829

# The name of the executable
EXE = teams

# Name files according to CS240 naming conventions
REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

# Store executables in a subdirectory
all: $(BIN)/$(EXE)

# Reflects how the files may have been named in CP0
$(BIN)/$(EXE): $(OBJ)/main.o $(OBJ)/Player.o $(OBJ)/Queue.o $(OBJ)/Graph.o 
	$(CC) $(FLAGS) $(OBJ)/main.o $(OBJ)/Player.o $(OBJ)/Queue.o $(OBJ)/Graph.o -o $@

$(OBJ)/main.o: main.cpp Player.h Queue.h Graph.h
	$(CC) $(FLAGS) -c main.cpp -o $@

$(OBJ)/Player.o: Player.cpp Player.h Hashtable.cpp
	$(CC) $(FLAGS) -c Player.cpp -o $@

$(OBJ)/Graph.o: Graph.cpp Graph.h Queue.h
	$(CC) $(FLAGS) -c Graph.cpp -o $@

$(OBJ)/Queue.o: Queue.cpp Queue.h
	$(CC) $(FLAGS) -c Queue.cpp -o $@

# Update to add targets for your other .o files, following the Play.o sample

# Run make tar to build a .tar.gz file appropriate for uploading to Brightspace
tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz