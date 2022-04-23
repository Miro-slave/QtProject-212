#include <iostream>
#include <vector>
#include "Sheet.h"
using namespace std;

/*float count_M() {
	float M_all;
	for (int i = 0; i < Qi.size(); i++) {
		M_all = M_all + Ci[i] / Mi[i];
	}
}*/

float liquid_fuel_volume(vector<float> Q, vector<float> C) {
	float fuel_volume = 0;
	for (int i = 0; i < Q.size(); i++) {
		fuel_volume = fuel_volume + Q[i] * C[i];
	}
	return fuel_volume;
}
float liquid_fuel_weight(vector<float> Q, vector<float> P) {
	float fuel_volume = 0;
	for (int i = 0; i < Q.size(); i++) {
		fuel_volume =  Q[i] / P[i];
	}
	return fuel_volume;
}

float gas_fuel_volume(vector<float> M, vector<float> n,vector<float> Q, vector<float> P, vector<float> C) {
	float fuel_volume = 0, M_all = 0;
	float Qi = 0, mi = 0, Ci = 0;
	for (int i = 0; i < Q.size(); i++) {
		M_all = M_all + C[i] / M[i];
	}

	for (int i = 0; i < Q.size(); i++) {
		mi = M[i] * n[i];
		Qi = Q[i] * mi;
		Ci = C[i] * M_all / M[i];
		fuel_volume = fuel_volume + Qi * Ci;
	}
	return fuel_volume;
}
float gas_fuel_weight(vector<float> M, vector<float> n, vector<float> Q, vector<float> P, vector<float> C) {
	float fuel_volume = 0, M_all = 0;
	float Qi = 0, mi = 0, Ci = 0;

	for (int i = 0; i < Q.size(); i++) {
		M_all = M_all + C[i] * M[i];
	}

	for (int i = 0; i < Q.size(); i++) {
		mi = M[i] * n[i];
		Qi = Q[i] / mi;
		Ci = C[i] * M[i] / M_all;
		fuel_volume = fuel_volume + Qi * Ci;
	}
	return fuel_volume;

}

float fuel_ratio(vector<float> M, vector<float> K, vector<float> C) {
	float A = 0;
	for (int i = 0; i < M.size(); i++) {
		A = K[i] * C[i];
	}
	return (2 * A * 16 + 2 * 3.76 * A * 14) / M[0];
}

int main()
{
	setlocale(LC_ALL, "rus");

	int k = 0;
	float Q_volume = 0, Q_weight = 0, ratio = 0, M_all = 0;
	Sheet ExelTable;
	vector<float> Q, C, M, m, P, K, n, L, fuel_type;

	ExelTable.setPath("test.csv");
	vector<vector<float>>* measurements = ExelTable.readAsFloat();

	for (const auto& basicString : *measurements)
	{
		k = 0;
		for (const auto& element : basicString)
		{
			k++;
			switch (k)
			{
				case 1:
					Q.push_back(element);
				case 2:
					C.push_back(element);
				case 3:
					M.push_back(element);
				case 4:
					m.push_back(element);
				case 5:
					P.push_back(element);
				case 6:
					K.push_back(element);
				case 7:
					n.push_back(element);
				case 8:
					L.push_back(element);
				case 9:
					fuel_type.push_back(element);
			}
		}
	}
	if(fuel_type[0] == 1.0f)
	cout << "Объемная теплотворность жидкого топлива = " << liquid_fuel_volume(Q, C) << endl;
	cout << "Массовая теплотворность жидкого топлива = " << liquid_fuel_weight(Q, P) << endl;

	cout << "Объемная теплотворность газообразного топлива = " << gas_fuel_volume(M, n, Q, P, C) << endl;
	cout << "Массовая теплотворность газообразного топлива = " << gas_fuel_weight(M, n, Q, P, C) << endl;

	cout << "Стереохимическое отношение = " << fuel_ratio(M, K, C) << endl;
}
