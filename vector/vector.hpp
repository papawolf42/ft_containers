/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:41:59 by gunkim            #+#    #+#             */
/*   Updated: 2022/07/18 05:50:28 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <algorithm>
#include <vector>
#include <memory>

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef Alloc																	allocator_type;
private:
	typedef T 																		value_type;
	typedef typename allocator_type::reference										reference;
	typedef typename allocator_type::const_reference								const_reference;
	typedef typename allocator_type::pointer										pointer;
	typedef typename allocator_type::const_pointer									const_pointer;
	typedef ft::iterator<random_access_iterator_tag, value_type>					iterator;
	typedef const ft::iterator<random_access_iterator_tag, value_type>				const_iterator;
	typedef typename allocator_type::difference_type								difference_type;
	typedef typename allocator_type::size_type										size_type;

	allocator_type	_alloc;// allocator
	pointer			_ptr;// pointer
	size_t			_size;// size
	size_t			_cap;// capacity

	vector() : _ptr(NULL), _size(0), _cap(0) {}

	explicit vector(const allocator_type& alloc = allocator_type())
	:
		_alloc(alloc),
		_ptr(NULL),
		_size(0),
		_cap(0)
	{}

	/* n개의 컨테이너를 여러개 만드는 함수 */
	// explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	// :
	// {}

	/* range constructor */
	// template<class InputIterator>
	// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	// :
	// {}

	/* copy constructor */
	// vector(const vector& x);

	iterator begin()
	{
		return (_ptr);
	}

	const_iterator begin() const
	{
		return (_ptr);
	}
	
	iterator end()
	{
		return (_ptr + _size);
	}

	const_iterator end() const
	{
		return (_ptr + _size);
	}

	size_type size() const
	{
		return (_size);
	}

	void push_back(const value_type& val)
	{
		insert(end(), val);
	}

	/* CAPACITY */
	/* resize */
	void resize (size_type n, value_type val = value_type())
	{
		// n < size
		// n > size
		// n > capacity
	}

	/* reserve */
	void reserve(size_type n)
	{
		if (n < _cap)
			return ;
		pointer new_ptr = _alloc.allocate(n);
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.construct(new_ptr + i, _ptr + i);
			_alloc.destory(_ptr + i);
		}
		_alloc.deallocate(_ptr, _cap);
		_cap = n;
		_ptr = new_ptr;
	}

	/* insert */
	/* single element(1) */
	iterator insert (iterator position, const value_type& val)
	{
		// index 0 1 2
		// value 1 2 3
		// insert(2, 4);
		// after
		// index 0 1 2 3
		// value 1 2 4 3
		size_type index = position - _ptr;
		if (++_size > _cap)
		{
			reserve(_size * 2);
		}
		if (index == _size)
		{
			_alloc.construct(_ptr + _size, val);
		}
		else
		{
			_alloc.construct(_ptr + _size, *(_ptr + _size - 1));
			int i = _size - 1;
			for (; i > index ; i--;)
			{
				*(_ptr + i) = *(_ptr + i - 1);
			}
			*(_ptr + i) = val;
		}
		_size++;
	}

	/* fill */

	/* range */
};

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;

	iterator()
	{};
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
	typedef typename ptrdiff_t						difference_type;
	typedef typename T								value_type;
	typedef typename T*								pointer;
	typedef typename T&								reference;
	typedef typename ft::random_access_iterator_tag	iterator_category;//not implemented
};

template <class T> class
iterator_traits<const T*>
{
	typedef typename ptrdiff_t						difference_type;
	typedef typename T								value_type;
	typedef typename T*								pointer;
	typedef typename T&								reference;
	typedef typename ft::random_access_iterator_tag	iterator_category;//not implemented
};


// Category
class input_iterator_tag { };
class output_iterator_tag { };
class forward_iterator_tag { };
class bidirectional_iterator_tag { };
class random_access_iterator_tag { }; //most functional thing

template <typename T>
class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
{
public:
	typedef typename ft:iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
	typedef typename Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};


template <typename T>
class random_access_iterator : iterator<random_access_iterator_tag, T>
{
public:
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
	typedef T*																				pointer;
	typedef T&																				reference;

	/* Input */
	/* Output */
	/* Forward */
	/* Bidirectional */
	/* Random Access */
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
