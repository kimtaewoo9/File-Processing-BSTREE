#!/bin/bash

check_compilation() {
	print_title "COMPILING"

	sleep 2

	if [ -e ${PATH_TEST}/user_exe ]; then
		rm -f ${PATH_TEST}/user_exe
	fi

	text="= Compiling "
	printf "\n${text}" >> "${PATH_DEEPTHOUGHT}"/deepthought
	printf "%.s=" $(seq 1 $(( 80 - ${#text} ))) >> "${PATH_DEEPTHOUGHT}"/deepthought

	printf "\n$> ${COMPILER} -Wall -Wextra -Werror -g3 ${PATH_SUBMIT}/${SRC_FILE} -o user_exe\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
	${COMPILER} -Wall -Wextra -Werror -g3 ${PATH_SUBMIT}/${SRC_FILE} -o user_exe 2>> "${PATH_DEEPTHOUGHT}"/deepthought
	FLAG=$?

	${COMPILER} -g3 ${PATH_SUBMIT}/${SRC_FILE} -o user_exe 2>> "${PATH_DEEPTHOUGHT}"/deepthought
	retvalue=$?

	printf "%-16s%-16s%-16s\n" "COMPILER" "RESULT" "-Wall -Wextra -Werror"
	printf "${COLOR_OK}%-16s${DEFAULT}" "${COMPILER}"
	if [ $retvalue -eq 0 ]; then
		printf "${COLOR_OK}%-16s${DEFAULT}" "success"
	else
		printf "${COLOR_FAIL}%-16s${DEFAULT}" "failure"
	fi
	if [ $FLAG -eq 0 ]; then
		printf "${COLOR_OK}%-16s${DEFAULT}" "success"
	else
		printf "${COLOR_FAIL}%-16s${DEFAULT}" "failure"
	fi

	printf "\n\n\n"

	make -s -C "${PATH_TEST}"/test ${PROJECT}

	return $retvalue
}