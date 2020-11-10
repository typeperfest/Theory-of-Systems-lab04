
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

double GetRandomNumberFloat(double min, double max, int precision) {
	double value;
	value = rand() % (int)pow(10, precision);
	value = min + (value / pow(10, precision)) * (max - min);
	return value;
}

struct point {
	double x, y;
	//Вычисление значения функции в точке
	double Fit() { return sin(x) * sin(y) / (1 + x * x + y * y); }
	//Функция мутации
	void mut() {
		if (rand() % 100 < 40)
			x += GetRandomNumberFloat(-1, 1, 5);
		if (rand() % 100 < 40)
			y += GetRandomNumberFloat(-1, 1, 5);
		// if (1) x += GetRandomNumberFloat(0, 1, 5) + 0.5;
		// if (1) y += GetRandomNumberFloat(0, 1, 5) + 0.5;
		if (x > 2)
			x = 2;
		if (x < 0)
			x = 0;
		if (y > 2)
			y = 2;
		if (y < -2)
			y = -2;
	}
	void sub(point & Ind_l, point & Ind_r) {
		x = Ind_l.x;
		y = Ind_r.y;
	}
};

bool pred(point Ind_l, point Ind_r) { return Ind_l.Fit() > Ind_r.Fit(); }

//Функция кроссовера
void cross(point & Ind_l, point & Ind_r, std::vector<point> & Population) {
	point sub_ind_1, sub_ind_2;
	sub_ind_1.sub(Ind_l, Ind_r);
	sub_ind_2.sub(Ind_r, Ind_l);
	sub_ind_1.mut();
	sub_ind_2.mut();
	Population.push_back(sub_ind_1);
	Population.push_back(sub_ind_2);
}

//Функция естественного отбора
void RIP(std::vector<point> & Population) {
	std::sort(Population.begin(), Population.end(), pred);
	Population.erase(Population.begin() + 4, Population.end());
}
void Print(std::vector<point> & Population) {

	// print Population
	double Fit_Sum = 0;
	for (int j = 0; j < 4; j++) {
		std::cout << "X = " << Population[j].x << "   Y = " << Population[j].y
			<< "   Fit = " << Population[j].Fit() << std::endl;
		Fit_Sum += Population[j].Fit();
	}
	double Fit_Mid = Fit_Sum / 4;
	std::cout << "Middle Fit = " << Fit_Mid
		<< "   Max Fit = " << Population[0].Fit() << std::endl
		<< std::endl;
}
int main() {
	srand(time(NULL));
	//Создаем изначальную попюляцию
	std::vector<point> Population;
	for (int i = 0; i < 4; i++) {
		point buf;
		buf.x = GetRandomNumberFloat(0, 2, 5);
		buf.y = GetRandomNumberFloat(0, 4, 5) - 2;
		Population.push_back(buf);
	}
	std::sort(Population.begin(), Population.end(), pred);
	for (int i = 0; i < 10; i++) {
		Print(Population);
		// Step of GA
		cross(Population[0], Population[1], Population);
		cross(Population[0], Population[2], Population);
		RIP(Population);
	}
	Print(Population);
}