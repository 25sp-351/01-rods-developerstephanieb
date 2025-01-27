CC     = clang
CFLAGS = -Wall -g

SRCS   = main.c
OBJS   = $(SRCS:.c=.o)
EXEC   = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

