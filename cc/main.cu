
/********************************************************************************************
* Implementing Graph Cuts on CUDA using algorithm given in CVGPU '08                       ** 
* paper "CUDA Cuts: Fast Graph Cuts on GPUs"                                               **
* Copyright (c) 2008 International Institute of Information Technology.                    **  
* All rights reserved.                                                                     **
* Created By Vibhav Vineet.                                                                ** 
********************************************************************************************/

#include "CudaCuts.cu"
#include "Example.h"
#include <assert.h>

using namespace std; 

int main(int argc, char** argv) {
	assert(argc >= 2);
	load_files(argv[1]);
	int initCheck = cudaCutsInit(gRealSizeX, gRealSizeY ,num_Labels) ;
//	printf("Compute Capability %d\n",initCheck);
	if( initCheck > 0 ) {
//		printf("The grid is initialized successfully\n");
	}
	else 
		if( initCheck == -1 ) {
			printf("Error: Please check the device present on the system\n");
		}
	int dataCheck   =  cudaCutsSetupDataTerm( dataTerm );
	if( dataCheck == 0 ) {
//		printf("The dataterm is set properly\n");	
	}
	else 
		if( dataCheck == -1 ) {
			printf("Error: Please check the device present on the system\n");
		}
	int smoothCheck =  cudaCutsSetupSmoothTerm( smoothTerm );
	if( smoothCheck == 0 ) {
//		printf("The smoothnessterm is set properly\n");
	}
	else
		if( smoothCheck == -1 ) {
			printf("Error: Please check the device present on the system\n");
		}
	int hcueCheck   =  cudaCutsSetupHCue( hCue );
	if( hcueCheck == 0 ) {
//		printf("The HCue is set properly\n");
	}
	else
		if( hcueCheck == -1 ) {
			printf("Error: Please check the device present on the system\n");
		}
	int vcueCheck   =  cudaCutsSetupVCue( vCue );
	if( vcueCheck == 0 ) {
//		printf("The VCue is set properly\n");
	}
	else 
		if( vcueCheck == -1 ) {
			printf("Error: Please check the device present on the system\n");
		}
	int graphCheck = cudaCutsSetupGraph();
	if( graphCheck == 0 ) {
//		printf("The graph is constructed successfully\n");
	}
	else 
		if( graphCheck == -1 ) {
			printf("Error: Please check the device present on the system\n");
		}
	int optimizeCheck = -1; 
	if( initCheck == 1 ) {
		// Get energy before starting
//		printf("\nStarting energies...\n");
		cudaCutsGetEnergy( );
//		printf("\n\n");
		//CudaCuts involving atomic operations are called
		optimizeCheck = cudaCutsAtomicOptimize();
		//CudaCuts involving stochastic operations are called
		//optimizeCheck = cudaCutsStochasticOptimize();
	}
	if( optimizeCheck == 0 ) {
		printf("The algorithm successfully converged\n");
	}
	else 
		if( optimizeCheck == -1 ) {
			printf("Error: Please check the device present on the system\n");
		}
	int resultCheck = cudaCutsGetResult( );
	if( resultCheck == 0 ) {
		printf("The pixel labels are successfully stored\n");
	}
	else 
		if( resultCheck == -1 ) {
			printf("Error: Please check the device present on the system\n");
		}
//	printf("\nFinal energies...\n");
	int energy = cudaCutsGetEnergy();
//	printf("\n\n");
	initFinalImage();
	cudaCutsFreeMem();
	exit(1);
//	CUT_EXIT(argc,argv);
}

void load_files(char *filename) {
	LoadDataFile(filename, gRealSizeX, gRealSizeY, num_Labels, dataTerm, smoothTerm, hCue, vCue);
}

