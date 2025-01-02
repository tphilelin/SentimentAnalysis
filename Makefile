CC = gcc
CFLAGS = -lm -Wall -Wextra
EXECUTABLE = vader
SRC = vaderSentiment.c main.c
 
$(EXECUTABLE) : $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(EXECUTABLE)


