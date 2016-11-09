CC=g++
CFLAGS = `wx-config --cxxflags --libs` -std=c++14 -Wall -Werror -Wfatal-errors

all:
	$(CC) main.cc MyApp/*.cc wxImagePanel/*.cc MyFrame/*.cc $(CFLAGS)
