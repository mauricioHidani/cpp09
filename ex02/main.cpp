/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:34:15 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/21 11:40:00 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <vector>
#include <deque>
#include "PmergeMe.hpp"

double getTimeElapsed(const timeval& start, const timeval& end) {
	long	sec = end.tv_sec - start.tv_sec;
	long	usec = end.tv_usec - start.tv_usec;

	return (sec * 1000000.0) + usec;
}

template<typename C1, typename C2>
bool checkSort(const C1& c1, const C2& c2) {
	if (c1.size() != c2.size())
		return false;

	typename C1::const_iterator	it1 = c1.begin();
	typename C2::const_iterator	it2 = c2.begin();

	while (it1 != c1.end()) {
		if (*it1 != *it2)
			return false;
		it1++;
		it2++;
	}

	return true;
}

template<typename Container>
void displayContainer(std::ostream& out, const std::string& tgt, 
					  const Container& stl) {
	out << tgt << ": ";
	for (size_t i = 0; i < stl.size(); i++) {
		out << stl[i];
		if (i < stl.size() - 1)
			out << " ";
		if (i == 4 && stl.size() > 5) {
			out << "[...]";
			break;
		}
	}
	out << std::endl;
}

template<typename Container>
void displayResult(std::ostream& out, const Container& stl, 
				   const double& timeElapsed) {
	out << "Time to process a range of" << "\t"
		<< stl.size() << " elements with std::[..]:\t"
		<< std::fixed << std::setprecision(5) << timeElapsed << "µs"
		<< std::endl;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error: the input format must be enclosed in double quotes, "
				  << "with positive numbers separated by spaces. "
				  << std::endl;
		return 1;
	}

	std::vector<int>	vector;
	std::deque<int>		deque;
	double				vectorTime, dequeTime;

	{ // Container Vector
		struct timeval		start, end;

		gettimeofday(&start, NULL); // start time of process sort
		
		try {
			PmergeMe::buildContainer(argv[1], vector);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return 1;
		}
		
		PmergeMe::mergeInsertSort(vector);
		
		gettimeofday(&end, NULL); // end time of process sort
		vectorTime = getTimeElapsed(start, end);
	}

	{ // Container Deque
		struct timeval	start, end;

		gettimeofday(&start, NULL); // start time of process sort
		
		try {
			PmergeMe::buildContainer(argv[1], deque);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return 1;
		}

		PmergeMe::mergeInsertSort(deque);
		
		gettimeofday(&end, NULL); // end time of process sort
		dequeTime = getTimeElapsed(start, end);
	}

	if (!checkSort(vector, deque)) {
		std::cerr << "Error: the containers doesn't contain the same result; ";
		std::cerr << "the sort operation was incorrect. " << std::endl;
		return 1;
	}

	std::vector<int>	before;
	PmergeMe::buildContainer(argv[1], before);
	displayContainer(std::cout, "Before", before);
	displayContainer(std::cout, "After", deque);

	displayResult(std::cout, vector, vectorTime);
	displayResult(std::cout, deque, dequeTime);

	return 0;
}
