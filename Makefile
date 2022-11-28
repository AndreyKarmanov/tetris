CXX = g++ # compiler program
CXXFLAGS = -std=c++14 -g -Wall -MMD \
			-Wextra -Werror=vla 

# MMD generates dependency files
OBJECTS = window.o piece.o pieceFactory.o gameObserver.o gameSubject.o gameBoard.o textObserver.o graphicsWrapper.o game.o main.o
DEPENDS = ${objects:.o=.d}
PROGRAM = biquardis

${PROGRAM}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${PROGRAM} -lX11

# basically just copies all .d files into this file
-include ${DEPENDS} # hyphen means ignore errors

.PHONY: clean 
clean:
	rm ${PROGRAM} ${OBJECTS} ${DEPENDS} ${OBJECTS:.o=.d}
