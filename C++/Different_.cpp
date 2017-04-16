#include <iostream>
#include <fstream>
#include <cstring>
#define Length 5

enum Func {
	sin,
	cos,
	tg,
	ctg,
	ln,
};


class Node{
	public:
		int Format_;
		int Number_; // format 1
		char Operator_; // format 2
		char Variable_; // format 3
		Node * Left_;
		Node * Right_;
		Node(){
			Format_ = 0;
			Right_ = NULL;
			Left_ = NULL;
			//std::cout << "Constructor works\n";
		};
		~Node(){
			//std::cout << "Destructor works\n";
		};
		Node * Read_(){
			char c;
			do{
				std::cin >> c;
				if (c == '('){
					if (this->Left_ == NULL){
						this->Left_ = new Node;
						this->Left_ = this->Left_->Read_();
					} else {
						this->Right_ = new Node;
						this->Right_ = this->Right_->Read_();
					}
				}
				if ((c == '+') || (c == '-') || (c == '*') || (c == '/' ) || (c == '^')){
					this->Format_ = 2;
					this->Operator_ = c;
				}
				if ((c >= '0') && (c <= '9')) {
					ungetc(c, stdin);
					this->Format_ = 1;
					std::cin >> this->Number_;
				}
				if ((c >= 'a') && (c <= 'z')){
					this->Format_ = 3;
					this->Variable_ = c;
				}
			} while (c != ')');
			return this;
		};
		
		void Node_Dump(){
			if (this->Format_ != 0){
				std::cout << "(";
				
				if (this->Left_ != NULL) 
					this->Left_->Node_Dump();
				if (this->Format_ == 1)
					std::cout << this->Number_;
				if (this->Format_ == 2)
					std::cout << this->Operator_;
				if (this->Format_ == 3)
					std::cout << this->Variable_;
				
				if (this->Right_ != NULL)
					this->Right_->Node_Dump();
				std::cout << ")"; 
			} else std::cout << "Empty\n";
		};
		
		void Generate_Labels(std::ofstream * File, int * a){
			int c = (*a);
			(*a)++;
			if (this->Format_ != 0){
				
				if (this->Format_ == 1)
					*File << "l" << c << "[label = " << this->Number_ << "];\n";
				if (this->Format_ == 2)
					*File << "l" << c << "[label = \"" << this->Operator_ << "\"];\n";
				if (this->Format_ == 3)
					*File << "l" << c << "[label =  "<< this->Variable_ << "];\n";
				
				if (this->Left_ != NULL){
					this->Left_->Generate_Labels(File, a);
				}
				
				if (this->Right_ != NULL){			
					this->Right_->Generate_Labels(File, a);
				}
			}
		}
		
		void Dump_InFile(std::ofstream * File, int * a){
			int c = (*a);
			(*a)++;
			if (this->Format_ != 0){
				*File << "l" << c;
				
				if (this->Left_ != NULL){
					*File << "->";
					this->Left_->Dump_InFile(File, a);
				}
				
				
				if (this->Right_ != NULL){
					*File << "l" << c << "->";
					this->Right_->Dump_InFile(File, a);
				}
				
				if ((this->Right_ == NULL) && (this->Left_ == NULL))
					*File << ";\n";
			}			
		}
		
