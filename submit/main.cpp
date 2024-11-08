/*
* Dummy file입니다.
* 본인이 테스트하고 싶은 내용으로 변경 후 사용하세요.
*/

#include <iostream>

int main() {
	char	command;
	int		key;

	while (std::cin >> command >> key) {
		std::cout << command << " " << key << std::endl;
	}

	return (0);
}