CXX = g++
CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
#LDFLAGS = -lboost_date_time

OBJS1 = Algorithm1.o

SRCS1 = Algorithm1.cpp

OBJS2 = Algorithm3.o

SRCS2 = Algorithm3.cpp


HEADERS =

#target: dependencies
#	rule to build
#
All: Program1 Program2

Program1: ${OBJS1}
	${CXX} ${OBJS1} -o program1

${OBJS1}: ${SRCS1}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

Program2: ${OBJS2}
	${CXX} ${OBJS2} -o program2

${OBJS2}: ${SRCS2}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

Debug: 
