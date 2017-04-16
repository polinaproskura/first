#include <iostream>

class Node {
	public:
		int format_number;
		char x_; //1
		double num_; //2
		char oper_;     //3       
		int sub_Node;
    	Node* left_;  
    	Node* right_;
		Node() : left_(NULL), right_(NULL){
			format_number = 0;
			x_ = 0;
			num_ = 0;
			oper_ = 0;
			sub_Node = 0;
			std::cout << "Constructor works" << std::endl;
		};
		~Node(){
			std::cout << "Destructor works" << std::endl;	
		};
		
};

int main() {
	//предположим, что я уже написала работающий итератор для дерева
	int i = 0;
	while (c != '='){
		std::cin >> c;
		if ((c >= '0') && (c <= '9')){
			Node a[i];
			a[i].format_number = 2;
			a[i].num_ = (int)c - 48;
			i++;
		} else if ((c == '+') || (c == '-') || (c == '*') || (c == '/' ) || (c == '^')){
			Node a[i];
			a[i].format_number = 3;
			a[i].oper_ = c;
			a[i].left_ = //ближайший неприсвоенный, написать функцию поиска
			a[i].right_ = //ближайший неприсвоенный с учетом предыдущего
			i++;
		} else if ((c >= 'a') && (c <= 'z')){
			Node a[i];
			a[i].format_number = 1;
			a[i].x_ = c;
			i++;
		}
	}
	Node a;
	return 0;
}
