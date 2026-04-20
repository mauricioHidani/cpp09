/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:54:07 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/20 15:21:09 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

template<typename Container>
void PmergeMe::buildContainer(const std::string& in, Container& stl) {
	std::string	target = in, token = "";
	size_t		findPos = 0;
	int			value = 0;

	while (findPos != std::string::npos) {
		findPos = target.find(" ");
		token = target.substr(0, findPos);
		if (!std::isdigit(token[0]) && token[0] != ' ')
			throw std::runtime_error("this is not a valid entry");
		if (std::isdigit(token[0])) {
			value = std::atoi(token.c_str());
			if (value < 0)
				throw std::runtime_error("only positive integers are accepted");
			stl.push_back(value);
		}
		target = target.substr(findPos + 1);
	}
}

template<typename Container>
void PmergeMe::insertWithJacobsthal(Container& mainChain, Container& pending) {
	int			pendinSize = static_cast<int>(pending.size());
	Container	jac = buildJacobsthal<Container>(pendinSize);
	Container	inserted(pendinSize, false);
	
	mainChain.insert(mainChain.begin(), pending[0]);
	inserted[0] = true;
	
	for (size_t i = 0; i < jac.size(); i++) {
		int idx = jac[i] - 1;
		if (idx >= pendinSize || inserted[idx]) continue;

		typename Container::iterator pos = std::lower_bound(
			mainChain.begin(), 
			mainChain.end(), 
			pending[idx]
		);
		mainChain.insert(pos, pending[idx]);
		inserted[idx] = true;
	}

	for (size_t i = 1; i < pending.size(); i++) {
		if (!inserted[i]) {
			typename Container::iterator pos =
			std::lower_bound(mainChain.begin(), mainChain.end(), pending[i]);
			mainChain.insert(pos, pending[i]);
		}
    }
}

template<typename Container>
Container PmergeMe::buildJacobsthal(int number) {
	Container	sequence;
	int			a = 1, b = 3, next = 0;

	sequence.push_back(1);
	while (b < number) {
		sequence.push_back(b);
		next = b + 2 * a;
		a = b;
		b = next;
	}
	return sequence;
}

template<typename Container>
void PmergeMe::mergeInsertSort(Container& sequence) {
	Container	mainChain, pending;
	bool		hasStraggler = false;
	int			straggler = 0;

	if (sequence.size() <= 1)
		return ;

	hasStraggler = sequence.size() % 2 != 0;
	straggler = hasStraggler ? sequence.back() : 0;

	for (size_t i = 0; (i + 1) < sequence.size(); i += 2) {
		int lower = sequence[i], higher = sequence[i + 1];
		if (lower > higher) swap(lower, higher);
		mainChain.push_back(higher);
		pending.push_back(lower);
	}

	mergeInsertSort(mainChain);

	insertWithJacobsthal(mainChain, pending);

	if (hasStraggler) {
        typename Container::iterator pos = std::lower_bound(
			mainChain.begin(), 
			mainChain.end(), 
			straggler
		);
        mainChain.insert(pos, straggler);
    }

    sequence = mainChain;
}
