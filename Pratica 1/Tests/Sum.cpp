#include "Sum.h"
#include <iostream>
#include <chrono>

string calcSum(int* sequence, int size) { //somatorio,indice;

    if (size <= 0) {
        return "";
    }
    else if (size == 1) {
        return to_string(sequence[0]) + ",0" + ";";
    }

    string result = "";
    int n = 0;


    while(n != size){
        pair<int, int> temp = sumMin(sequence, n+1, size);
        n++;
        result += to_string(temp.first) + "," + to_string(temp.second) + ";";
    }

    return result;
}

pair<int, int> sumMin(int* sequence, int n, int size){

    int index = 0, sum = 0, sumtemp = 0;

    for(int i = 0; i < size; i++){

        if((i+n) <= size){
            sumtemp = 0;
            for(int j = i; j < i + n; j++){
                sumtemp += sequence[j];
            }
            if (sumtemp < sum || (i == 0)){
                index = i;
                sum = sumtemp;
            }
        }
        else
            break;

    }

    return make_pair(sum, index);
}
