#!/bin/sh

CONFIG_DIR=./config/to_nc_config

echo $1 $2

TEST_DIR=$1
OUT_DIR=$2
CURRENT_DIR=$PWD
BENCHMARK=`basename $TEST_DIR`

echo "run $BENCHMARK in $TEST_DIR, output to $CURRENT_DIR/$OUT_DIR/$BENCHMARK"

cp $CONFIG_DIR/* $TEST_DIR
cd $TEST_DIR
./run-sim > output.txt

if [ ! -d $OUT_DIR ] 
then
    mkdir $CURRENT_DIR/$OUT_DIR
fi

if [ ! -d $OUT_DIR/$BENCHMARK ] 
then
    mkdir $CURRENT_DIR/$OUT_DIR/$BENCHMARK
fi

cp output.txt ruby_stat.txt result.txt stats.txt ruby_timestamp0.txt $CURRENT_DIR/$OUT_DIR/$BENCHMARK
