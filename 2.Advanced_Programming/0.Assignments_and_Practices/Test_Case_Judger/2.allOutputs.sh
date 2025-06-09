#! /bin/zsh

echo "please enter number of output files you have: "

read numberOfFiles

for ((i=1; i<numberOfFiles; i++))
do
	cat "output$i.txt" >> combinedOutputs.txt
	echo >> combinedOutputs.txt
done
echo "Done."
