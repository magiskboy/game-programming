GCC := g++

FLAGS := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

BUILD := build

SRC := src

INCLUDE := include

all: main Core CreditState FPSController Game Input LogoState MachineState Map Panel PlayState Snake State 
	# ${GCC} ${FLAGS} -o ${BUILD}/snake \
	# 	${BUILD}/main.o \
	# 	${BUILD}/Core.o \
	# 	${BUILD}/CreditState.o \
	# 	${BUILD}/FPSController.o \
	# 	${BUILD}/Game.o \
	# 	${BUILD}/Input.o \
	# 	${BUILD}/LogoState.o \
	# 	${BUILD}/MachineState.o \
	# 	${BUILD}/Map.o \
	# 	${BUILD}/Panel.o \
	# 	${BUILD}/PlayState.o \
	# 	${BUILD}/Snake.o \
	# 	${BUILD}/State.o \

main: ${SRC}/main.cpp
	${GCC} -c ${SRC}/main.cpp -o ${BUILD}/main.o

Core: ${SRC}/Core.cpp ${INCLUDE}/Core.h
	${GCC} -c ${SRC}/Core.cpp ${INCLUDE}/Core.h ${INCLUDE}/Input.h ${INCLUDE}/MachineState.h -o ${BUILD}/Core.o

CreditState: ${SRC}/CreditState.cpp ${INCLUDE}/CreditState.h
	${GCC} -c ${SRC}/CreditState.cpp ${INCLUDE}/CreditState.h -o ${BUILD}/CreditState.o

FPSController: ${SRC}/FPSController.cpp ${INCLUDE}/FPSController.h
	${GCC} -c ${SRC}/FPSController.cpp ${INCLUDE}/FPSController.h -o ${BUILD}/FPSController.o

Game: ${SRC}/Game.cpp ${INCLUDE}/Game.h
	${GCC} -c ${SRC}/Game.cpp ${INCLUDE}/Game.h -o ${BUILD}/Game.o

Input: ${SRC}/Input.cpp ${INCLUDE}/Input.h
	${GCC} -c ${SRC}/Input.cpp ${INCLUDE}/Input.h -o ${BUILD}/Input.o

LogoState: ${SRC}/LogoState.cpp ${INCLUDE}/LogoState.h
	${GCC} -c ${SRC}/LogoState.cpp ${INCLUDE}/LogoState.h -o ${BUILD}/LogoState.o

MachineState: ${SRC}/MachineState.cpp ${INCLUDE}/MachineState.h
	${GCC} -c ${SRC}/MachineState.cpp ${INCLUDE}/MachineState.h -o ${BUILD}/MachineState.o

Map: ${SRC}/Map.cpp ${INCLUDE}/Map.h
	${GCC} -c ${SRC}/Map.cpp ${INCLUDE}/Map.h -o ${BUILD}/Map.o

Panel: ${SRC}/Panel.cpp ${INCLUDE}/Panel.h
	${GCC} -c ${SRC}/Panel.cpp ${INCLUDE}/Panel.h -o ${BUILD}/Panel.o

PlayState: ${SRC}/PlayState.cpp ${INCLUDE}/PlayState.h
	${GCC} -c ${SRC}/PlayState.cpp ${INCLUDE}/PlayState.h ${INCLUDE}/State.h ${INCLUDE}/Core.h ${INCLUDE}/MachineState.h ${INCLUDE}/LogoState.h ${INCLUDE}/Map.h ${INCLUDE}/Snake.h ${INCLUDE}/Panel.h -o ${BUILD}/PlayState.o

Snake: ${SRC}/Snake.cpp ${INCLUDE}/Snake.h
	${GCC} -c ${SRC}/Snake.cpp ${INCLUDE}/Snake.h ${INCLUDE}/Vector2.h -o ${BUILD}/Snake.o

State: ${SRC}/State.cpp ${INCLUDE}/State.h
	${GCC} -c ${SRC}/State.cpp ${INCLUDE}/State.h -o ${BUILD}/State.o

deps:
	@sudo apt install -y libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev> /dev/null

clean:
	@rm -rf ${BUILD}
