#include <iostream>
#include <fstream>
#include <assert.h>

 
int priority(char c){
	if (c == '^')
		return 4;
	if ((c == '*') || (c == '/'))
		return 3;
	if ((c == '+') || (c == '-'))
		return 2;
	if ((c == '(') || (c == ')'))
		return 1;
}

class Stack_char
{
	public:
		int length_;
		char * arr_;
		Stack_char() : arr_(new char[100]){
			length_ = 0;
		};
		~Stack_char()
		{
			delete[] arr_;
			arr_ = NULL;
		};
		Stack_char& operator ++(){
			this->length_ ++;
			return *this;
		};
		Stack_char& operator --(){
			this->length_ --;
			return *this;
		};
		int Stack_Ok() {
			if ((0 <= length_) && (length_ <= 100)) return 1;
			return 0;
		}
		void Stack_Dump() {
			assert(Stack_Ok());
			std::cout << "length = " << length_ << std::endl;
			int i;
			std::cout << "Stack : ";
			for (i = 0; i < length_; i++){
				std::cout << arr_[i] << "; ";
			}
			std::cout << std::endl;
			std::cout << std::endl;
		};
};

int main() {
	std::ofstream File;
	File.open("obr_pol.txt");
	Stack_char St;
	char c;
	double x;
	do {
		std::cin >> c;
		if ((c >= '0') && (c <= '9')) {
			ungetc(c, stdin);
			std::cin >> x;
			File << x << " ";
		}
		else if ((c == '+') || (c == '-') || (c == '*') || (c == '/' ) || (c == '^')){
			while ((priority(c) <= priority(St.arr_[St.length_ - 1])) && (St.length_ != 0)){
				File << St.arr_[St.length_ - 1] << " ";
				--St;
			}
			St.arr_[St.length_] = c;
			++St;
		} else if (c == ')') {
			while (St.arr_[St.length_ - 1] != '(') {
				File << St.arr_[St.length_ - 1] << " ";
				--St;
				}
				--St;
		}  else if (c == '(') {
			St.arr_[St.length_] = c;
			++St;
		}	else if ((c >= 'a') && (c <= 'z')){
			File << c << " ";
		}
		St.Stack_Dump();
	} while (c != '=');
	while (St.length_ != 0) {
		File << St.arr_[St.length_ - 1] << " ";
		--St;
	}
	File << "=";
	File.close();
	std::cout << "the end" << std::endl;
	return 0;
}
