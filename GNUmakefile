CFILES 	:= $(wildcard source/*.c)
CFLAGS 	:= -I include -ggdb
CC		:= gcc

OUTPUT 	:= krabascript

all: $(OUTPUT)
$(OUTPUT) : $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

install:
	sudo mv $(OUTPUT) /usr/local/bin/
