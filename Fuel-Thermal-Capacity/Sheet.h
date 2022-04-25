#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Sheet
{
public:
    Sheet();
    Sheet(std::string path);

	// creates associated Sheet if empty
    void setPath(const std::string& path);

    void write(const std::vector<std::vector<std::string>>& data) const;
	std::vector<std::vector<std::string>> read() const;
    std::vector<std::vector<float>> readAsFloat() const;

private:
    // associated sheet
    std::string _path; 
};