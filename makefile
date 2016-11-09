CC=g++
CFLAGS= -I/home/teun/Downloads/wxWidgets-3.0.2/include `wx-config --cxxflags --libs` -std=c++14 -Wall

all:
	$(CC) hello.cc  $(CFLAGS)
