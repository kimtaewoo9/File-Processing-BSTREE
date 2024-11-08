#!/bin/bash

timeout_test() {
	retvalue=0

	if command -v setarch &> /dev/null; then
		setarch $(uname -m) --addr-no-randomize timeout "${TIMEOUT_DURATION}" "${PATH_TEST}"/user_exe < "$1" > /dev/null 2>&1
	else
		timeout "${TIMEOUT_DURATION}" "${PATH_TEST}"/user_exe < "$1" > /dev/null 2>&1
	fi

	SIG=$?
	if [ $SIG -eq 124 ]; then
		printf "Command './user_exe < $1' got killed by a Timeout\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
		printf "%-4s${COLOR_FAIL}T${DEFAULT}\n"
		retvalue=1
	fi

	return $retvalue
}

leak_test() {
	retvalue=0

	if command -v setarch &> /dev/null; then
		setarch $(uname -m) --addr-no-randomize leaks --atExit -- "${PATH_TEST}"/user_exe < "$1" > leaks.log 2>&1
	else
		leaks --atExit -- "${PATH_TEST}"/user_exe < "$1" > leaks.log 2>&1 
	fi
	result=$(cat leaks.log)
	rm -f leaks.log

	if echo $result | grep -qv "0 leaks for 0 total leaked bytes"; then
		printf "Command './user_exe < $1' got leaks\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
		printf "%-4s${COLOR_FAIL}L${DEFAULT}\n"
		retvalue=1
	fi

	return $retvalue
}

diff_test() {
	text="\n= TEST CASE - $(basename "$1") "
	printf "${text}" >> "${PATH_DEEPTHOUGHT}"/deepthought
	printf "%.s=" $(seq 1 $(( 80 - ${#text} ))) >> "${PATH_DEEPTHOUGHT}"/deepthought
	printf "\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
	
	printf "$> ./user_exe < $(basename "$1")\n" >> "${PATH_DEEPTHOUGHT}"/deepthought

	timeout_test "$1"
	if [ $? -eq 1 ]; then
		return 1
	fi

	leak_test "$1"
	if [ $? -eq 1 ]; then
		return 1
	fi

	"${PATH_TEST}"/user_exe < "$1" > "${PATH_TEST}"/output/${PROJECT}/user_output_test_$(basename "$1") 2>&1
	SIG=$?
	if [ $SIG -eq 134 ]; then
		printf "Command './user_exe < $1' got killed by an Abort\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
		printf "%-4s${COLOR_FAIL}A${DEFAULT}\n"
		retvalue=1
	elif [ $SIG -eq 138 ]; then
		printf "Command './user_exe < $1' got killed by a Bus error\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
		printf "%-4s${COLOR_FAIL}B${DEFAULT}\n"
		retvalue=1
	elif [ $SIG -eq 139 ]; then
		printf "Command './user_exe < $1' got killed by a Segmentation fault\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
		printf "%-4s${COLOR_FAIL}S${DEFAULT}\n"
		retvalue=1
	else
		"${PATH_TEST}"/test/test_exe < "$1" > "${PATH_TEST}"/output/${PROJECT}/output_test_$(basename "$1") 2>&1
		DIFF=$(diff -u "${PATH_TEST}"/output/${PROJECT}/user_output_test_$(basename "$1") "${PATH_TEST}"/output/${PROJECT}/output_test_$(basename "$1"))
		printf "$> diff -u user_output_test_$(basename "$1") output_test_$(basename "$1")\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
		if [ "$DIFF" != "" ] || [ ! -e "${PATH_TEST}"/output/${PROJECT}/user_output_test_$(basename "$1") ]; then
			echo "${DIFF}" | cat -e >> "${PATH_DEEPTHOUGHT}"/deepthought
			printf "\nDiff KO :(\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
			printf "%-1s${COLOR_FAIL}[KO]${DEFAULT}\n"
			retvalue=1
		else
			printf "\nDiff OK :D\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
			printf "%-1s${COLOR_OK}[OK]${DEFAULT}\n"
			retvalue=0
		fi
	fi

	return $retvalue
}