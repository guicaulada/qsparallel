#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 100000000

int main(int argc, char *argv[]) {
	char str[8];
	long int tam;
	int c;
	FILE *fout;

	fout = fopen("quicksort.in", "w");
	if (argc == 1)
		tam = TAM;
	else
		tam = atol(argv[1]);

	fprintf(fout, "%ld\n", tam);

	while (tam > 0) {
		for (c = 0; c < 7; c++) {
			str[c] = 33 + (rand() % 94);
		}
		str[c] = 0;
		fprintf(fout, "%s\n", str);
		printf("%d\n",tam);
		tam--;
	}

	return EXIT_SUCCESS;
}
