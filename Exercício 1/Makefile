C_COMP = gcc 

run : GC1
	./GC1
GC1 : GC1.o
	$(C_COMP) -o GC1 GC1.c -lGL -lGLU -lglut -lm

GC1.o : GC1.c
	$(C_COMP) -c GC1.c -lGL -lGLU -lglut -lm