		Node& operator = (int i){
			this->Format_ = 1;
			this->Number_ = i;
			this->Left_ = NULL;
			this->Right_ = NULL;
			return *this;
		}
		Node& operator = (char c){
			if (((c == '+') || (c == '-') || (c == '*') || (c == '/' ) || (c == '^'))){
				this->Format_ = 2;
				this->Operator_ = c;
				this->Left_ = NULL;
				this->Right_ = NULL;
			}
			else {
				this->Format_ = 3;
				this->Variable_ = c;
				this->Left_ = NULL;
				this->Right_ = NULL;
			}
			return *this;
		}
		Node& operator = (Node& a){
			this->Format_ = a.Format_;
			if (a.Left_ != NULL){
				this->Left_ = a.Left_;
			} else {
				this->Left_ = NULL;
			}
			if (a.Right_ != NULL){
				this->Right_ = a.Right_;
			} else {
				this->Right_ = NULL;
			}
			if (a.Format_ == 1){
				this->Number_ = a.Number_;
			}
			if (a.Format_ == 3){
				this->Variable_ = a.Variable_;
			}
			if (a.Format_ == 2){
				this->Operator_ = a.Operator_;
			}
			return *this;
		}
		Node * Optimization(){
			if (this->Left_ != NULL){
				this->Left_->Optimization();
			}
			if (this->Right_ != NULL){
				this->Right_->Optimization();
			}
			// null and one operations
			if (this->Format_ == 2){
				if (this->Operator_ == '*'){
					if ((this->Left_->Format_ == 1) && (this->Left_->Number_ == 0)){
						*this = *(this->Left_);
					} else if ((this->Right_->Format_ == 1) && (this->Right_->Number_ == 0)){
						*this = *(this->Right_);
					} else if ((this->Right_->Format_ == 1) && (this->Right_->Number_ == 1)){
						*this = *(this->Left_);
					} else if ((this->Left_->Format_ == 1) && (this->Left_->Number_ == 1)){
						*this = *(this->Right_);
					}
				}
				if (this->Operator_ == '/'){
					if ((this->Left_->Format_ == 1) && (this->Left_->Number_ == 0)){
						*this = this->Left_->Number_;
					} else if ((this->Right_->Format_ == 1) && (this->Right_->Number_ == 1)){
						*this = *(this->Left_);
					}
				}
				if (this->Operator_ == '+'){
					if ((this->Left_->Format_ == 1) && (this->Left_->Number_ == 0)){
						*this = *(this->Right_);
					} else if ((this->Right_->Format_ == 1) && (this->Right_->Number_ == 0)){
						*this = *(this->Left_);
					}
				}
				if (this->Operator_ == '-'){
					if ((this->Right_->Format_ == 1) && (this->Right_->Number_ == 0)){
						*this = this->Left_->Number_;
					}	
				}	
			}
			//constant nodes
			if ((this->Format_ == 2) && (this->Left_->Format_ == 1) && (this->Right_->Format_ == 1)){
				if (this->Operator_ == '*'){
					*this =(int) (this->Left_->Number_ * this->Right_->Number_);
				}
				else if (this->Operator_ == '/'){
					*(this) = (int)((this->Left_->Number_) / (this->Right_->Number_));
				}
				else if (this->Operator_ == '+'){
					*(this) = (int)((this->Left_->Number_) + (this->Right_->Number_));
				}
				else if (this->Operator_ == '-'){
					*(this) = (int)((this->Left_->Number_) - (this->Right_->Number_));
				}
			}
		}
		Node * Diff_(){
			Node New_Node;
			if (this->Format_ == 1){
				New_Node = 0;
			} else if (this->Format_ == 3){
				New_Node = 1;
			} else if (this->Format_ == 2){
				if (this->Operator_ == '+'){
					New_Node = '+';
					New_Node.Left_ = new Node;
					New_Node.Right_ = new Node;
					*(New_Node.Left_) = *(this->Left_->Diff_());
					*New_Node.Right_ = *this->Right_->Diff_();
				}
				if (this->Operator_ == '-'){
					New_Node = '-';
					New_Node.Left_ = new Node;
					New_Node.Right_ = new Node;
					*New_Node.Left_ = *this->Left_->Diff_();
					*New_Node.Right_ = *this->Right_->Diff_();
				}
				if (this->Operator_ == '*'){
					New_Node = '+';
					
					New_Node.Left_ = new Node;
					New_Node.Right_ = new Node;
					*New_Node.Left_ = '*';
					*New_Node.Right_ = '*';
					
					New_Node.Right_->Left_ = new Node;
					New_Node.Left_->Left_ = new Node;
					New_Node.Left_->Right_ = new Node;
					New_Node.Right_->Right_ = new Node;
					
					*New_Node.Left_->Left_ = *this->Left_->Diff_();
					*New_Node.Left_->Right_ = *this->Right_;
					*New_Node.Right_->Left_ = *this->Left_;
					*New_Node.Right_->Right_ = *this->Right_->Diff_();
				}
				if (this->Operator_ == '/'){
					New_Node = '/';
					
					New_Node.Left_ = new Node;
					New_Node.Right_ = new Node;
					
					*New_Node.Right_ = '*';
					*New_Node.Left_ = '-';
					
					New_Node.Right_->Left_ = new Node;
					New_Node.Left_->Left_ = new Node;
					New_Node.Left_->Right_ = new Node;
					New_Node.Right_->Right_ = new Node;
					
					*New_Node.Right_->Left_ = *this->Right_;
					*New_Node.Right_->Right_ = *this->Right_;
					
					*New_Node.Left_->Left_ = '*';
					*New_Node.Left_->Right_ = '*';
					
					New_Node.Left_->Left_->Left_ = new Node;
					New_Node.Left_->Left_->Right_ = new Node;
					New_Node.Left_->Right_->Left_ = new Node;
					New_Node.Left_->Right_->Right_ = new Node;
					
					*New_Node.Left_->Left_->Left_ = *this->Left_->Diff_();
					*New_Node.Left_->Left_->Right_ = *this->Right_;
					
					*New_Node.Left_->Right_->Left_ = *this->Right_->Diff_();
					*New_Node.Left_->Right_->Right_ = *this->Left_;
				}
				if ((this->Operator_ == '^') && (this->Right_->Format_ == 1)){
					New_Node = '*';
					New_Node.Left_ = new Node;
					New_Node.Right_ = new Node;
					
					*New_Node.Left_ = *this->Right_;
					*New_Node.Right_ = '^';
					
					New_Node.Right_->Left_ = new Node;
					New_Node.Right_->Right_ = new Node;
					
					*New_Node.Right_->Left_ = *this->Left_;
					*New_Node.Right_->Right_ = '-';
					
					New_Node.Right_->Right_->Left_ = new Node;
					New_Node.Right_->Right_->Right_ = new Node;
					
					*New_Node.Right_->Right_->Left_ = *this->Right_;
					*New_Node.Right_->Right_->Right_ = 1;
				}
			}
			return &New_Node;
		}
};


int main() {
	std::ofstream File;
	File.open("graph.dot");
	File << "digraph G{\n";
	char c;
	Node x, y;
	do{
		std::cin >> c;
		if (c == '(')
			x.Read_();
	} while (c != '=');
	std::cout << std::endl;
	y = *x.Diff_();
	std::cout << std::endl;
	y.Optimization();
	y.Node_Dump();
	int a = 0;
	y.Generate_Labels(&File, &a);
	a = 0;
	y.Dump_InFile(&File, &a);
	File << "}";
	File.close();
	return 0;
}
