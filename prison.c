#include <stdio.h>
#include <stdlib.h>

int main(){
	int Mat[2][2][2];
	int i = 0;
	int j = 0;
	
	printf("Input player 1, 2 payoff sequantially | [player][player 1's strategy][player 2's strategy] : \n");
	scanf("%d %d %d %d %d %d %d %d", &Mat[0][0][0], &Mat[0][0][1], &Mat[0][1][0], &Mat[0][1][1], &Mat[1][0][0], &Mat[1][0][1], &Mat[1][1][0], &Mat[1][1][1]);
		
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			if((Mat[0][i][j] <= Mat[0][abs(i-1)][j]) || (Mat[1][i][j] <= Mat[1][i][abs(j-1)]))
				printf("Nash Equilbrium, (s1*, s2*) = (%d, %d)\n", i, j);
		}
	}

	return 0;
}
