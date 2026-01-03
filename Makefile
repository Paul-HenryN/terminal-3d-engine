CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lncurses -lm

SRCS = main.c render.c scene.c shape.c transform.c
OBJS = $(SRCS:.c=.o)
TARGET = 3dengine

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
