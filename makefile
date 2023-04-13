src := ./src/*.cpp
inc := ./inc/*.h

REGEX : src inc
	clang++ -g -m64 -c -Werror ${src}  
	ar rsc  libregex.a  ./*.o 
	# mv regex.o rn_regex.o

# install : REGEX
# 	-sudo cp ./libregex.so  /lib/



.PHONY : clean install


clean :
	-sudo  rm libregex.so /lib/libregex.so  ./*.o  ./*.a


main :  REGEX
	# clang++ -g -o main Test/main.cpp  -static -L. -lregex
	clang++ -g -o main Test/main.cpp  ./*.o