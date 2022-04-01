CC = g++
SRC_DIR = src
SRC_FILES = ${shell find ${SRC_DIR} -type f -name "*.cpp"}
COMPILER_FLAGS = -c -std=c++14 -m64 -g -Wall
INCLUDE_PATHS = -I include
LINKER_FLAGS = -lSDL2main -lSDL2
BUILD_DIR = build

build:
	${CC} ${SRC_FILES} ${COMPILER_FLAGS} ${INCLUDE_PATHS}
	- mkdir ${BUILD_DIR}
	mv *.o ${BUILD_DIR}

link:
	${CC} ${BUILD_DIR}/*.o -o ${BUILD_DIR}/main ${LINKER_FLAGS}

run:
	${BUILD_DIR}/main

clear:
	- rm -Rf ${BUILD_DIR}

all: clear build link run
