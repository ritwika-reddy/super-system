//============================================================================
// Name        : uva-problems.cpp
// Author      : ritwika-reddy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdio.h"
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>

using namespace std;

int N;
double dist[20][20], memo [1 << 16]; // 1 << 16 is 2^16

double matching (int bit_mask){ // @suppress("No return")
	if(memo[bit_mask] > -0.5) // see that we initialize the array with -1 in the main function
		return memo[bit_mask];
	if(bit_mask == (1 << 2*N) -1 ) // all are matched
		return memo[bit_mask] = 0;
	double matching_value = 32767 * 32767; // initialize with large value

	for(int p1 = 0; p1 < 2 * N; p1++)
		if(!bit_mask & (1 << p1)){ // if this bit is off
			for(int p2 = p1 + 1; p2 < 2*N; p2++)
				if(!(bit_mask & (1 << p2))) // if this different bit is also off
					matching_value = min(matching_value,
						dist[p1][p2] + matching(bit_mask | (1 << p1) | (1 << p2) ) );
			break;
		}
	return memo[bit_mask] = matching_value;
}

int main(){
	char line[1000], name[1000];
	int i,j, caseNo = 1, x[20], y[20];
	// freopen("10911.txt", "r", stdin); // one way to simplify testing

	while(sscanf(gets(line), "%d", &N), N){
		for (i=0; i < 2*N; i++)
			sscanf(gets(line), "%s %d %d", &name, &x[i], &y[i]);
		for (i=0; i < 2*N; i++)
			for(j=0; j < 2*N;j++)
				dist[i][j] = sqrt((double)(x[i] - x[j])*(x[i]-x[j])
						+(y[i]-y[j])*(y[i] - y[j]));
		// using DP to solve matching on general graph
		memset(memo, -1, sizeof memo);
		printf("Case %d: %.2lf\n", caseNo++, matching(0));
	}
	return 0;
}








