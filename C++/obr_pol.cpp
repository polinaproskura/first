#include <iostream>
#include <fstream>

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
		else if ((c == '(') || (c == '+') || (c == '-') || (c == '*') || (c == '/' )){
			St.arr_[St.length_] = c;
			++St;
		} else if (c == ')') {
			do{
				File << St.arr_[St.length_] << " ";
				--St;
			} while ((St.arr_[St.length_ - 1] != '(') || (St.length_ != 0));
		}
	} while (c != '=');
	File.close();
	return 0;
}
