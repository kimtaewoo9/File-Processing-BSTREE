#!/bin/bash

test_cases() {
	cases=($(find "${PATH_TEST}"/testcase/${PROJECT} $1 | sort))
	total=${#cases[@]}
	let "i=0"
	let "success=0"
	while [ $i -lt $total ]; do
		if [ $i -lt 10 ]; then
			text="0"
		else
			text=""
		fi
		printf "${COLOR_TESTCASE}%-75s${DEFAULT}" "#${text}$i"
		diff_test "${cases[$i]}"
		if [ $? -eq 0 ]; then
			let "success += 1"
		fi
		let "i += 1"
		sleep 0.5
	done

	if [ $total -lt 10 ]; then
		total="0${total}"
	fi
	if [ $success -lt 10 ]; then
		success="0${success}"
	fi

	printf "\n${COLOR_TOTAL}Total: ${success}/${total}${DEFAULT}\n\n\n"

	if [ $success -eq $total ]; then
		retvalue=0
	else
		retvalue=1
	fi

	return $retvalue
}

test_simple_case() {
	printf "${COLOR_PART}${UNDERLINE}TEST SIMPLE CASES\n\n${DEFAULT}"
	printf "${COLOR_TITLE}${UNDERLINE}TEST CASE${DEFAULT}"
	printf "%-65s"
	printf "${COLOR_TITLE}${UNDERLINE}RESULT\n${DEFAULT}"

	test_cases "-type f -name simple*"

	return $?
}

test_random_case() {
	printf "${COLOR_PART}${UNDERLINE}TEST RANDOM CASES\n\n${DEFAULT}"
	printf "${COLOR_TITLE}Generate test cases... "
	generate_testcases 5
	printf "done\n\n${DEFAULT}"
	sleep 1
	printf "${COLOR_TITLE}${UNDERLINE}TEST CASE${DEFAULT}"
	printf "%-65s"
	printf "${COLOR_TITLE}${UNDERLINE}RESULT\n${DEFAULT}"

	test_cases "-type f -name random*"

	remove_testcases

	return $?
}

test_user_defined_case() {
	printf "${COLOR_PART}${UNDERLINE}TEST USER DEFINED CASES\n\n${DEFAULT}"
	printf "${COLOR_TITLE}${UNDERLINE}TEST CASE${DEFAULT}"
	printf "%-65s"
	printf "${COLOR_TITLE}${UNDERLINE}RESULT\n${DEFAULT}"

	test_cases "-type f -not -name simple* -not -name random* -not -name *output* -not -name .DS_Store -not name README.md"

	return $?
}

start_test() {
	print_title "STARTING TESTS"

	mkdir -p "${PATH_TEST}"/output/${PROJECT}

	let "failed=0"
	TEST_FUNCTIONS=("test_simple_case" "test_random_case" "test_user_defined_case")
	for TEST_FUNCTION in "${TEST_FUNCTIONS[@]}"; do
		sleep 2
		${TEST_FUNCTION}
		if [ $? -eq 1 ]; then
			let "failed += 1"
		fi
	done

	if [ $failed -ne 0 ]; then
		printf "Fail: ${RED}[KO]${DEFAULT}  Abort: ${RED}A${DEFAULT}  Bus error: ${RED}B${DEFAULT}  Segmentation fault: ${RED}S${DEFAULT}  Timeout: ${RED}T${DEFAULT}  Leak: ${RED}L${DEFAULT}\n\n"
	fi

	return $retvalue
}