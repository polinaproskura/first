#include <iostream>

template <typename T>

class CDot{
	
	public :
		T x;
		T y;
		CDot(){
			std::cout << "Constructor works\n";
		}
		~CDot(){
			std::cout << "Destructor works\n";
		};
};

int main(){
	double a, b;
	int i, n;
	scanf("%d", &n);
	CDot <double> d[n], f;
	for (i = 0; i < n; i++){
		std::cin >> a >> b;
		d[i].x = a;
		d[i].y = b;
	}
	double t;
	std::cin >> t;
	if ((t >= 0) && (t < (n - 1))){
			f.x = d[(int)t].x + (t - (int)t) * (d[(int)t + 1].x - d[(int)t].x);
			f.y = d[(int)t].y + (t - (int)t) * (d[(int)t + 1].y - d[(int)t].y);
	} else
		std::cout << "Wrong parameter\n";
	if ((t >= 0) && (t <=(n - 1)))
		std::cout << f.x << " " << f.y << "\n";
	return 0;
}
