/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:25:26 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/19 08:57:22 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void): _input(std::string("")), _store(std::stack<int>()) {
}

RPN::RPN(const std::string& input): _input(input) {
}

RPN::RPN(const RPN& other): _store(other._store) {
}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		while (!_store.empty())
			_store.pop();
		_store = other._store;
	}

	return *this;
}

RPN::~RPN(void) {
	_input = "";

	while (!_store.empty())
		_store.pop();
}

int RPN::calc(void) {
	double				a = 0, b = 0;
	std::string			tkn = std::string("");
	std::stringstream	ss(_input);
	Calc				calc[] = {
		&RPN::calcSUM, &RPN::calcSUB, &RPN::calcDIV, &RPN::calcMUL
	};

	while (ss >> tkn) {
		if (tkn.length() == 1 && std::string("+-/*").find(tkn) != std::string::npos) {
			if (_store.size() < 2)
				throw std::runtime_error("operator without sufficient operands.");

			b = _store.top(); _store.pop();
			a = _store.top(); _store.pop();

			for (size_t i = 0; i < 4; i++)
					(this->*calc[i])(tkn, a, b);
		} else if (tkn.length() == 1 && std::isdigit(tkn[0])) {
			_store.push(tkn[0] - '0');
		} else {
			throw std::runtime_error("invalid input.");
		}
	}

	if (_store.size() != 1)
		throw std::runtime_error("malformed expression.");
	
	return _store.top();
}

void RPN::calcSUM(const std::string& tgt, const int& a, const int& b) {
	if (tgt != "+")
		return ;
	_store.push(a + b);
}

void RPN::calcSUB(const std::string& tgt, const int& a, const int& b) {
	if (tgt != "-")
		return ;
	_store.push(a - b);
}

void RPN::calcMUL(const std::string& tgt, const int& a, const int& b) {
	if (tgt != "*")
		return ;
	_store.push(a * b);
}

void RPN::calcDIV(const std::string& tgt, const int& a, const int& b) {
	if (tgt != "/")
		return ;
	if (b == 0)
		throw std::runtime_error("division by zero is invalid.");
	_store.push(a / b);
}
