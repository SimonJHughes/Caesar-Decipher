compile:
	g++ Project3.cpp Cipher.cpp CipherAdvanced.cpp Queue.cpp -c
	g++ Project3.o Cipher.o CipherAdvanced.o Queue.o -o Project3.out
run:
	./Project3.out
clean:
	rm *.o
	rm *.out