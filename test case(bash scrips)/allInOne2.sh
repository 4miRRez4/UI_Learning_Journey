#! /bin/zsh

echo "please enter number of input files you have: "

read numberOfFiles

for ((i=1; i<numberOfFiles; i++))
do
	cat "input$i.txt" >> combined.txt
done
echo "Done."
