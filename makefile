main: main.o hero.o hashtable.o queue.o
	g++ -std=gnu++17 -o main main.o hero.o hashtable.o queue.o

main.o: main.cpp hashtable.h queue.h hero.h
	g++ -std=gnu++17 -c main.cpp

hero.o: hero.cc hero.h
	g++ -std=gnu++17 -c hero.cc

queue.o: queue.cc queue.h
	g++ -std=gnu++17 -c queue.cc

hashtable.o: hashtable.cc hashtable.h
	g++ -std=gnu++17 -c hashtable.cc

clean:
	rm -rf *.o endlessrpg
