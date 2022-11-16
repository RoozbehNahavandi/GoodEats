CC := g++ -std=c++11

all: goodeats.out

goodeats.out: main.o Manager.o Shelf.o Recipe.o Client.o Interface.o Filters.o Offer.o Orders.o
	$(CC) main.o Client.o Manager.o Shelf.o Recipe.o Interface.o Filters.o Offer.o Orders.o -o goodeats.out

main.o: main.cpp Client.hpp Manager.hpp Defines.hpp Interface.hpp Exceptions.hpp 
	$(CC) -c main.cpp -o main.o

Client.o: Client.cpp Client.hpp Defines.hpp Exceptions.hpp Recipe.hpp Shelf.hpp Offer.hpp Orders.hpp
	$(CC) -c Client.cpp -o Client.o

Manager.o: Manager.cpp Manager.hpp Client.hpp Recipe.hpp Shelf.hpp  Defines.hpp Exceptions.hpp Filters.hpp Offer.hpp
	$(CC) -c Manager.cpp -o Manager.o

Shelf.o: Shelf.cpp Shelf.hpp Defines.hpp Exceptions.hpp
	$(CC) -c Shelf.cpp -o Shelf.o

Recipe.o: Recipe.hpp Recipe.cpp Defines.hpp Exceptions.hpp Filters.hpp
	$(CC) -c Recipe.cpp -o Recipe.o

Interface.o: Interface.hpp Interface.cpp Manager.hpp Client.hpp Recipe.hpp Shelf.hpp Defines.hpp Exceptions.hpp Filters.hpp Offer.hpp
	$(CC) -c Interface.cpp -o Interface.o 

Filters.o: Filters.hpp Filters.cpp Recipe.hpp
	$(CC) -c Filters.cpp -o Filters.o

Offer.o: Offer.hpp Offer.cpp Defines.hpp
	$(CC) -c Offer.cpp -o Offer.o

Orders.o: Orders.cpp Orders.hpp Defines.hpp
	$(CC) -c Orders.cpp -o Orders.o



.PHONY: clean
clean:
	rm *.out
	rm *.o