#!/bin/bash

for i in {1..64};
do
	cat sample/1.html >> data/1.html
	cat sample/2.html >> data/2.html
	cat sample/3.html >> data/3.html
done;

