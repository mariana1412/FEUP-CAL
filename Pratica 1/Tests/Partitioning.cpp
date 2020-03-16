#include "Partitioning.h"
#include <iostream>
#include <vector>

using namespace std;

int s_recursive(int n,int k)
{
    if((k > 1) && (k < n))
        return s_recursive(n-1, k-1) + k*s_recursive(n-1, k);

    else if((k == 1) || (k == n))
        return 1;

    return 0;
}

int s_dynamic(int n,int k)
{
    vector<int> res(k,1) ;// creates a vector with size k filled with 1's
    for(int i=0; i<(n-k); i++){//only goes through the vector (n-k) times
        for(int j=1;j<k; j++){	/* The element at index 'j' is equal to itself multiplited
			   by k (which is j+1) plus the element at the previous index */
            res[j] = (j+1)*res[j] + res[j-1];
        }
    }
    return res[k-1];
}


int b_recursive(int n)
{
    int result = 0;
    for(int i = 1; i <= n; i++)
        result += s_recursive(n, i);

	return result;
}

int b_dynamic(int n)
{
    int result = 0;
    for(int i = 1; i <= n; i++)
        result += s_recursive(n, i);

    return result;

}


