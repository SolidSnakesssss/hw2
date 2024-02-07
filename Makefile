CXX=g++
CXXFLAGS=-g -Wall -std=c++11
#Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=amazon.o user.o db_parser.o product.o product_parser.o util.o book.o clothing.o movie.o mydatastore.o

all: amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

amazon.o: amazon.cpp db_parser.h datastore.h product_parser.h util.h mydatastore.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp
user.o: user.cpp user.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c user.cpp
db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c db_parser.cpp
product.o: product.cpp product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product.cpp
product_parser.o: product_parser.cpp product_parser.h product.h book.h clothing.h movie.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product_parser.cpp
util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c util.cpp

#Custom File Book
book.o: book.cpp book.h product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c book.cpp
#Custom File Clothing
clothing.o: clothing.cpp clothing.h product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c clothing.cpp
#Custom File Movie
movie.o: movie.cpp movie.h product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c movie.cpp

#mydatastore
mydatastore.o: mydatastore.cpp mydatastore.h datastore.h util.h book.h clothing.h movie.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c mydatastore.cpp



clean:
	rm -f *.o amazon
