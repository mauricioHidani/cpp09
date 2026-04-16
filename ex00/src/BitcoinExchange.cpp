/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:40:26 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/16 17:55:24 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string& databasePath) {
	readDatabase(databasePath);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
	:	_data(other._data) {
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		_data = other._data;

	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {
	_data.clear();
}



std::string BitcoinExchange::getDate(std::string& line, 
									 const std::string& separator) {
	std::string			date = "";
	std::stringstream	sstream;
	int					year, month, day;
	char				firstDash, lastDash;

	if (!(sstream >> year >> firstDash >> month >> lastDash >> day))
		return ;
	if (firstDash == '-' && lastDash == '-')
		return ;
	if (year < 1 && (month < 1 || month > 12) && !isValidDay(year, month, day))
		throw BadInputException(date);

	return date;
}

void BitcoinExchange::readDatabase(const std::string& path) {
	std::ifstream	fstream;
	std::string		line;

	fstream.open(path.c_str());
	if (!fstream.is_open())
		throw std::runtime_error("could not open file.");
	
	while (std::getline(fstream, line) && !trim(line, " \t\r\n").empty()) {
		std::string date = getDate(line, DATABASE_SEPARATOR);

		std::cout << date << std::endl;
	}

	fstream.close();
}
