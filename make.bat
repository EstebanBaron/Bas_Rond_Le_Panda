g++ -c main.cpp -IC:\SFML-2.5.1\include
g++ -c Personnage.cpp -IC:\SFML-2.5.1\include
g++ -c Aliments.cpp -IC:\SFML-2.5.1\include
g++ -c Bouton.cpp -IC:\SFML-2.5.1\include
g++ -c Piece.cpp -IC:\SFML-2.5.1\include
g++ -c Vie.cpp -IC:\SFML-2.5.1\include

g++ main.o Personnage.o Aliments.o Bouton.o Piece.o Vie.o -o Bas-Rond_Le_Panda.exe -LC:\SFML-2.5.1\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system