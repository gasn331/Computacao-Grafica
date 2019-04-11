C_COMP = gcc 

run : GC2
	./GC2
GC2 : GC2.o
	$(C_COMP) -o GC2 GC2.c -lGL -lGLU -lglut -lm

GC2.o : GC2.c
	$(C_COMP) -c GC2.c -lGL -lGLU -lglut -lm
