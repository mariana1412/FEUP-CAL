#include "Factorial.h"

int factorialRecurs(int n)
{

    if((n == 0) || (n == 1))
        return 1;
    else
        return n*factorialRecurs(n-1);
}

int factorialDinam(int n)
{
    int aux = 1, result = 1;

    while(aux < n){
        aux++;
        result += aux;
    }

	return result;
}


/*
 * temporal -> são iguais já que têm os dois complexidades lineares
 * espacial -> a recursiva ocupa mais espaço
 * */