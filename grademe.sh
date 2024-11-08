#!/bin/bash

PATH_TEST="$(cd "$(dirname "$0")" && pwd -P)"

exec 2> /dev/null

source "${PATH_TEST}"/src/check_compilation.sh
source "${PATH_TEST}"/src/check_file.sh
source "${PATH_TEST}"/src/color.sh
source "${PATH_TEST}"/src/diff_test.sh
source "${PATH_TEST}"/src/end_test.sh
source "${PATH_TEST}"/src/init_config.sh
source "${PATH_TEST}"/src/init_deepthought.sh
source "${PATH_TEST}"/src/select_project.sh
source "${PATH_TEST}"/src/start_test.sh
source "${PATH_TEST}"/src/testcase.sh
source "${PATH_TEST}"/src/util.sh
source "${PATH_TEST}"/src/variable.sh

cd "${PATH_TEST}"

init_config

clear

init_deepthought

#select_project

check_file

sleep 1.5

check_compilation
if [ $retvalue -eq 1 ]; then
	printf "${COLOR_FAIL}Test exited.${DEFAULT}\n\n"
	printf "A deepthought file has been created in ${UNDERLINE}${COLOR_DEEPTHOUGHT_PATH}\"${PATH_DEEPTHOUGHT}\"\n${DEFAULT}"
	exit
fi

sleep 1.5

start_test

end_test