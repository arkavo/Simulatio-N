#!/bin/bash
rm Table.txt 
loop() {
	while [ "foo" == "foo" ] 
	do
	./seq1.out
	./seq2.out
	cat List.txt
	done
}
loop & 
gnuplot liveplot.gnu
