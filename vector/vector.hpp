/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:41:59 by gunkim            #+#    #+#             */
/*   Updated: 2022/07/25 02:08:08 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <algorithm>
#include <vector>
#include <iterator>
#include <memory>

namespace ft
{
template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};


// Category
class input_iterator_tag {};
class output_iterator_tag {};
class forward_iterator_tag			: public input_iterator_tag			{};
class bidirectional_iterator_tag	: public forward_iterator_tag		{};
class random_access_iterator_tag	: public bidirectional_iterator_tag	{}; //most functional thing

template <typename T>
class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
{
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
		typedef T*																				pointer;
		typedef T&																				reference;
	private:
		pointer _elem;
	
	public:
	random_access_iterator(void) : _elem(NULL) {}
	random_access_iterator(pointer elem) : _elem(elem) {}
	random_access_iterator(const random_access_iterator& copy) : _elem(copy._elem) {}
	random_access_iterator& operator=(const random_access_iterator& copy)
	{
		this->_elem = copy._elem;
		return (*this);
	}
	~random_access_iterator() {}

	pointer base() const { return (this->_elem); }
	reference operator*(void) const { return (*_elem); }
	
	random_access_iterator& operator++(void)
	{
		_elem++;
		return (*this);
	}

	random_access_iterator operator++(int)
	{
		random_access_iterator temp(*this);
		_elem++;
		return (temp);
	}
};

template <class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef Alloc																	allocator_type;
	typedef T 																		value_type;
	typedef typename allocator_type::size_type										size_type;//usually std::size_t
	typedef typename allocator_type::difference_type								difference_type;//usually std::ptrdiff_t
	typedef typename allocator_type::reference										reference;
	typedef typename allocator_type::const_reference								const_reference;
	typedef typename allocator_type::pointer										pointer;
	typedef typename allocator_type::const_pointer									const_pointer;
	typedef typename ft::random_access_iterator<value_type>							iterator;
	typedef typename ft::random_access_iterator<const value_type>					const_iterator;
	// typedef typename ft::reverse_iterator<iterator>									reverse_iterator;
	// typedef typename ft::reverse_iterator<const_iterator>							const_reverse_iterator;

private:
	pointer			_begin;// pointer
	pointer			_end;// size
	pointer			_end_cap;// capacity
	allocator_type	_alloc;

public:
	explicit vector(const allocator_type& alloc = allocator_type())
	:
		_begin(NULL),
		_end(NULL),
		_end_cap(NULL),
		_alloc(alloc)
	{}

	/* n개의 컨테이너를 여러개 만드는 함수 */
	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	:
		_begin(NULL),
		_end(NULL),
		_end_cap(NULL),
		_alloc(alloc)
	{
		if (n > max_size())
		{
			throw (std::length_error("vector::vector"));
		}
		_begin = _alloc.allocate(n);
		_end_cap = _begin + n;
		_end = _begin;
		while (_end != _end_cap)
		{
			_alloc.construct(_end, val);
			_end++;
		}
	}

	/* range constructor */
	// template<class InputIterator>
	// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	// :
	// 	_alloc(alloc),
	// 	_size(0),
	// 	_cap(0)
	// {
	// 	size_t n = last.pointer - first.pointer;
	// 	reserve(n);
	// 	for (int i = 0; i < n; i++)
	// 	{
	// 		_alloc.construct(_ptr + i, *(first + i));
	// 	}
	// 	_size = n;
	// }

	/* copy constructor */
	// vector(const vector& x)
	// :
	// 	_alloc(allocator_type()),
	// 	x::iterator itrx = x.begin();
	// {
	// 	reserve(x.size());
	// 	for(size_t i = 0; i < x.size(); i++)
	// 	{
	// 		_alloc.construct(_ptr + i, x);
	// 	}
	// }

	iterator begin()
	{
		return (_begin);
	}

	const_iterator begin() const
	{
		return (_begin);
	}
	
	iterator end()
	{
		return (_end);
	}

	const_iterator end() const
	{
		return (_end);
	}

	// reverse_iterator rbegin()
	// {
		
	// }

	// const_reverse_iterator rbegin() const
	// {
		
	// }

	// reverse_iterator rend()
	// {
		
	// }

	// const_reverse_iterator rend() const
	// {
		
	// }

	/* Capacity: */

	size_type size() const
	{
		return (_end - _begin);
	}

	size_type max_size() const
	{
		return (_alloc.max_size());
	}

	void resize(size_type n, value_type val = value_type())
	{
		if (n > this->max_size())
		{
			throw (std::length_error("vector::resize"));
		}

		size_type size = this->size();
		size_type capacity = this->capacity();
		if (n > size)
		{
			if (n > capacity)
			{
				reserve(n);
			}
			size_type times = n - size;
			while (times--)
			{
				_alloc.contruct(_end, val);
				_end++;
			}
		}
		else if (n < size)
		{
			size_type times = size - n;
			while (times--)
			{
				_end--;
				_alloc.destroy(_end);
			}
		}
	}

	size_type capacity() const
	{
		return (_end_cap - _begin);
	}

	bool empty() const
	{
		return ((this->size() == 0) ? true : false);
	}

	void reserve(size_type n)
	{
		if (n < this->capacity())
			return ;

		pointer new_begin = _alloc.allocate(n);
		size_type size = this->size();
		size_type capacity = this->capacity();

		for (size_type i = 0; i < size; i++)
		{
			_alloc.construct(new_begin + i, *(_begin + i));
			_alloc.destroy(_begin + i);
		}
		_alloc.deallocate(_begin, capacity);
		_begin = new_begin;
		_end = _begin + size;
		_end_cap = _begin + n;
	}

	/* Element access */
    reference operator[] (size_type n)
	{
		return (*(_begin + n));	
	}

	const_reference operator[] (size_type n) const
	{
		return (*(_begin + n));	
	}

	// void push_back(const value_type& val)
	// {
	// 	insert(end(), val);
	// }

	/* insert */
	/* single element(1) */
	iterator insert(iterator position, const value_type& val)
	{
		// pointer pos = &(*position);
		size_type pos = &(*position) - _begin;
		if (pos < 0 || this->size() < pos)
		{
			throw std::logic_error("vector");
		}
		size_type size = this->size();
		size_type capacity = this->capacity();
		if (size + 1 > capacity)
		{
			reserve((size == 0) ? 1 : size * 2);
		}
		_alloc.construct(_end, val);
		for (size_type i = 0; size - i != pos; i++)
		{
			*(_end - i) = *(_end - i - 1);
		}
		*(_begin + pos) = val;
		_end++;
		return (_begin + pos);
	}

	/* fill */

	/* range */
};

/*
** https://cplusplus.com/reference/iterator/iterator_traits/
*/
template <class Iterator>
class iterator_traits
{
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

//not defined;
template <class T> class iterator_traits<T*>
{
	typedef ptrdiff_t								difference_type;
	typedef T										value_type;
	typedef T*										pointer;
	typedef T&										reference;
	typedef typename ft::random_access_iterator_tag	iterator_category;
};

template <class T> class
iterator_traits<const T*>
{
	typedef ptrdiff_t								difference_type;
	typedef T										value_type;
	typedef T*										pointer;
	typedef T&										reference;
	typedef typename ft::random_access_iterator_tag	iterator_category;
};

/*
** https://cplusplus.com/reference/iterator/reverse_iterator/
*/
template <class Iterator>
class reverse_iterator
{
public:
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;
};

};
