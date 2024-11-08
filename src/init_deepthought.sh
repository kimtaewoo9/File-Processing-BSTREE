#!/bin/bash

init_deepthought() {
	mkdir -p "${PATH_DEEPTHOUGHT}"

	if [ -e "${PATH_DEEPTHOUGHT}"/deepthought ]; then
		rm -f "${PATH_DEEPTHOUGHT}"/deepthought
	fi
	
	text="= Host-specific information "
	printf "${text}" >> "${PATH_DEEPTHOUGHT}"/deepthought
	printf "%.s=" $(seq 1 $(( 80 - ${#text} ))) >> "${PATH_DEEPTHOUGHT}"/deepthought
	printf "\n$> hostname; uname -msr\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
	hostname >> "${PATH_DEEPTHOUGHT}"/deepthought
	uname -msr >> "${PATH_DEEPTHOUGHT}"/deepthought
	printf "\n$> date\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
	date >> "${PATH_DEEPTHOUGHT}"/deepthought
	printf "\n$> clang --version\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
	clang --version >> "${PATH_DEEPTHOUGHT}"/deepthought
	printf "\n$> clang++ --version\n" >> "${PATH_DEEPTHOUGHT}"/deepthought
	clang++ --version >> "${PATH_DEEPTHOUGHT}"/deepthought
}