CC = gcc
CFLAGS = -g -Wall -I$(INCLUDE_DIR)

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

_SRC_FILES = life_test.c life.c
SRC_FILES = ${addprefix ${SRC_DIR}/, ${_SRC_FILES}}

TARGETS = life_test

all: ${TARGETS}

life_test:
	${CC} ${CFLAGS} ${SRC_FILES} -o ${BUILD_DIR}/$@ && ./${BUILD_DIR}/$@