void initFinalImage() {
	out_pixel_values=(int**)malloc(sizeof(int*)*gRealSizeY);
	for(int i = 0 ; i < gRealSizeY ; i++ ) {
		out_pixel_values[i] = (int*)malloc(sizeof(int) * gRealSizeX );
		for(int j = 0 ; j < gRealSizeX ; j++ ) {
			out_pixel_values[i][j]=0;
		}
	}
	writeImage() ;
}

void writeImage() {
	for(int i = 0 ; i <  gSizeTotal ; i++) {
		int row = i / gSizeX, col = i % gSizeX ;
		if(row >= 0 && col >= 0 && row <= gRealSizeY -1 && col <= gRealSizeX - 1 )
			out_pixel_values[row][col]=pixelLabel[i]*255;
	}
	write_image();
}

void write_image() {
	FILE* fp=fopen("result_cuda_test.pgm","w");
	fprintf(fp,"%c",'P');
	fprintf(fp,"%c",'2');
	fprintf(fp,"%c",'\n');
	fprintf(fp,"%d %c %d %c ",gRealSizeX,' ',gRealSizeY,'\n');
	fprintf(fp,"%d %c",255,'\n');
	for(int i=0;i<gRealSizeY;i++) {
		for(int j=0;j<gRealSizeX;j++) {
			fprintf(fp,"%d\n",out_pixel_values[i][j]);
		}
	}
	fclose(fp);
}

void write_data_to_file(char *filename, int my_width, int my_height, int skip, int max, int *data) {
	FILE* fp=fopen(filename,"w");
	fprintf(fp,"%c",'P');
	fprintf(fp,"%c",'2');
	fprintf(fp,"%c",'\n');
	fprintf(fp,"%d %c %d %c ",my_width,' ',my_height,'\n');
	fprintf(fp,"%d %c",max,'\n');
	for(int i=0;i<gRealSizeY * gRealSizeX * skip; i += skip) {
		fprintf(fp,"%d\n",data[i]);
	}
	fclose(fp);
}

void SubsampleData(int ratio, int width, int height, int *srcData, int *&dstData) {
   assert( width % ratio == 0 ); 
   assert( height % ratio == 0 );
   int dstWidth = width / ratio; 
   int dstHeight = height / ratio; 

   // allocation and initialization
   dstData = new int[dstWidth * dstHeight]; 
   for (int n = 0; n < dstHeight * dstWidth; n++) 
      dstData[n] = 0; 

   // summation of multiple pixel to a single destionation
   for (int y = 0; y < height; y++) {
      int dy = y / ratio; 
      for (int x = 0; x < width; x++) {
         int dx = x / ratio; 
         int n = x + y * width; 
         dstData[dx + dy * dstWidth] += srcData[n]; 
      }
   }

   // normalize 
   int ratiosq = ratio * ratio; 
   for (int n = 0; n < dstHeight * dstWidth; n++) 
      dstData[n] /= ratiosq; 
}


