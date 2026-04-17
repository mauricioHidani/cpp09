/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:48:35 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/17 11:58:07 by mhidani          ###   ########.fr       */
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
# define INFOBASE_SEPARATOR "|"
#endif

#define DAYS_PER_MONTH {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}

class BitcoinExchange {
private:
	std::map<std::string, double>	_data;

	void validateFStream(std::ifstream& fstream);
	void readDB(std::string& path);
	bool isValidDay(const int& year, const int& month, const int& day);
	bool isValidValue(const std::string& strValue, double& value);
	bool isValidDate(const std::string& date);
	void dslInfo(std::ostream& out, const std::string& dt, const double& val);

public:
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange(const std::string& databasePath);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	virtual ~BitcoinExchange(void);

	void exec(const std::string& infoPath);
};

std::string trim(const std::string& value, const std::string& scapes);
