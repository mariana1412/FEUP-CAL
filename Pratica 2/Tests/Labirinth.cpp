#include "Labirinth.h"

#include <iostream>

using namespace std;

static bool firstTime = true;

Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];

}


void Labirinth::initializeVisited() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}

void  Labirinth::printLabirinth() {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}

void  Labirinth::printVisited() {
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            cout << visited[i][j] << " ";

        cout << endl;
    }
}


bool Labirinth::findGoal(int x, int y) {

    //inicializar array Visited pela primeira vez
    if(firstTime){
        initializeVisited();
        firstTime = false;
    }

    //verificar se está dentro do labirinto
    if(x > 9 || x < 0 || y < 0 || y > 9){
        return false;
    }
    else if(labirinth[x][y] == 2){ //verificar se é a saida
        cout << "\nSuccess!\n";
        return true;
    }
    else if(labirinth[x][y] == 0){ //verificar se é parede
        return false;
    }

    if(!visited[x][y]){
        visited[x][y] = true;

        if(findGoal(x+1, y)) //direita
            return true;
        else if(findGoal(x-1, y)) //esquerda
            return true;
        else if (findGoal(x, y+1)) //baixo
            return true;
        else if(findGoal(x, y-1)) //cima
            return true;
        else
            return false;
    }

    return false;
}


