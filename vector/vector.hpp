/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:41:59 by gunkim            #+#    #+#             */
/*   Updated: 2022/08/04 17:57:04 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <algorithm>
#include <vector>
#include <iterator>
#include <memory>

namespace ft
{

template<bool Is_bool, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };

template <bool is_integral, typename T>
	struct is_integral_res {
		typedef T type;// 이건 왜 있는지 모르곘네???
		static const bool value = is_integral;
	};

template <typename>
	struct is_integral_type : public is_integral_res<false, bool> {};
template <>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};
template <>
	struct is_integral_type<char> : public is_integral_res<true, char> {};
template <>
	struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
template <>
	struct is_integral_type<short int> : public is_integral_res<true, short int> {};
template <>
	struct is_integral_type<int> : public is_integral_res<true, int> {};
template <>
	struct is_integral_type<long int> : public is_integral_res<true, long int> {};
template <>
	struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
template <>
	struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
template <>
	struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
template <>
	struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
template <>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

template <typename T>
	struct is_integral : public is_integral_type<T> {};

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

/*
** https://cplusplus.com/reference/iterator/iterator_traits/
*/
template <class Iterator>
class iterator_traits
{
public:
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

// template<class InputIterator>
// 	typename ft::iterator_traits<InputIterator>::difference_type
// 		distance (InputIterator first, InputIterator last)
// 		{
// 			typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
// 			while (first != last)
// 			{
// 				first++;
// 				rtn++;
// 			}
// 			return (rtn);
// 		}

template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distance (InputIterator first, InputIterator last)
{
	typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
	while (first != last)
	{
		first++;
		rtn++;
	}
	return (rtn);
}

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

	// implement const_iterator
	template <class U>
	random_access_iterator(const random_access_iterator<U>& u) : _elem(u.base()) {}

	~random_access_iterator() {}

	pointer base() const
	{
		return (_elem);
	}

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
	
	random_access_iterator& operator--(void)
	{
		_elem--;
		return (*this);
	}

	random_access_iterator operator--(int)
	{
		random_access_iterator temp(*this);
		_elem--;
		return (temp);
	}

	random_access_iterator operator+(int num)
	{
		return (_elem + num);
	}

	random_access_iterator operator-(difference_type num)
	{
		return (_elem - num);
	}

	// 반복자간 빼기일 경우, 그 거리(정수)를 리턴.
	int operator-(random_access_iterator& itr)
	{
		return (_elem - itr._elem);
	}

	random_access_iterator& operator+=(int num)
	{
		this->_elem += num;
		return (*this);
	}

	random_access_iterator& operator-=(int num)
	{
		this->_elem -= num;
		return (*this);
	}

	value_type& operator[](size_t idx)
	{
		return (*(_elem + idx));
	}

	value_type& operator=(const value_type& val) const
	{
		return (*(_elem = val));
	}

	//equality/inequality comparisons operator
	bool operator==(const random_access_iterator& itr) const
	{
		return ((_elem == itr._elem) ? 1 : 0);
	}

	bool operator!=(const random_access_iterator& itr) const
	{
		return ((_elem != itr._elem) ? 1 : 0);
	}

	//inequality comparisons operator
	bool operator>(const random_access_iterator& itr) const
	{
		return ((_elem > itr._elem) ? 1 : 0);
	}

	bool operator>=(const random_access_iterator& itr) const
	{
		return ((_elem >= itr._elem) ? 1 : 0);
	}

	bool operator<(const random_access_iterator& itr) const
	{
		return ((_elem < itr._elem) ? 1 : 0);
	}

	bool operator<=(const random_access_iterator& itr) const
	{
		return ((_elem <= itr._elem) ? 1 : 0);
	}

	pointer operator->() const
	{
		return (_elem);
	}

	friend random_access_iterator operator+(int idx, random_access_iterator& itr);
	friend random_access_iterator operator-(int idx, random_access_iterator& itr);
};

template <class T>
random_access_iterator<T> operator+(int idx, random_access_iterator<T>& itr)
{
	return (itr._elem + idx);
}

