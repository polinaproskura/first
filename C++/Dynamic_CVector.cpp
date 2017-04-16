#include <iostream>
#include <cmath>
#include <assert.h>

class CVector
{
	private:
		const static int size_ = 10;
		double * elem_;
		CVector ( const CVector& that );
	public:
		CVector() : elem_(new double[size_]) {
			int i;
			for (i = 0; i < size_; i++)
			{
				elem_[i] = i + 1;
			}
			std::cout<<"Vector had been constructed\n"<<std::endl;
		};
		~CVector(){
			delete[] elem_;
			elem_ = NULL;
			std::cout << "Destructor works\n";
		};
		double& operator[] (int index){
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
		}
		CVector& operator- (CVector& v1){
			int i;
			for (i = 0; i < size_; i++)
			{
				this->elem_[i] -= v1[i];
			}
			return *this;
		}
		CVector& operator* (int number){
			int i;
			for (i = 0; i < size_; i++)
			{
				this->elem_[i] = this->elem_[i] * number;
			}
			return *this;
		}
		CVector& operator* (CVector& v1){
			int i;
			for (i = 0; i < size_; i++)
			{
				this->elem_[i] = this->elem_[i] * v1[i];
			}
			return *this;
		}
		double operator() (int number){
			int i;
			double mod = 0;
			for (i = 0; i < size_; i++)
			{
				mod += this->elem_[i] * this->elem_[i];
			}
			mod = sqrt(mod);
			return mod;
		}
		CVector& operator= (CVector& v1){
			int i;
			for (i = 0; i < size_; i++){
				v1[i] = this->elem_[i];
			}
			return *this;
		}
};


int main() {
	int i;
	CVector v;
	int t = v[0];
	std::cout << t << "\n";
	CVector v1;
	v = v1 * t;
	v1 = v;
	for (i = 0; i < 10; i++)
	{
		std::cout << v[i] << " ";
	} 
	std::cout << "\n";
	v * v1;
	for (i = 0; i < 10; i++)
	{
		std::cout << v[i] << " ";
	} 
	std::cout << "\n"; 
	std::cout << v(t) << "\n";
	return 0;
}
