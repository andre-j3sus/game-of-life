CC = gcc
CFLAGS = -g -Wall -I${INCLUDE_DIR} -I${LIFE_INCLUDE_DIR}

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
LIFE_INCLUDE_DIR = ../life/include

_SRC_FILES = app_animations.c animations.c
SRC_FILES = ${addprefix ${SRC_DIR}/, ${_SRC_FILES}}

TARGETS = app_animations

all: ${TARGETS}

app_animations:
	${CC} ${CFLAGS} ${SRC_FILES} ../life/src/life.c -o ${BUILD_DIR}/$@ && ./${BUILD_DIR}/$@
