CC = gcc -Wall
LIBS = -lm
MAIN= payetse

SRCS = main.c abb.c FuncionsPayETSE.c grafo.c pila.c

DEPS = abb.h FuncionsPayETSE.h grafo.h pila.h

OBJS = $(SRCS:.c=.o)

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) $(LIBS) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< 

cleanall: clean
	rm -f $(MAIN)

clean:
	rm -f *.o *.~w
