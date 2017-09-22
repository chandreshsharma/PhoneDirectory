all:	default

DEFINEFLAGS=

ifeq ($(DEBUG),1)
DEFINEFLAGS += -DDEBUG
endif

default: phonedirectory.cpp 
#	echo $(DEFINEFLAGS)
	g++ $(DEFINEFLAGS) phonedirectory.cpp main.cpp -o phonedir 

clean:
	rm -rf phonedir 
