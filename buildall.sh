#!bin/bash

BENCHMARKS=`ls -1 -F | awk '/\//' | sed 's/\///'`;
BENCHMARKS="aes backprop barneshut BFS2 bfs-rod blk cc cfd dlb hotspot IIX kmeans KMN lavaMD lbm LBM2 lps lud mum NeuralNetwork nn NN nw pvc pvr ray sad SM spmv srad1 srad2 ssc streamcluster SYRK vecAdd wave WC wp pathfinder bitonicSort FWT MonteCarlo quasirandomGenerator reduction sad scan SCP"

if [ $# > 1 ] && [ $1 == "clean" ] 
then 
    for BMK in $BENCHMARKS;
    do
        cd $BMK
        make clean
        cd ..
    done
else
    for BMK in $BENCHMARKS;
    do
        make -C $BMK
        if [ $? != 0 ] 
        then 
            exit 0
        fi 
    done
fi
@
