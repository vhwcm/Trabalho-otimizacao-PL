CC      := gcc
CFLAGS  := -Wall -Wextra -O2

TARGET  := comprimidos
SRC     := trab.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