void WriteSubsampleDataSet(char *filename, int width, int height, int nLabels, int ratio, int *dataCostArray, int *smoothCostArray, int *hCue, int *vCue) {
	int dstWidth = width / ratio; 
	int dstHeight = height / ratio; 
	int i, n, x, y;
	FILE *fp = fopen(filename, "w"); 

   // demux the data cost array 
   int *dataCostArray0 = new int[width * height]; 
   int *dataCostArray1 = new int[width * height]; 
   for (n = 0; n < width * height; n++) {
      dataCostArray0[n] = dataCostArray[n * nLabels + 0]; 
      dataCostArray1[n] = dataCostArray[n * nLabels + 1]; 
   }
   int *d_Cost0;
   int *d_Cost1; 
   int *d_hCue; 
   int *d_vCue;
   SubsampleData(ratio, width, height, dataCostArray0, d_Cost0); 
   SubsampleData(ratio, width, height, dataCostArray1, d_Cost1); 
   SubsampleData(ratio, width, height, hCue, d_hCue); 
   SubsampleData(ratio, width, height, vCue, d_vCue); 

	fprintf(fp,"%d %d %d \n",dstWidth,dstHeight,nLabels);
	printf("[WriteSubsampleDataSet] width=%d height=%d nLabels=%d\n", dstWidth, dstHeight, nLabels);

	int gt = 1;
	for(i = 0; i < dstWidth * dstHeight; i++)
		fprintf(fp,"%d ",gt);
	fprintf(fp, "\n"); 

	assert(nLabels == 2); 
	for(n = 0; n < dstWidth * dstHeight; n++) {
		fprintf(fp,"%d ",d_Cost0[n]);
	}
	fprintf(fp, "\n"); 
	for(n = 0; n < dstWidth * dstHeight; n++) {
		fprintf(fp,"%d ",d_Cost1[n]);
	}
	fprintf(fp, "\n"); 

	n = 0;
	for(y = 0; y < dstHeight; y++) {
		for(x = 0; x < dstWidth-1; x++) {
			fprintf(fp,"%d ",d_hCue[n++]);
		}
		n++; // skip one blank column.... 
	}
	fprintf(fp, "\n"); 

	n = 0;
	for(y = 0; y < dstHeight-1; y++) {
		for(x = 0; x < dstWidth; x++) {
			fprintf(fp,"%d ",d_vCue[n++]);
		}
	}
	// skip the last row
	fprintf(fp, "\n");
	fclose(fp);
	delete[] d_Cost0;
	delete[] d_Cost1; 
	delete[] d_hCue; 
	delete[] d_vCue; 
	delete[] dataCostArray0; 
	delete[] dataCostArray1; 
}

void LoadDataFile(char *filename, int &width, int &height, int &nLabels, int *&dataCostArray, int *&smoothCostArray, int *&hCue, int *&vCue) {
//	printf("enterd\n");
	FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d %d %d",&width,&height,&nLabels);
	printf("width=%d height=%d nLabels=%d\n", width, height, nLabels);
	int i, n, x, y;
	int gt;
	for(i = 0; i < width * height; i++)
		fscanf(fp,"%d",&gt);
	dataCostArray = new int[width * height * nLabels];
	for(int c=0; c < nLabels; c++) {
		n = c;
		for(i = 0; i < width * height; i++) {
			fscanf(fp,"%d",&dataCostArray[n]);
			n += nLabels;
		}
	}
	write_data_to_file("datacost0.pgm", width, height, 2, 16384, dataCostArray); 
	write_data_to_file("datacost1.pgm", width, height, 2, 16384, dataCostArray + 1); 
	hCue = new int[width * height];
	vCue = new int[width * height];
	n = 0;
	for(y = 0; y < height; y++) {
		for(x = 0; x < width-1; x++) {
			fscanf(fp,"%d",&hCue[n++]);
		}
		hCue[n++] = 0;
	}
	write_data_to_file("hCue.pgm", width, height, 1, 1024, hCue);
	n = 0;
	for(y = 0; y < height-1; y++) {
		for(x = 0; x < width; x++) {
			fscanf(fp,"%d",&vCue[n++]);
		}
	}
	for(x = 0; x < width; x++) {
		vCue[n++] = 0;
	}
	write_data_to_file("vCue.pgm", width, height, 1, 1024, hCue); 
	fclose(fp);
	smoothCostArray = new int[nLabels * nLabels];
	smoothCostArray[0] = 0 ;
	smoothCostArray[1] = 1 ;
	smoothCostArray[2] = 1 ;
	smoothCostArray[3] = 0 ;
   // create subsampled working set 
   // WriteSubsampleDataSet("flower2.txt", width, height, nLabels, 2, dataCostArray, smoothCostArray, hCue, vCue); 
   // WriteSubsampleDataSet("flower3.txt", width, height, nLabels, 3, dataCostArray, smoothCostArray, hCue, vCue); 
   // WriteSubsampleDataSet("flower5.txt", width, height, nLabels, 5, dataCostArray, smoothCostArray, hCue, vCue); 
}

