/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange2.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:42:49 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/17 10:10:37 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::string BitcoinExchange::getDate(std::string& line, 
									 const std::string& separator) {
	std::string			date = "";
	size_t				first = 0;
	size_t				last = 0;
	int					year, month, day;
	std::stringstream	sstream;

	if (!(first = line.find(separator)))
		throw BadInputException(line);
	date = line.substr(0, first);

	if ((first = date.find_first_of("-")) == 0)
		throw BadInputException(date);
	if ((last = date.find_last_of("-")) == 0)
		throw BadInputException(date);

	if (!(sstream >> year >> first >> month >> last >> day))
	year = std::atoi(date.substr(0, first).c_str());
	if (year < 1)
		throw BadInputException(date);

	month = std::atoi(date.substr(first + 1, last).c_str());
	if (month < 1 || month > 12)
		throw BadInputException(date);

	day = std::atoi(date.substr(last + 1, date.length()).c_str());
	if (!isValidDay(year, month, day))
		throw BadInputException(date);

	return date;
}

bool BitcoinExchange::isValidDay(int year, int month, int day) {
	int		daysPerMonth[] = DAYS_PER_MONTH;
	bool	isLeapYear = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	
	if (month == 2 && isLeapYear)
		daysPerMonth[1] = 28;

	return (day < 1 || day > daysPerMonth[month - 1]) ? false : true;
}

double BitcoinExchange::getValue(std::string& line, 
								 const std::string& separator) {
	double		value = 0;
	std::string	raw = "";
	size_t		sep = 0;

	if ((sep = line.find(separator)) == 0)
		throw BadInputException(line);

	raw = line.substr(sep - 1, line.length());
	value = std::strtod(raw.c_str(), NULL);
	if (value > std::numeric_limits<double>::max())
		throw LargeNumberException();
	if (value < 0)
		throw NoPositiveNumberException();

	return value;
}

void BitcoinExchange::readDatabase(const std::string& path) {
	std::ifstream	fileStream;
	std::string		line = "";
	std::string		date = "";
	double			value = 0;

	if (path.empty())
		throw InputErrorException();
	
	fileStream.open(path.c_str());
	if (!fileStream.is_open())
		throw InputErrorException();

	while (std::getline(fileStream, line) && !trim(line, " \t\r\n").empty()) {
		date = getDate(line, DATABASE_SEPARATOR);
		value = getValue(line, DATABASE_SEPARATOR);

		_data[date] = value;
	}

	fileStream.close();
}

void BitcoinExchange::printInfo(std::ostream& out, 
								const std::string& date, 
								const double& value) {
	out << date
		<< " => "
		<< value
		<< " = "
		<< std::fixed << std::setprecision(2) 
		<< _data[date]
		<< std::endl;
}

void BitcoinExchange::exec(const std::string& infoPath) {
	std::ifstream	fileStream;
	std::string		line = "";
	std::string		date = "";
	double			value = 0;

	if (infoPath.empty())
		throw InputErrorException();

	fileStream.open(infoPath.c_str());
	if (!fileStream.is_open())
		throw InputErrorException();
	
	while (std::getline(fileStream, line) && !trim(line, " \t\r\n").empty()) {
		try {
			date = getDate(line, INFOBASE_SEPARATOR);
			value = getValue(line, INFOBASE_SEPARATOR);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		displayInfo(std::cout, date, value);
	}
}

const char* BitcoinExchange::InputErrorException::what() const throw() {
	return "could not open file.";
}

const char* BitcoinExchange::NoPositiveNumberException::what() const throw() {
	return "not a positive number.";
}

const char* BitcoinExchange::LargeNumberException::what() const throw() {
	return "too large a number.";
}

BitcoinExchange::BadInputException::BadInputException(const std::string& msg)
	:	std::runtime_error("bad input => " + msg) {
}

std::string trim(std::string& value, const std::string& scapes) {
	std::size_t	first;
	std::size_t	end;

	first = value.find_first_of(scapes);
	if (first == std::string::npos)
		return std::string("");

	end = value.find_last_of(scapes);

	return value.substr(first, end - first + 1);
}
