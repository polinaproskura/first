#include <iostream>
#include <cstring>

class CString{
	protected:
		const static int length_ = 100;
		char* str_;
	public:
		CString() : str_(new char[length_]){
			std::cin >> str_;
			std::cout << "Constructor works\n";
		};
		~CString(){
			delete[] str_;
			str_ = NULL;
			std::cout << "Destructor works\n";
		};
		char * Cstrstr(CString s1){
			return strstr(this->str_, s1.str_);
		}
		CString& Replace(CString s1, CString s2){
			char * pos1;
			char * pos2;
			pos1 = this->Cstrstr(s1);
			pos2 = pos1 + strlen(s1.str_);
			int i;
			for (i = 0; i < strlen(this->str_); i++)
			{
				this->pos1 + i = this->(pos2 + i);
			}
			strncpy(s2.str_, this->str_, strlen(s2.str_));
			std:: cout << this->str_;
			return *this;
		}
};


int main()
{
	CString s;
	CString s0;
	s.Cstrstr(s0);
	s.Replace(s0, "world");
	return 0;
}
