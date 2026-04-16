/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:48:35 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/16 17:36:45 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <map>

#ifndef DATABASE_PATH
# define DATABASE_PATH "data.csv"
#endif

#ifndef DATABASE_SEPARATOR
# define DATABASE_SEPARATOR ","
#endif

#ifndef INFOBASE_SEPARATOR
# define INFOBASE_SEPARATOR " | "
#endif

#define DAYS_PER_MONTH {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}

class BitcoinExchange {
private:
	std::map<std::string, double>	_data;

	void readDatabase(const std::string& path);
	bool isValidDay(int year, int month, int day);
	std::string getDate(std::string& line, const std::string& separator);
	double getValue(std::string& line, const std::string& separator);
	void printInfo(std::ostream& out, const std::string& date, const double& value);

public:
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange(const std::string& databasePath);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	virtual ~BitcoinExchange(void);

	void exec(const std::string& infoPath);

	class InputErrorException: public std::exception {
	public:
		virtual const char* what() const throw();
	};
	class NoPositiveNumberException: public std::exception {
	public:
		virtual const char* what() const throw();
	};
	class LargeNumberException: public std::exception {
	public:
		virtual const char* what() const throw();
	};
	class BadInputException: public std::runtime_error {
	public:
		BadInputException(const std::string& msg);
	};
};

std::string trim(std::string& value, const std::string& scapes);
