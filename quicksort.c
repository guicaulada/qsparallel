#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

void qsinternal(char **array, int esq, int dir, int cut) {
	int i = esq, j = dir;
	{ 
		char* tmp;
		char* pivot = array[(esq + dir) / 2];
		while (i <= j) {
			while (strcmp(array[i],pivot) < 0)
				i++;
			while (strcmp(array[j],pivot) > 0)
				j--;
			if (i <= j) {
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
				i++;
				j--;
			}
		}
	}
	if ( ((dir-esq)<cut) ){
		if (esq < j){ qsinternal(array, esq, j, cut); }			
		if (i < dir){ qsinternal(array, i, dir, cut); }
	}else{
		#pragma omp task 	
		{ qsinternal(array, esq, j, cut); }
		#pragma omp task 	
		{ qsinternal(array, i, dir, cut); }		
	}
}


void qsparallel(char** array, int len){

	int cut = 1000;

	#pragma omp parallel
	{	
		#pragma omp single nowait
		{
			qsinternal(array, 0, len-1, cut);	
		}
	}	

}


int main(void) {
	clock_t begin = clock();
	char **keys;
	long int N, i;

	FILE *file;

	if ((file = fopen("quicksort.in", "r")) == NULL) {
		perror("quicksort.in");
		exit(1);
	}

	fscanf(file, "%ld", &N);
	keys = (char**) malloc(N * 8);
	if (keys == NULL) {
		perror("Memory allocation");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < N; i++) {
		keys[i] = malloc(8);
		if (keys[i] == NULL) {
			perror("Memory allocation");
			exit(EXIT_FAILURE);
		}
		fscanf(file, "%s", keys[i]);
	}
	fclose(file);
	
	omp_set_num_threads(64);
	//qsort(keys, N, sizeof(char *), (int(*)(const void *, const void *)) strcmp);
	qsparallel(keys,N);

	if ((file = fopen("quicksort.out", "w")) == NULL) {
		perror("quicksort.out");
		exit(1);
	}

	for (i = 0; i < N; i++)
		fprintf(file, "%s\n", keys[i]);

	fclose(file);
	free(keys);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\n\n%.6f\n\n",time_spent);
	return EXIT_SUCCESS;
}