template <class T>
random_access_iterator<T> operator-(int idx, random_access_iterator<T>& itr)
{
	return (itr._elem - idx);
}

/*
** https://cplusplus.com/reference/iterator/reverse_iterator/
*/
template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;

private:
	iterator_type _elem;
	// pointer _elem;// 원래 이거였는데

public:
	reverse_iterator()
	:
		_elem(NULL)
	{}

	explicit reverse_iterator(iterator_type it)
	:
		_elem(it)
	{}

	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it)
	:
		_elem(rev_it.base())
	{}

	iterator_type base() const
	{
		return (_elem);
	}

	reference operator*() const
	{
		iterator_type tmp = this->_elem;
		return (*(--(tmp)));
	}

	reverse_iterator operator+(difference_type n) const
	{
		return (reverse_iterator(_elem - n));
	}

	//save

	reverse_iterator& operator++()
	{
		_elem--;
		return (*this);
	}

	reverse_iterator operator++(int)
	{
		reverse_iterator temp(_elem--);
		return (temp);
	}

	reverse_iterator operator-(difference_type n) const
	{
		return (reverse_iterator(_elem + n));
	}

	reverse_iterator& operator--()
	{
		_elem++;
		return (*this);
	}

	reverse_iterator operator--(int)
	{
		reverse_iterator temp(_elem++);
		return (temp);
	}

	reverse_iterator& operator+=(difference_type n)
	{
		_elem -= n;
		return (*this);
	}

	reverse_iterator& operator-=(difference_type n)
	{
		_elem -= n;
		return (*this);
	}

	reference operator[](difference_type n) const
	{
		return (*(_elem - n));
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	friend bool operator==(const reverse_iterator& lhs, const reverse_iterator& rhs);
	friend bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	friend bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	friend bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	friend bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	friend bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
};

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
{
	return (rev_it + n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() - rhs.base());
}

template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return ((lhs.base() == rhs.base()) ? true : false);
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return ((lhs.base() != rhs.base()) ? true : false);
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return ((lhs.base() < rhs.base()) ? true : false);
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return ((lhs.base() <= rhs.base()) ? true : false);
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return ((lhs.base() > rhs.base()) ? true : false);
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return ((lhs.base() >= rhs.base()) ? true : false);
}

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
	typedef typename ft::reverse_iterator<iterator>									reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>							const_reverse_iterator;

private:
	pointer			_begin;// pointer
	pointer			_end;// size
	pointer			_end_cap;// capacity
	allocator_type	_alloc;

