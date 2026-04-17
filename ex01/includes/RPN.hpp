/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:25:20 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/17 15:16:00 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <stack>

class RPN {
private:
	std::string		_input;
	std::stack<int>	_store;

	void calcSUM(const std::string& tgt, const int& a, const int& b);
	void calcSUB(const std::string& tgt, const int& a, const int& b);
	void calcMUL(const std::string& tgt, const int& a, const int& b);
	void calcDIV(const std::string& tgt, const int& a, const int& b);

protected:
	RPN(void);

public:
	RPN(const std::string& input);
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	virtual ~RPN(void);

	int calc(void);

	typedef void (RPN::*Calc)(const std::string& tgt, const int&, const int&);
};
