//Kmeans, from Rodinia
#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <omp.h>
#include "kmeans.h"

extern double wtime(void);

void usage(char *argv0) {
    char *help =
        "\nUsage: %s [switches] -i filename\n\n"
        "    -i filename      :file containing data to be clustered\n"		
        "    -m max_nclusters :maximum number of clusters allowed    [default=5]\n"
        "    -n min_nclusters :minimum number of clusters allowed    [default=5]\n"
        "    -t threshold     :threshold value                       [default=0.001]\n"
        "    -l nloops        :iteration for each number of clusters [default=1]\n"
        "    -b               :input file is in binary format\n"
        "    -r               :calculate RMSE                        [default=off]\n"
        "    -o               :output cluster center coordinates     [default=off]\n";
    fprintf(stderr, help, argv0);
    exit(-1);
}

int setup(int argc, char **argv) {
	int	opt;
	extern char   *optarg;
	char   *filename = 0;
	float  *buf;
	char	line[1024];
	int	isBinaryFile = 0;
	float	threshold = 0.001;
	int	max_nclusters=5;
	int	min_nclusters=5;
	int	best_nclusters = 0;
	int	nfeatures = 0;
	int	npoints = 0;
	float	len;
	float **features;
	float **cluster_centres=NULL;
	int	i, j, index;
	int	nloops = 1;		
	int	isRMSE = 0;		
	float	rmse;
	int	isOutput = 0;
	//float	cluster_timing, io_timing;		

	// obtain command line arguments and change appropriate options
	while ( (opt=getopt(argc,argv,"i:t:m:n:l:bro"))!= EOF) {
		switch (opt) {
		case 'i': filename=optarg;
			break;
		case 'b': isBinaryFile = 1;
			break;            
		case 't': threshold=atof(optarg);
  			break;
		case 'm': max_nclusters = atoi(optarg);
 			break;
		case 'n': min_nclusters = atoi(optarg);
			break;
		case 'r': isRMSE = 1;
			break;
		case 'o': isOutput = 1;
			break;
		case 'l': nloops = atoi(optarg);
			break;
		case '?': usage(argv[0]);
			break;
		default: usage(argv[0]);
			break;
		}
	}
	if (filename == 0) usage(argv[0]);

    /* get nfeatures and npoints */
	if (isBinaryFile) {
        int infile;
        if ((infile = open(filename, O_RDONLY, "0600")) == -1) {
            fprintf(stderr, "Error: no such file (%s)\n", filename);
            exit(1);
        }
        read(infile, &npoints,   sizeof(int));
        read(infile, &nfeatures, sizeof(int));        

        /* allocate space for features[][] and read attributes of all objects */
        buf         = (float*) malloc(npoints*nfeatures*sizeof(float));
        features    = (float**)malloc(npoints*          sizeof(float*));
        features[0] = (float*) malloc(npoints*nfeatures*sizeof(float));
        for (i=1; i<npoints; i++)
            features[i] = features[i-1] + nfeatures;
        read(infile, buf, npoints*nfeatures*sizeof(float));
        close(infile);
	}
	else {
        FILE *infile;
        if ((infile = fopen(filename, "r")) == NULL) {
            fprintf(stderr, "Error: no such file (%s)\n", filename);
            exit(1);
	}		
        while (fgets(line, 1024, infile) != NULL)
		if (strtok(line, " \t\n") != 0)
			npoints++;			
        rewind(infile);
        while (fgets(line, 1024, infile) != NULL) {
            if (strtok(line, " \t\n") != 0) {
                /* ignore the id (first attribute): nfeatures = 1; */
                while (strtok(NULL, " ,\t\n") != NULL) nfeatures++;
                break;
            }
        }        

        /* allocate space for features[] and read attributes of all objects */
        buf         = (float*) malloc(npoints*nfeatures*sizeof(float));
        features    = (float**)malloc(npoints*          sizeof(float*));
        features[0] = (float*) malloc(npoints*nfeatures*sizeof(float));
        for (i=1; i<npoints; i++)
            features[i] = features[i-1] + nfeatures;
        rewind(infile);
        i = 0;
        while (fgets(line, 1024, infile) != NULL) {
            if (strtok(line, " \t\n") == NULL) continue;            
            for (j=0; j<nfeatures; j++) {
                buf[i] = atof(strtok(NULL, " ,\t\n"));             
                i++;
            }            
        }
        fclose(infile);
	}
	printf("[BENCH] CUDA Kmeans from Rodinia\n");
//	printf("I/O completed\n");
	printf("[BENCH] Number of objects: %d\n", npoints);
	printf("[BENCH] Number of features: %d\n", nfeatures);
	printf("[BENCH] Number of Iteration: %d\n", nloops);

	/* ============== I/O end ==============*/
	if (npoints < min_nclusters) {
		printf("Error: min_nclusters(%d) > npoints(%d) -- cannot proceed\n", min_nclusters, npoints);
		exit(0);
	}

	srand(7);/* seed for future random number generator */	
	memcpy(features[0], buf, npoints*nfeatures*sizeof(float)); /* now features holds 2-dimensional array of features */
	free(buf);

	/* ======================= core of the clustering ===================*/
	cluster_centres = NULL;
	index = cluster(npoints,	/* number of data points */
		nfeatures,		/* number of features for each point */
		features,		/* array: [npoints][nfeatures] */
		min_nclusters,		/* range of min to max number of clusters */
		max_nclusters,
		threshold,		/* loop termination factor */
		&best_nclusters,	/* return: number between min and max */
		&cluster_centres,	/* return: [best_nclusters][nfeatures] */  
		&rmse,			/* Root Mean Squared Error */
		isRMSE,			/* calculate RMSE */
		nloops			/* number of iteration for each number of clusters */
	);

	printf("[BENCH] Writing output to <result.txt>\n");
	FILE *fpo = fopen("result.txt","w");
	if((min_nclusters == max_nclusters)) {
		for(i = 0; i < max_nclusters; i++){
			fprintf(fpo, "%d:", i);
			for(j = 0; j < nfeatures; j++){
				fprintf(fpo, " %.2f", cluster_centres[i][j]);
			}
			fprintf(fpo, "\n\n");
		}
	}
	fclose(fpo);
	
	len = (float) ((max_nclusters - min_nclusters + 1)*nloops);
	if(min_nclusters != max_nclusters){
		if(nloops != 1) {
			printf("Best number of clusters is %d\n", best_nclusters);
		}
		else{
			printf("Best number of clusters is %d\n", best_nclusters);
		}
	}
	else{
		if(nloops != 1){
			if(isRMSE)
				printf("Number of trials to approach the best RMSE of %.3f is %d\n", rmse, index + 1);
		}
		else{
			if(isRMSE)
				printf("Root Mean Squared Error: %.3f\n", rmse);
		}
	}

	free(features[0]);
	free(features);    
	return(0);
}

