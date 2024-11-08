#!/bin/bash

print_title() {
	text=$1
	
	printf "${COLOR_TITLE}"
	printf "%.s${CHAR_LENGTH}" $(seq 1 ${TITLE_LENGTH})
	printf "\n${DEFAULT}"
	
	TEXT_LENGTH=${#text}
	PADDING_LENGTH=$(( (${TITLE_LENGTH} - ${TEXT_LENGTH} - 2) / 2 ))
	EXTRA_PADDING=$(( (${TITLE_LENGTH} - ${TEXT_LENGTH} - 2) % 2 ))

	printf "${COLOR_TITLE}${CHAR_WIDTH}%*s%s%*s${CHAR_WIDTH}\n${DEFAULT}" ${PADDING_LENGTH} "" "${text}" $((${PADDING_LENGTH} + ${EXTRA_PADDING})) ""

	printf "${COLOR_TITLE}"
	printf "%.s${CHAR_LENGTH}" $(seq 1 ${TITLE_LENGTH})
	printf "\n\n${DEFAULT}"
}