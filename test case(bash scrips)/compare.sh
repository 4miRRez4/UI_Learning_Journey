#! /bin/zsh

if diff -u "$inputs.txt" "$outputs.txt"; then
	echo "Congratulations! They're all true."
else
	:
fi
