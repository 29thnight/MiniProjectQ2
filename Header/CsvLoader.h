#pragma once
#include <CoreDefine.h>

template<typename T>
inline T convertFromString(const std::string& str);

template<>
inline int convertFromString<int>(const std::string& str) 
{
    return std::stoi(str);
}

template<>
inline float convertFromString<float>(const std::string& str) 
{
    return std::stof(str);
}

template<>
inline bool convertFromString<bool>(const std::string& str) 
{
    return (str == "true" || str == "TRUE");
}

template<>
inline std::string convertFromString<std::string>(const std::string& str) 
{
    return str;
}

template<typename... Types>
class CSVReader 
{
public:
    using RowType = std::tuple<Types...>;
    CSVReader(const std::string& filename) 
    {
        std::ifstream file(filename);
        if (!file.is_open()) 
        {
            throw std::runtime_error("Could not open file");
        }

        std::string line;
        while (std::getline(file, line)) 
        {
            std::vector<std::string> row;
            std::istringstream stream(line);
            std::string cell;

            while (std::getline(stream, cell, ',')) 
            {
                row.push_back(cell);
            }

            if (!row.empty()) 
            {
                data.push_back(parseRow(row));
            }
        }

        file.close();
    }

public:
    void printData() const 
    {
        for (const auto& row : data) 
        {
            printRow(row);
            std::cout << std::endl;
        }
    }

    template<typename Func>
	void forEach(Func&& func) const
	{
		for (const auto& row : data)
		{
			std::apply(std::forward<Func>(func), row);
		}
	}

public:
    template<std::size_t... I>
    RowType parseRowImpl(const std::vector<std::string>& row, std::index_sequence<I...>) const 
    {
        return RowType{convertFromString<typename std::tuple_element<I, RowType>::type>(row[I])...};
    }

    RowType parseRow(const std::vector<std::string>& row) const 
    {
        return parseRowImpl(row, std::make_index_sequence<sizeof...(Types)>{});
    }

    template<std::size_t... I>
    void printRowImpl(const RowType& row, std::index_sequence<I...>) const 
    {
        ((std::cout << std::get<I>(row) << " "), ...);
    }

    void printRow(const RowType& row) const 
    {
        printRowImpl(row, std::make_index_sequence<sizeof...(Types)>{});
    }

private:
    std::vector<RowType> data;
};