/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:40:26 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/17 13:16:45 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	_data = other._data;
}

BitcoinExchange::BitcoinExchange(const std::string& databasePath) {
	readDB(const_cast<std::string&>(databasePath));
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		_data = other._data;

	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {
	_data.clear();
}

bool BitcoinExchange::isValidValue(const std::string& strValue, double& value) {
	char*	endptr = NULL;

	if (strValue.empty()) {
		std::cerr << "Error: bad input => empty" << std::endl;
		return false;
	}

	value = std::strtod(strValue.c_str(), &endptr);
	if (*endptr != '\0' && !std::isspace(*endptr)) {
		std::cerr << "Error: bad input => " << strValue << std::endl;
		return false;
	}

	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) {
	int					daysPerMonth[] = DAYS_PER_MONTH;
	int					year, month, day;
	char				dash1, dash2;
	bool				isOut, isOutBitcoinCreation, isLeapYear;
	std::stringstream	sstream(date);

	year = month = day = dash1 = dash2 = 0;
	isOut = isOutBitcoinCreation = isLeapYear = false;

	if (!(sstream >> year >> dash1 >> month >> dash2 >> day) || 
		  dash1 != '-' || dash2 != '-' ||
		  !(sstream >> std::ws).eof()) {
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}
	
	isOut = year < 2008 || (month < 1 || month > 12);
	isOutBitcoinCreation = year == 2008 && month < 10;

	if (isOut || isOutBitcoinCreation) {
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}

	isLeapYear = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	if (month == 2 && !isLeapYear)
		daysPerMonth[1] = 28;
	if (day < 1 || day > daysPerMonth[month - 1]) {
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}
	
	return true;
}

void BitcoinExchange::dslInfo(std::ostream& out, const std::string& date, 
							  const double& value) {
	std::map<std::string, double>::const_iterator it = _data.lower_bound(date);
	if (it == _data.end() || it->first != date) {
		if (it == _data.begin()) {
			std::cerr << "Error: no available rate for date => " << date 
					  << std::endl;
			return ;
		}
		--it;
	}

	out << date << " => " << value << " = " << it->second * value << std::endl;
}

void BitcoinExchange::validateFStream(std::ifstream& fstream) {
	if (!fstream.is_open())
		throw std::invalid_argument("could not open file.");
	if (fstream.peek() == std::ifstream::traits_type::eof())
		throw std::runtime_error("file is empty.");
}

void BitcoinExchange::readDB(std::string& path) {
	std::ifstream	fstream;
	std::string		line = "", date = "", strRate = "";
	size_t			sepPos = 0;
	double			rate = 0;

	if (path.empty())
		throw std::invalid_argument("could not open file.");

	fstream.open(path.c_str());
	validateFStream(fstream);

	std::getline(fstream, line); // trims the header
	while (std::getline(fstream, line)) {
		sepPos = line.find(DATABASE_SEPARATOR);
		if (sepPos == std::string::npos) {
			std::cerr << "Error: bad input => " << trim(line, " \t\r\n") 
					  << std::endl;
			continue ;
		}

		date = trim(line.substr(0, sepPos), " \t\r\n");
		strRate = trim(line.substr(sepPos + 1), " \t\r\n");
		rate = 0;

		if (isValidDate(date) && isValidValue(strRate, rate))
			_data[date] = rate;
	}

	fstream.close();
}

void BitcoinExchange::exec(const std::string& infoPath) {
	std::ifstream	fstream;
	std::string		line = "", date = "", strValue = "";
	size_t			sepPos = 0;
	double			value = 0;
	bool			validDate = false, validValue = false;

	if (infoPath.empty())
		throw std::invalid_argument("could not open file.");

	fstream.open(infoPath.c_str());
	validateFStream(fstream);

	std::getline(fstream, line); // trims the header
	while (std::getline(fstream, line)) {
		sepPos = line.find(INFOBASE_SEPARATOR);
		if (sepPos == std::string::npos) {
			std::cerr << "Error: bad input => " << trim(line, " \t\r\n") 
					  << std::endl;
			continue ;
		}

		date = trim(line.substr(0, sepPos), " \t\r\n");
		strValue = trim(line.substr(sepPos + 1), " \t\r\n");
		value = 0;

		validDate = isValidDate(date);
		validValue = isValidValue(strValue, value);

		if (validDate && validValue) {
			if (value < 0) {
				std::cerr << "Error: not a positive number." << std::endl;
				continue ;
			} else if (value > 1000) {
				std::cerr << "Error: too large a number." << std::endl;
				continue ;
			}
			dslInfo(std::cout, date, value);
		}
	}

	fstream.close();
}

std::string trim(const std::string& src, const std::string& target) {
	size_t	start = 0;
	size_t	end = 0;

	if ((start = src.find_first_not_of(target.c_str())) == std::string::npos)
		return std::string("");

	end = src.find_last_not_of(target.c_str());
	return src.substr(start, end - start + 1);
}
