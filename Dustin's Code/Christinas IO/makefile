CXX = g++
CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
#LDFLAGS = -lboost_date_time

OBJS1 = main.o

SRCS1 = main.cpp


HEADERS =

#target: dependencies
#	rule to build
#
All: Program1

Program1: ${OBJS1}
	${CXX} ${OBJS1} -o program

${OBJS1}: ${SRCS1}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

Debug: 
