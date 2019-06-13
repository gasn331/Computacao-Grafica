CPP_COMP = g++ 

run : GC
	./GC
GC : GC.o
	$(CPP_COMP) -o GC GC.cpp -lGL -lGLU -lglut -lm

GC.o : GC.cpp
	$(CPP_COMP) -cpp GC.cpp -lGL -lGLU -lglut -lm
