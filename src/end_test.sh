#!/bin/bash

clean_up() {
	if [ -e "${PATH_TEST}/test/test_exe" ]; then
		make -C "${PATH_TEST}"/test fclean
	fi

	if [ -e "${PATH_TEST}/user_exe" ]; then
		rm -rf "${PATH_TEST}"/user_exe*
	fi

	rm -rf "${PATH_TEST}/output"
}

end_test() {
	clean_up

	sleep 3

	printf "A deepthought file has been created in ${UNDERLINE}${COLOR_DEEPTHOUGHT_PATH}\"${PATH_DEEPTHOUGHT}\"\n${DEFAULT}"
}
