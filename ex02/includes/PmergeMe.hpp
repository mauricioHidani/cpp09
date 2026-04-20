/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:33:34 by mhidani           #+#    #+#             */
/*   Updated: 2026/04/20 11:57:38 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class PmergeMe {
private:
	template<typename Container>
	static void insertWithJacobsthal(Container& mainChain, Container& pending);

public:
	PmergeMe(void);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	virtual ~PmergeMe(void);

	template<typename Container>
	static void buildContainer(const std::string& in, Container& stl);
	
	template<typename Container>
	static Container buildJacobsthal(int number);
	
	template<typename Container>
	static void mergeInsertSort(Container& sequence);
};

#include "PmergeMe.tpp"
