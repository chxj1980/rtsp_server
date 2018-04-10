
DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

LIVEDIR = /work/compile/arm/live
SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 
CPPFLAGS = -Wno-write-strings -I${DIR_INC} \
		   -I/usr/local/include/sqlite\
		   -I/usr/local/include/jrtplib3\
		   -I/usr/local/include
CPPLDFLAGS =-L/usr/local/lib -luuid -lssl -lcrypto -lz -lpthread -lsqlite \
            -ljthread -ljrtp \

TARGET = rtsp_server.mod
BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = arm-arago-linux-gnueabi-g++
${BIN_TARGET}:${OBJ}
	$(CC) ${OBJ} $(CPPLDFLAGS) -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CPPFLAGS) -c $^ -o $@

.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
	find ${DIR_BIN} -name *.mod -exec rm -rf {} \;