public:
	explicit vector (const allocator_type& alloc = allocator_type())
	:
		_begin(NULL),
		_end(NULL),
		_end_cap(NULL),
		_alloc(alloc)
	{}

	/* n개의 컨테이너를 여러개 만드는 함수 */
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
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
	template<class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
	:
		_begin(NULL),
		_end(NULL),
		_end_cap(NULL),
		_alloc(alloc)
	{
		// size_type n = &(*last) - &(*first);
		difference_type n = ft::distance(first, last);
		_begin = _alloc.allocate(n);
		for (size_type i = 0; i < n; i++)
		{
			_alloc.construct(_begin + i, *(first + i));
		}
		_end = _begin + n;
		_end_cap = _end;
	}

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
		return (iterator(_begin));
	}

	const_iterator begin() const
	{
		return (iterator(_begin));
	}
	
	iterator end()
	{
		return (iterator(_end));
	}

	const_iterator end() const
	{
		return (iterator(_end));
	}

	reverse_iterator rbegin()
	{
		
	}

	const_reverse_iterator rbegin() const
	{
		
	}

	reverse_iterator rend()
	{
		
	}

	const_reverse_iterator rend() const
	{
		
	}

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

	reference at (size_type n)
	{
		return (*(_begin + n));
	}

	const_reference at (size_type n) const
	{
		return (*(_begin + n));
	}

	reference front()
	{
		return (*(_begin));
	}

	const_reference front() const
	{
		return (*(_begin));
	}

	reference back()
	{
		return (*(_end - 1));
	}

	const_reference back() const
	{
		return (*(_end - 1));
	}

	/* Modifier */

	// assign range
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last)
	{
		size_type n = last - first;
		if (n > this->max_size())
		{
			throw (std::length_error("vector::vector"));
		}
		size_type size = this->size();
		size_type capacity = this->capacity();
		if (n > capacity)
		{
			for (int i = 0; i < size; i++)
			{
				_alloc.destroy(_begin + i);
			}
			_alloc.deallocate(_begin, capacity);
			_begin = _alloc.allocate(n);
			for (int i = 0; i < n; i++)
			{
				_alloc.construct(_begin + i, first.base() + i);
			}
			_end_cap = _begin + n;
			_end = _end_cap;
		}
		else if (n <= capacity)
		{
			for (int i = n; i < size; i++)
			{
				_alloc.destroy(_begin + i);
			}
			for (int i = size; i < n; i++)
			{
				_alloc.construct(_begin + i, first.base() + i);
			}
			for (int i = 0; i < size; i++)
			{
				*(_begin + i) = first.base() + i;
			}
			_end = _begin + n;
		}
	}

	// assign fill
	void assign(size_type n, const value_type& val)
	{
		if (n > max_size())
		{
			throw (std::length_error("vector::vector"));
		}
		size_type size = this->size();
		size_type capacity = this->capacity();
		if (n > capacity)
		{
			for (int i = 0; i < size; i++)
			{
				_alloc.destroy(_begin + i);
			}
			_alloc.deallocate(_begin, capacity);
			_begin = _alloc.allocate(n);
			for (int i = 0; i < n; i++)
			{
				_alloc.construct(_begin + i, val);
			}
			_end_cap = _begin + n;
			_end = _end_cap;
		}
		else if (n <= capacity)
		{
			for (int i = n; i < size; i++)
			{
				_alloc.destroy(_begin + i);
			}
			for (int i = size; i < n; i++)
			{
				_alloc.construct(_begin + i, val);
			}
			for (int i = 0; i < n; i++)
			{
				*(_begin + i) = val;
			}
			_end = _begin + n;
		}
	}

	void push_back(const value_type& val)
	{
		insert(end(), val);
	}

	void pop_back()
	{
		erase(end() - 1);
	}

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
	void insert (iterator position, size_type n, const value_type& val)
	{
		size_type pos = &(*position) - _begin;
		if (pos < 0 || this->size() < pos)
		{
			throw std::logic_error("vector");
		}
		size_type size = this->size();
		size_type capacity = this->capacity();
		if (size + pos > capacity)
		{
			reserve((size == 0) ? n : size + pos);
		}
		// 여기서 capacity를 보장받게됨.
		// 이밑에서는 이제 복사가 일어나야하는데. 
		// 2가지 정도로 분기를 생각해볼 수 있음
		// 1. pos가 end라서, 그대로 추가되는 경우, 이 경우는 construct만 일어나게됨
		// 2. pos가 size 아래에 존재해서, 복사 + 삽입이 일어나야 하는 경우. 
		//		그럼 pos 위치에서, size + pos으로 (size - pos) 번 construct
		//		그런 다음, 남은 횟수 
		for (size_type i = 0; i < size - pos; i++)
		{
			_alloc.construct(_begin + size + n - 1 - i, _begin + size - i - 1);
		}
		for (size_type i = 0; i < n - (size - pos); i++)
		{
			_alloc.construct(_begin + size + i, val);
		}
		for (size_type i = 0; i < size - pos; i++)
		{
			*(_begin + size - i) = val;
		}
		size += n;
		_end = _begin + size;
	}

	/* range */

	//single
	iterator erase (iterator position)
	{
		size_type pos = &(*position) - _begin;
		if (pos < 0 || this->size() < pos)
		{
			throw std::logic_error("vector");
		}
		size_type size = this->size();
		size_type time = size - pos;
		for (size_type i = 0; i < time; i++)
		{
			*(_begin + pos + i) = *(_begin + pos + i + 1);
		}
		_alloc.destroy(_end);
		_end--;
		return (_begin + pos);
	}

	//range
	//iterator erase (iterator first, iterator last);

};

};
