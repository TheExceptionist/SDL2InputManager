objects = main.o
exe_name = sdl2keys
include_dir = include
lib_dir = lib
libs = SDL2

$(exe_name) : $(objects)
	g++ -Wall $(objects) -o $(exe_name) -I $(include_dir) -L $(lib_dir) \
	-l $(libs)

main.o : main.cpp
	g++ -c main.cpp


.PHONY : clean \
	 reset
clean : 
	-rm $(objects)

reset: 
	-rm $(objects) $(exe_name)
