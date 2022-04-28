#include "Sheet.h"
#include "Exceptions.h"

Sheet::Sheet() : _path("") {}

Sheet::Sheet(std::string path) : _path(std::move(path)) {}

void Sheet::setPath(const std::string& path)
{
    _path = path;
}

void Sheet::write(const std::vector<std::vector<std::string>>& data) const
{
    std::fstream file;
    file.open(_path, std::ios::out);
#ifdef DEBUG
    if (file.is_open())
        std::cerr << "excel file opened successfully\n";
    else
        throw FileOpenException("database input");
#endif
    for (auto element : data)
    {
        std::string s;
	    for (auto basicString : element)
	    {
		    s.append(basicString + ",");
	    }
        file << s << "\n";
#ifdef DEBUG
        if (file.fail())
            throw OutputStreamException("database input");
#endif
    }
#ifdef DEBUG
    std::cerr << "database input completed successfully\n";
#endif
    file.close();
}

std::vector<std::vector<std::string>> Sheet::read() const
{
    auto data = new std::vector<std::vector<std::string>>;

    // File pointer
    std::fstream file;
    file.open(_path, std::ios::in);
#ifdef DEBUG
    if (file.is_open())
        std::cerr << "excel file opened successfully\n";
    else
        throw FileOpenException("output from the database");
#endif
    std::vector<std::string> row;
    std::string word, line;
  
    while (file >> line) 
    {
        row.clear();
#ifdef DEBUG
        if (file.fail())
            throw InputStreamException("output from the database(caused of file)");
#endif
        // used for breaking words
        std::stringstream s(line);
  
        // read every column data of a row and
        // store it in a string variable, 'word'
    	while (getline(s, word, ','))
        {
#ifdef DEBUG
            if (s.fail())
                throw InputStreamException("output from the database(caused of string)");
#endif
            row.push_back(word);
        }
        // add current row to data vector
    	data->push_back(row);
    }
#ifdef DEBUG
    std::cerr << "output from the database completed successfully\n";
#endif

    file.close();

    return *data;
}


/**
 * read csv file as table of floats
 *
 * all "" (empty strings) converts to 0, be careful
 * all not empty strings will crash with exception BE CAREFUL TWICE !!!
 */
std::vector<std::vector<float>> Sheet::readAsFloat() const
{
    auto data = new std::vector<std::vector<float>>;

    // File pointer
    std::fstream file;
    file.open(_path, std::ios::in);
#ifdef DEBUG
    if (file.is_open())
        std::cerr << "excel file opened successfully\n";
    else
        throw FileOpenException("float_output from the database");
#endif
    std::vector<float> row;
    std::string word, line;

    while (file >> line) 
    {
        row.clear();
#ifdef DEBUG
        if (file.fail())
            throw InputStreamException("float_output from the database(caused of file)");
#endif
        // used for breaking words
        std::stringstream s(line);
  
        // read every column data of a row and
        // store it in a string variable, 'word'
    	while (getline(s, word, ','))
        {
#ifdef DEBUG
            if (s.fail())
                throw InputStreamException("float_output from the database(caused of string)");
#endif
            if(word.empty())
            {
	            row.push_back(0);
            }
            else
            {
                row.push_back(std::stof(word));
            }
        }
        // add current row to data vector
    	data->push_back(row);
    }
#ifdef DEBUG
    std::cerr << "float_output from the database completed successfully\n";
#endif

    file.close();

    return *data;
}

