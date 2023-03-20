src := ./src/*.cpp
inc := ./inc/*.h

REGEX : src inc
	clang++ -g ${src} -shared -fPIC -o libregex.so

install : REGEX
	-sudo cp ./libregex.so  /lib/



.PHONY : clean


clean :
	-rm libregex.so


main : REGEX install
	clang++ -g -o main Test/main.cpp  -L. -lregex