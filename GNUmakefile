CFILES 	:= $(wildcard source/*.cpp)
CFLAGS 	:= -I include
CC		:= g++

OUTPUT 	:= krabascript

all: $(OUTPUT)
$(OUTPUT) : $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)