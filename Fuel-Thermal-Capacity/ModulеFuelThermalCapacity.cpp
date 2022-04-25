﻿#include <iostream>
#include <vector>
#include "Sheet.h"
using namespace std;


/*Исходные данные в таблицах:
Qнi(дж/м^3)
Ci(по объему)
газообразное топливо - 0
жидкое топливо - 1
*/
//Т.к. перевод из СС не требудется, то функция считает как для газообразного, так и для жидкого
float fuel_volume(vector<float> Q, vector<float> C) {
	float fuel_volume_all = 0;

	for (int i = 0; i < Q.size(); i++) {
		fuel_volume_all = fuel_volume_all + Q[i] * C[i];
	}
	return fuel_volume_all;
}

//Функции считают значение в зависимости от того, какой вид топлива используется
float liquid_fuel_weight(vector<float> Q, vector<float> C, vector<float> P, vector<float> fuel_type) {
	float fuel_weight_all = 0, Qi = 0;

	for (int i = 0; i < Q.size(); i++) {
		if (fuel_type[i] == 1.0f) {
			Qi = Q[i] / P[i];//Перевод из дж/м^3 в Дж/кг
			fuel_weight_all = fuel_weight_all + Qi * C[i];
		}
	}
	return fuel_weight_all;
}
float gas_fuel_weight(vector<float> Q, vector<float> C, vector<float> M, vector<float> n, vector<float> P, vector<float> fuel_type) {
	float fuel_weight_all = 0, M_all = 0;
	float mi, Qi, Ci;

	for (int i = 0; i < Q.size(); i++) {
		if (fuel_type[i] == 0.0f) {
			M_all = M_all + M[i] * C[i];
		}
	}
	for (int i = 0; i < Q.size(); i++) {
		if (fuel_type[i] == 0.0f) {
			mi = M[i] * n[i];
			Qi = Q[i] / mi;
			Ci = C[i] * (M[i] / M_all);
			fuel_weight_all = fuel_weight_all + Qi * Ci;
		}
	}
	return fuel_weight_all;
}

//Значение не зависит от вида топлива, значит функция 1 для всех видов
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
	vector<float> Q, C, M, m, P, K, n, L, fuel_type, element;

	ExelTable.setPath("D:/Prog/ModulеFuelThermalCapacity/QtProject-212-fork/Fuel-Thermal-Capacity/test.csv");
	vector<vector<float>> measurements = ExelTable.readAsFloat();

	for (int i = 0; i < measurements.size(); i++)
	{
		Q.push_back(measurements[i][0]);
		C.push_back(measurements[i][1]);
		M.push_back(measurements[i][2]);
		m.push_back(measurements[i][3]);
		P.push_back(measurements[i][4]);
		K.push_back(measurements[i][5]);
		n.push_back(measurements[i][6]);
		L.push_back(measurements[i][7]);
		fuel_type.push_back(measurements[i][8]);
	}

	//if(fuel_type[0] == 1.0f)
	cout << "Объемная теплотворность топлива = " << fuel_volume(Q, C) << endl;
	cout << "Массовая теплотворность жидкого топлива = " << liquid_fuel_weight(Q, C, P, fuel_type) << endl;
	cout << "Массовая теплотворность газообразного топлива = " << gas_fuel_weight(Q, C, M, n, P, fuel_type) << endl;
	cout << "Стереохимическое отношение = " << fuel_ratio(M, K, C) << endl;

	return 0;
}
