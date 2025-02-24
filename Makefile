CC = gcc

CFLAGS = -Wall -Wextra -Werror -O2

TARGET = cache-money-to-words

SRC = cache-money-to-words.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean $(TARGET)