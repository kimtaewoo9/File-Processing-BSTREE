#!/bin/bash

check_file() {
	print_title "CHECKING FILE"

	sleep 2

	if [ -e "${PATH_SUBMIT}/main.c" ]; then
		SRC_FILE="main.c"
		COMPILER="clang"
	elif [ -e "${PATH_SUBMIT}/main.cpp" ]; then
		SRC_FILE="main.cpp"
		COMPILER="clang++"
	else
		SRC_FILE="missing_source_file"
		COMPILER="missing_compiler"
	fi

	printf "SOURCE FILE\n"
	if [ -e "${PATH_SUBMIT}"/${SRC_FILE} ]; then
		printf "${COLOR_OK}found${DEFAULT}\n\n"
	else
		printf "${COLOR_FAIL}not found${DEFAULT}\n\n"
		printf "${COLOR_FAIL}Please provide a source file to test or check the path in ${UNDERLINE}my_config.sh${DEFAULT}\n"
		printf "${COLOR_FAIL}Test exited.${DEFAULT}\n"
		exit
	fi
}