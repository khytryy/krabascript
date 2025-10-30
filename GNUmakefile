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
	@if [ -f "$(OUTPUT)" ]; then \
		echo "Installing $(OUTPUT)..."; \
		sudo cp $(OUTPUT) /usr/local/bin/; \
		echo "SUCCESS: $(OUTPUT) has been copied to /usr/local/bin/! You can now run it with '$(OUTPUT)' command."; \
	else \
		echo "Error: Cannot find $(OUTPUT), run 'make' first."; \
		exit 1; \
	fi