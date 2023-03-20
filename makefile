src := ./src/*.cpp
inc := ./inc/*.h

REGEX : src inc
	clang++ -g ${src} -shared -fPIC -o libregex.so


.PHONY : clean


clean :
	-rm libregex.so


main : REGEX
	clang++ -g -o main Test/main.cpp  -L. -lregex