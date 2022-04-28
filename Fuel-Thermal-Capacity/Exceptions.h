#pragma once


#include <exception>
#include <iostream>
#include <string>
#include <clocale>
#define DEBUG


class DivideByZeroException : public std::exception
{
	std::string _error;
public:
	DivideByZeroException(std::string ModuleName) {
		_error = "Деление на ноль в модуле: " + ModuleName;
	};
	inline const char* what() const {
		return  _error.c_str();
	};
};


class OutOfBoundsException : public std::exception
{
	std::string _error;
public:
	OutOfBoundsException(std::string ModuleName) {
		_error = "Выход за границы массива в модуле: " + ModuleName;
	};
	inline const char* what() const {
		return  _error.c_str();
	};
};

class FileOpenException : public std::exception
{
	std::string _error;
public:
	FileOpenException(std::string ModuleName) {
		_error = "Ошибка открытия файла в модуле: " + ModuleName;
	};
	inline const char* what() const {
		return  _error.c_str();
	};
};

class InputStreamException : public std::exception
{
	std::string _error;
public:
	InputStreamException(std::string ModuleName) {
		_error = "Ошибка потока ввода в модуле: " + ModuleName;
	};
	inline const char* what() const {
		return  _error.c_str();
	};
};

class OutputStreamException : public std::exception
{
	std::string _error;
public:
	OutputStreamException(std::string ModuleName) {
		_error = "Ошибка потока вывода в модуле: " + ModuleName;
	};
	inline const char* what() const {
		return  _error.c_str();
	};
};