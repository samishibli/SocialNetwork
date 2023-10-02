output: network.o user.o social_network.o
	g++ -std=c++11 network.o user.o social_network.o -o output

network.o: network.cpp
	g++ -c network.cpp -o network.o

user.o: user.cpp
	g++ -c user.cpp -o user.o

social_network.o: social_network.cpp
	g++ -c social_network.cpp -o social_network.o

clean:
	rm -f network.o user.o social_network.o output