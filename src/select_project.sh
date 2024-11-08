#!/bin/bash

select_project() {
	text="SELECT PROJECT"
	printf "${COLOR_TITLE}"
	printf "%.s${CHAR_LENGTH}" $(seq 1 ${TITLE_LENGTH})
	printf "\n${CHAR_WIDTH}\033[$(( (${TITLE_LENGTH} - ${#text}) / 2 ))G${text}\033[${TITLE_LENGTH}G${CHAR_WIDTH}\n"
	printf "%.s${CHAR_LENGTH}" $(seq 1 ${TITLE_LENGTH})
	printf "\n\n${DEFAULT}"

	printf "(1) Binary Search Tree\n\n"
	printf "(2) AVL Tree\n\n"
	printf "(3) B Tree\n\n"
	printf "(4) Exit\n\n"

	printf "Choose an option: [1-4]: "

	select opt in "Binary Search Tree" "AVL Tree" "B Tree" "Exit"; do
		case $opt in
			"Binary Search Tree")
				PROJECT="__bstree"
				printf "\n"
				break
				;;
			"AVL Tree")
				PROJECT="__avltree"
				printf "\n"
				break
				;;
			"B Tree")
				PROJECT="__btree"
				printf "\n"
				break
				;;
			"Exit")
				printf "\nTest exited.\n"
				exit
				;;
			*)
				printf "${COLOR_FAIL}\nInvalid option. Test exited.\n${DEFAULT}"
				exit
				;;
		esac
	done
}