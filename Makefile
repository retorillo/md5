all: test.exe
	./test.exe
test.exe: test.cpp catch.hpp
	g++ test.cpp -o test.exe
catch.hpp:
	curl -o catch.hpp https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
