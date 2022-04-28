#include <vector>
#include <iostream>
#include <clocale>
#include "Sheet.h"
#include "Exceptions.h"
using namespace std;
//ЧТОБЫ УБРАТЬ ДЕБАГ МОД, ЗАКОММЕНТИРУЙТЕ #define DEBUG В ФАЙЛЕ Exceptions.h


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
#ifdef DEBUG
		if (C.size() <= i)
			throw OutOfBoundsException("fuel_volume");
#endif
		fuel_volume_all = fuel_volume_all + Q[i] * C[i];
	}
#ifdef DEBUG
	cerr << "модуль " << "fuel_volume" << " выполнен успешно\n";
#endif
	return fuel_volume_all;
}

//Функции считают значение в зависимости от того, какой вид топлива используется
float liquid_fuel_weight(vector<float> Q, vector<float> C, vector<float> P, vector<float> fuel_type) {
	float fuel_weight_all = 0, Qi = 0;
	for (int i = 0; i < Q.size(); i++) {
#ifdef DEBUG
		if (P[i] == 0)
			throw DivideByZeroException("liquid_fuel_weight");
		else if (C.size() <= i || P.size() <= i || fuel_type.size() <= i)
			throw OutOfBoundsException("liquid_fuel_weight");
#endif
		if (fuel_type[i] == 1.0f) {
			Qi = Q[i] / P[i];//Перевод из дж/м^3 в Дж/кг
			fuel_weight_all = fuel_weight_all + Qi * C[i];
		}
	}
#ifdef DEBUG
	cerr << "модуль " << "liquid_fuel_weight" << " выполнен успешно\n";
#endif
	return fuel_weight_all;
}
float gas_fuel_weight(vector<float> Q, vector<float> C, vector<float> M, vector<float> n, vector<float> P, vector<float> fuel_type) {
	float fuel_weight_all = 0, M_all = 0;
	float mi, Qi, Ci;

	for (int i = 0; i < Q.size(); i++) {
#ifdef DEBUG
		if (C.size() <= i || M.size() <= i || fuel_type.size() <= 0)
			throw OutOfBoundsException("gas_fuel_weight");
#endif
		if (fuel_type[i] == 0.0f) {
			M_all = M_all + M[i] * C[i];
		}
	}
	for (int i = 0; i < Q.size(); i++) {
#ifdef DEBUG
		if (C.size() <= i || M.size() <= i || n.size() <= i || fuel_type.size() <= 0)
			throw OutOfBoundsException("gas_fuel_weight");
#endif
		if (fuel_type[i] == 0.0f) {
			mi = M[i] * n[i];
#ifdef DEBUG
			if (mi == 0 || M_all == 0)
				throw DivideByZeroException("gas_fuel_weight");
#endif
			Qi = Q[i] / mi;
			Ci = C[i] * (M[i] / M_all);
			fuel_weight_all = fuel_weight_all + Qi * Ci;
		}
	}
#ifdef DEBUG
	cerr << "модуль " << "gas_fuel_weight" << " выполнен успешно\n";
#endif
	return fuel_weight_all;
}

//Значение не зависит от вида топлива, значит функция 1 для всех видов
float fuel_ratio(vector<float> M, vector<float> K, vector<float> C) {
	float A = 0;
	for (int i = 0; i < M.size(); i++) {
#ifdef DEBUG
		if (C.size() <= i || K.size() <= i)
			throw OutOfBoundsException("fuel_ratio");
#endif
		A = K[i] * C[i];
	}
#ifdef DEBUG
	if (M[0] == 0)
		throw DivideByZeroException("fuel_ratio");
#endif
#ifdef DEBUG
	cerr << "модуль " << "fuel_ratio" << " выполнен успешно\n";
#endif
	return (2 * A * 16 + 2 * 3.76 * A * 14) / M[0];
}

int main()
{
	try
	{
		setlocale(LC_ALL, "rus");

		int k = 0;
		float Q_volume = 0, Q_weight = 0, ratio = 0, M_all = 0;
		Sheet ExelTable;
		vector<float> Q, C, M, m, P, K, n, L, fuel_type, element;
		ExelTable.setPath("test.csv");

		vector<vector<float>> measurements = ExelTable.readAsFloat();

		for (int i = 0; i < measurements.size(); i++)
		{
#ifdef DEBUG
			if (measurements[i].size() < 9 || measurements.size() <= i)
				throw OutOfBoundsException("распределение данных из таблицы");
#endif
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
#ifdef DEBUG
		cerr << "модуль " << "распределение данных из таблицы" << " выполнен успешно\n";
#endif
		//if(fuel_type[0] == 1.0f)
		cout << "Объемная теплотворность топлива = " << fuel_volume(Q, C) << endl;
		cout << "Массовая теплотворность жидкого топлива = " << liquid_fuel_weight(Q, C, P, fuel_type) << endl;
		cout << "Массовая теплотворность газообразного топлива = " << gas_fuel_weight(Q, C, M, n, P, fuel_type) << endl;
		cout << "Стереохимическое отношение = " << fuel_ratio(M, K, C) << endl;
	}
	catch (exception& ex)
	{
		cerr << ex.what();
	}

	return 0;
}
