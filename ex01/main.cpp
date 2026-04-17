/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:25:15 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/17 16:24:56 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include "RPN.hpp"

int main(int argc, char** argv) {
	if (argc != 2 || (argc == 2 && std::string(argv[1]).empty())) {
		std::cerr << "Error: no operation was reported." << std::endl; 
		return 1;
	}
	
	try {
		RPN rpn(argv[1]);
		std::cout << rpn.calc() << std::endl;

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
