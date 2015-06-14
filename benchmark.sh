#!/bin/bash

[ ! -d result ] && mkdir result

if [ ! -d testdata ]
then
	echo No testdata found.
	exit 1
fi

for testdata in testdata/*.sql
do
	echo Running test $testdata
	result=${testdata%.*}
	result=${result##*/}
	psql/bin/psql < $testdata | tee result/${result}.txt
	echo Test $testdata done.
done
