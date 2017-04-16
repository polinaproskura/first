#include <iostream>
#include <cmath>
#include <assert.h>

template <typename T>

class CVector
{
	private:
		const static int size_ = 10;
		T * elem_;
		CVector ( const CVector& that );
	public:
		CVector() : elem_(new T[size_]) {
			int i;
			for (i = 0; i < size_; i++)
			{
				elem_[i] = i + 1;
			}
		};
		T& operator[] (int index){
			assert((index >= 0) && (index <= size_));
			return elem_[index];
		};
		CVector& operator+ (CVector& v1){
			int i;
			for (i = 0; i < size_; i++)
			{
				this->elem_[i] += v1[i];
			}
			return *this;
		};
		CVector& operator- (CVector& v1){
			int i;
			for (i = 0; i < size_; i++)
			{
				this->elem_[i] -= v1[i];
			}
			return *this;
		};
		CVector& operator* (int number){
			int i;
			for (i = 0; i < size_; i++)
			{
				this->elem_[i] = this->elem_[i] * number;
			}
			return *this;
		};
		CVector& operator* (CVector& v1){
			int i;
			for (i = 0; i < size_; i++)
			{
				this->elem_[i] = this->elem_[i] * v1[i];
			}
			return *this;
		};
		T operator() (int number){
			int i;
			double mod = 0;
			for (i = 0; i < size_; i++)
			{
				mod += this->elem_[i] * this->elem_[i];
			}
			mod = sqrt(mod);
			return mod;
		};
		CVector& operator= (CVector& v1){
			int i;
			for (i = 0; i < size_; i++){
				v1[i] = this->elem_[i];
			}
			return *this;
		};
		~CVector(){
			delete[] elem_;
			elem_ = NULL;
		};
};

template <> class CVector <bool> {
	private:
		const static int size_ = 10;
		bool * elem_;
		CVector ( const CVector& that );
	public:
	CVector () : elem_(new bool[size_]){
		int i;
		for (i = 0; i < size_; i++)
		{
			elem_[i] = i % 2;
		}
	};
	~CVector() {
		delete[] elem_;
		elem_ = NULL;
	};
	bool& operator[] (int index){
		assert((index >= 0) && (index <= size_));
		return elem_[index];
	};
	class CBitIterator {
		protected:
			CVector & first_;
		public:
			int index_;
			CBitIterator(CVector & first, int index) : first_(first), index_(index){};
			CBitIterator(CVector & first) : first_(first){
				index_ = 0;
			};
			~CBitIterator(){};
			CBitIterator& operator = (CBitIterator i) {
				i.index_ = index_;
				i.first_ = first_ ;
				return i;
			};
			bool operator < (CBitIterator i){
				if (index_ < i.index_)
					return true;
				return false;
			};
			bool operator > (CBitIterator i){
				if (index_ > i.index_)
					return true;
				return false;
			};
			bool operator == (CBitIterator i){
				if (index_ == i.index_)
					return true;
				return false;
			};
			bool operator != (CBitIterator i){
				if (index_ != i.index_)
					return true;
				return false;
			};
			CBitIterator begin() {
				CBitIterator Help(first_);
				return Help;
			};
			CBitIterator end(){
				CBitIterator Help(first_, first_.size_);
				return Help;
			};
			void next(){
				this->index_ ++;
			};
			bool & current(){
				return this->first_[this->index_];
			};
	};
};

int main() {
	int j;
	CVector <bool> b;
	for (j = 0; j < 10; j++)
	{
		std::cout << b[j] << " ";
	} 
	std::cout << "\n";
	
	CVector <bool> :: CBitIterator i(b);
	for (i = i.begin(); i != i.end(); i.next())
	{
		std::cout << i.current() << " ";
	} 
	std::cout << "\n";
	
	return 0;
}
