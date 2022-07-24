/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lab.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 05:54:19 by gunkim            #+#    #+#             */
/*   Updated: 2022/07/25 02:07:52 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator>
#include <vector.hpp>
#include <vector>

int main()
{
	ft::vector<int> vector_int;
	std::cout << "size:" << vector_int.size() << std::endl;

	ft::vector<int>::iterator itei = vector_int.begin();
	vector_int.insert(itei, 42);
	
	itei = vector_int.begin();
	// vector_int.insert(itei++, 43);
	vector_int.insert(++itei, 43);
	// vector_int.insert(--itei, 41);
	std::cout << "size:" << vector_int.size() << std::endl;
	for (int i = 0; i < 3; i++)
		std::cout << vector_int[i] << std::endl;
}
