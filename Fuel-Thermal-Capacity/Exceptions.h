#pragma once


#include <exception>
#include <iostream>
#include <string>
#define DEBUG


class DivideByZeroException : public std::exception
{
	std::string _error;
public:
	DivideByZeroException(std::string ModuleName) {
		_error = "Divide by zero in module: " + ModuleName;
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
		_error = "Out of bounds in module: " + ModuleName;
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
		_error = "File open error in module: " + ModuleName;
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
		_error = "Input stream error in module: " + ModuleName;
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
		_error = "Output stream error in module: " + ModuleName;
	};
	inline const char* what() const {
		return  _error.c_str();
	};
};