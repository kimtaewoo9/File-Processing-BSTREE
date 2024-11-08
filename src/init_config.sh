#!/bin/bash

init_config() {
	echo "init_config"
	
	if [ ! -e "${PATH_TEST}"/my_config.sh ]; then
		printf "${BOLD}my_config.sh${DEFAULT} file is not found\n"
		printf "Creating file...\n"
		if [ -e "${PATH_TEST}"/src/config_template.sh ]; then
			cp "${PATH_TEST}"/src/config_template.sh "${PATH_TEST}"/my_config.sh
			printf "File created with success in ${BOLD}${PURPLE}${PATH_TEST}\n${DEFAULT}"
			printf "${RED}${UNDERLINE}Edit my_config.sh file${DEFAULT} with the path of your project and launch script.\n"
		else
			printf "Can't create my_config.sh file, try to update or clone again the repository and retry.\n"
			exit
		fi
		exit
	fi

	source "${PATH_TEST}"/my_config.sh
}