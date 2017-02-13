all: test.exe
	./test.exe
test.exe: md5.h md5.cpp test.h test.cpp catch.hpp
	g++ md5.cpp test.cpp -o test.exe
catch.hpp:
	curl -o catch.hpp https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp

trace: trace.exe
	./trace.exe
trace.exe: md5.h md5.cpp trace.h trace.cpp
	g++ md5.cpp trace.cpp -o trace.exe
