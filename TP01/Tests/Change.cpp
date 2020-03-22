#include "Change.h"
#include <iostream>

/* ALINEA A
 * Ir dividindo o montante pela maior moeda, guarda-se o número de moedas desse tipo e fica-se com o resto.
 */

/* ALINEA B
 * Slide 12 - Formulação recursiva - Programação Dinamica
 */

/* ALINEA C
 *      i   |   k           0   1   2   3   4   5   6   7   8   9
 *          |
 *      0   |   minCoins    0   0   0   0   0   0   0   0   0   0
 *          |   lastCoin    0   0   0   0   0   0   0   0   0   0
 *          |
 *      1   |   minCoins    0   1   2   3   4   5   6   7   8   9
 *          |   lastCoin    0   1   1   1   1   1   1   1   1   1
 *          |
 *      2   |   minCoins    0   1   1   2   2   3   3   4   4   5
 *          |   lastCoin    0   1   2   1   2   1   2   1   2   1
 *          |
 *      3   |   minCoins    0   1   1   2   2   1   2   2   3   3
 *          |   lastCoin    0   1   2   1   2   5   1   2   1   2
 */

//exercicio d --> de forma recursiva
/*string calcChange(int m, int numCoins, int *coinValues)
{
    cout << "----------------------------------" << endl;
    if (m <= 0 || (numCoins < 0)) {
        cout << "Nem todas as condicoes se verificam! \n";
        cout << "----------------------------------" << endl;
        return "";
    }
    else if (coinValues[0] > m){
        cout << "Nao ha moedas para completar o troco!\n";
        cout << "----------------------------------" << endl;
        return "-";
    }

    string result = "";
    int numberCoins = minCoins(numCoins-1, m, coinValues), counter = 0;

    cout << "Number of coins -> " << numberCoins << endl;

    while(m != 0) {
        int coin = lastCoin(numCoins-1, m, coinValues);
        m -= coin;
        result += to_string(coin) + ";";
        counter++;
    }
     cout << "Final number of coins -> " << counter << endl;

    if(counter != numberCoins){
        cout << "It's not right! \n";
        cout << "----------------------------------" << endl;
        return "";
    }
    else
        cout << "Everything is fine!! \n";

    cout << "----------------------------------" << endl;
    return result;
}

int minCoins(int i, int k, int *coinValues){ //i é o numero diferente de moedas, ou seja, tamanho do array-1; k é o troco que ainda falta dar

    if(k < 0)
        return -1;
    else if(k == 0 && i < 0) {
        return 0;
    }
    else if(i == 0 || ((k>=coinValues[i]) && (minCoins(i, k - coinValues[i], coinValues)+1 < minCoins(i-1, k, coinValues)))) {
        return minCoins(i, k - coinValues[i], coinValues) + 1;
    }
    else {
        return minCoins(i - 1, k, coinValues);
    }
}

int lastCoin(int i, int k, int *coinValues){ //i é o numero diferente de moedas, ou seja, tamanho do array-1; k é o troco que ainda falta dar

    if((k == 0) || (i < 0))
        return 0;

    else if (coinValues[i] <= k && (i == 0))
        return coinValues[i];

    else if(coinValues[i] <= k && (minCoins(i, k - coinValues[i], coinValues)+1 < minCoins(i-1, k, coinValues)))
        return  coinValues[i];

    else
        return lastCoin(i-1, k, coinValues);

}*/

//exercicio d --> com programção dinâmica

string calcChange(int m, int numCoins, int *coinValues){

    cout << "----------------------------------" << endl;
    if (m <= 0 || (numCoins < 0)) {
        cout << "Nem todas as condicoes se verificam! \n";
        cout << "----------------------------------" << endl;
        return "";
    }
    else if (coinValues[0] > m){
        cout << "Nao ha moedas para completar o troco!\n";
        cout << "----------------------------------" << endl;
        return "-";
    }

    int minCoins[m + 1];  // quantidade de moedas usadas
    int lastCoin[m + 1];  // ultima moeda adicionada

    fill_n(minCoins, m+1, 0);
    fill_n(lastCoin, m+1, 0);

    // percorre quantas moedas é para usar, usando 1, 2, 3...
    for (int i = 1; i <= numCoins; i++ ) {
        // montante a ter em consideração desde o valor da moeda até ao valor do montante requeridp
        for (int k = coinValues[i-1]; k <= m; k++) {
            // ...==0 quando compara com i=1 para puder adicionar a 1ª moeda
            // se a quant. moedas usadas no montante a ter em conta for maior que
            //      quant. moedas usadas com o montante atual menos o valor da moeda maior
            // OU SEJA se ao adicionar a moeda nova o numero minimo de moedas diminui
            if (minCoins[k] == 0 || 1 + minCoins[k - coinValues[i-1]] < minCoins[k]) {
                //atualiza o numero minimo de moedas: passa a ser 1 <- a moeda adicionada +
                //                                              o numero minimo de moedas do montante tirando o valor da moeda considerada
                minCoins[k] = 1 + minCoins[k - coinValues[i-1]];
                //atualiza também a ultima moeda para ser a moeda de maior valor
                lastCoin[k] = coinValues[i - 1];
            }
            // não entra no if, a moeda não serve, então não mudam os arrays
        }
    }

    string output = "";
    int temp = m;

    if (minCoins[m] == 0)
        return "-";

    for (int i = 0; i < minCoins[m]; i++) {
        output += to_string(lastCoin[temp]) + ";";
        temp -= lastCoin[temp];
    }

    return output;

}