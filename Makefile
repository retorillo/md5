all: test.exe
	./test.exe
test.exe: md5.h md5.cpp test.cpp catch.hpp
	g++ md5.cpp test.cpp -o test.exe
catch.hpp:
	curl -o catch.hpp https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp

pad: pad.exe
	./pad.exe
pad.exe: md5.h md5.cpp pad.h pad.cpp
	g++ md5.cpp pad.cpp -o pad.exe
