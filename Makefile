all: test.exe
	./test.exe
test.exe: md5.h md5.cpp test.cpp catch.hpp
	g++ md5.cpp test.cpp -o test.exe
catch.hpp:
	curl -o catch.hpp https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
rfc: rfc1321/rfc.exe
	./rfc1321/rfc.exe -x
rfc1321/rfc.exe: rfc1321/md5c.c rfc1321/mddriver.c
	gcc rfc1321/md5c.c rfc1321/mddriver.c -o rfc1321/rfc.exe 
