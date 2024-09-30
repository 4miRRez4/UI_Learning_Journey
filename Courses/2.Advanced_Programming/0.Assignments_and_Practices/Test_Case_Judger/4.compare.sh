#! /bin/zsh

if diff -u "outputOfCode.txt" "combinedOutputs.txt"; then
	echo "Congratulations! They're all true."
else
	:
fi
