#!/bin/bash

generate_testcase() {
	if [ $1 -lt 10 ]; then
		text="0"
	else
		text=""
	fi

	filename="${PATH_TEST}"/testcase/${PROJECT}/random${text}$1
	for i in {0..99}; do
		instruction=$(shuf -n 1 -e 'i' 'd')
		number=$(shuf -i 1-25 -n1)
		echo "$instruction $number" >> "$filename"
	done
}

remove_testcases() {
	rm -f "${PATH_TEST}"/testcase/${PROJECT}/random*
}

generate_testcases() {
	for i in $(seq 0 $(($1 - 1))); do
		generate_testcase $i
	done
}