target := bot
objs := main.o bot.o rand.o

CC := g++
CFLAGS := -Wall -g -std=c++11

all: $(target)

bot: $(objs)
	$(CC) $(CFLAGS) -o $@ $^

bot.o: bot.cpp bot.h rand.h
	$(CC) $(CFLAGS) -c $<

rand.o: rand.cpp rand.h
	$(CC) $(CFLAGS) -c $<

main.o: main.cpp bot.h rand.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f bot bot.o rand.o main.o
