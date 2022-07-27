/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lab.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <papawolf@kakao.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 05:54:19 by gunkim            #+#    #+#             */
/*   Updated: 2022/07/25 17:26:46 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator>
#include <vector.hpp>
#include <vector>

int main()
{
	/* 012 */
	/*
	ft::vector<int> vector_int;
	std::cout << "size:" << vector_int.size() << std::endl;
	vector_int.reserve(100);

	ft::vector<int>::iterator itei = vector_int.begin();
	vector_int.push_back(42);
	std::cout << "iterator base : " << itei.base() << std::endl;
	std::cout << "vector size/cap: " << vector_int.size() << " / " << vector_int.capacity() << std::endl;
	std::cout << "[0] : " <<  vector_int[0] << std::endl;
	std::cout << "front : " <<  vector_int.front() << std::endl;
	std::cout << "back  : " <<  vector_int.back() << std::endl;
	
	vector_int.push_back(43);
	std::cout << "iterator base : " << itei.base() << std::endl;
	std::cout << "vector size/cap: " << vector_int.size() << " / " << vector_int.capacity() << std::endl;
	std::cout << "[0] : " <<  vector_int[0] << std::endl;
	std::cout << "front : " <<  vector_int.front() << std::endl;
	std::cout << "back  : " <<  vector_int.back() << std::endl;
	
	vector_int.pop_back();
	std::cout << "iterator base : " << itei.base() << std::endl;
	std::cout << "vector size/cap: " << vector_int.size() << " / " << vector_int.capacity() << std::endl;
	std::cout << "[0] : " <<  vector_int[0] << std::endl;
	std::cout << "front : " <<  vector_int.front() << std::endl;
	std::cout << "back  : " <<  vector_int.back() << std::endl;
	
	vector_int.pop_back();
	std::cout << "iterator base : " << itei.base() << std::endl;
	std::cout << "vector size/cap: " << vector_int.size() << " / " << vector_int.capacity() << std::endl;
	std::cout << "[0] : " <<  vector_int[0] << std::endl;
	std::cout << "front : " <<  vector_int.front() << std::endl;
	std::cout << "back  : " <<  vector_int.back() << std::endl;
	*/


	// 013 range_constructor
	ft::vector<int> series;

	for (size_t i = 40; i < 50; i += 1)
	{
		series.push_back(i);
	}
	for (size_t i = 0; i < series.size(); i++)
	{
		std::cout << " " << series[i] << std::endl;;
	}

	std::cout << std::endl;;

	ft::vector<int>::iterator first = series.begin() + 2;
	ft::vector<int>::iterator second = series.end() - 2;

	ft::vector<int> series2(first, second);
	for (size_t i = 0; i < series2.size(); i++)
	{
		std::cout << " " << series2[i] << std::endl;;
	}
}
