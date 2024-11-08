#ifndef SET_HPP
# define SET_HPP

# include <__algorithm/equal.h>
# include <__algorithm/lexicographical_compare.h>
# include <__algorithm/lexicographical_compare_three_way.h>
# include <__assert> // all public C++ headers provide the assertion handler
# include <__availability>
# include <__config>
# include <__functional/is_transparent.h>
# include <__functional/operations.h>
# include <__iterator/erase_if_container.h>
# include <__iterator/iterator_traits.h>
# include <__iterator/ranges_iterator_traits.h>
# include <__iterator/reverse_iterator.h>
# include <__memory/allocator.h>
# include <__memory_resource/polymorphic_allocator.h>
# include <__node_handle>
# include <__ranges/concepts.h>
# include <__ranges/container_compatible_range.h>
# include <__ranges/from_range.h>
# include "__tree"
# include <__type_traits/is_allocator.h>
# include <__utility/forward.h>
# include <version>

// standard-mandated includes

// [iterator.range]
# include <__iterator/access.h>
# include <__iterator/data.h>
# include <__iterator/empty.h>
# include <__iterator/reverse_access.h>
# include <__iterator/size.h>

// [associative.set.syn]
# include <compare>
# include <initializer_list>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
# include <__undef_macros>

# if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
# endif

namespace ft {
	template <class _Key, class _Compare, class _Allocator>
	class multiset;

	template <class _Key, class _Compare = std::less<_Key>, class _Allocator = std::allocator<_Key> >
	class _LIBCPP_TEMPLATE_VIS set
	{
	public:
		// types:
		typedef _Key                                     key_type;
		typedef key_type                                 value_type;
		typedef std::__type_identity_t<_Compare>         key_compare;
		typedef key_compare                              value_compare;
		typedef std::__type_identity_t<_Allocator>       allocator_type;
		typedef value_type&                              reference;
		typedef const value_type&                        const_reference;

		static_assert((std::is_same<typename allocator_type::value_type, value_type>::value),
					"Allocator::value_type must be same type as value_type");

	private:
		typedef __tree<value_type, value_compare, allocator_type>      __base;
		typedef std::allocator_traits<allocator_type>                  __alloc_traits;

		__base __tree_;

	public:
		typedef typename __base::pointer                pointer;
		typedef typename __base::const_pointer          const_pointer;
		typedef typename __base::size_type              size_type;
		typedef typename __base::difference_type        difference_type;
		typedef typename __base::const_iterator         iterator;
		typedef typename __base::const_iterator         const_iterator;
		typedef _VSTD::reverse_iterator<iterator>       reverse_iterator;
		typedef _VSTD::reverse_iterator<const_iterator> const_reverse_iterator;

	# if _LIBCPP_STD_VER > 14
		typedef std::__set_node_handle<typename __base::__node, allocator_type> node_type;
		typedef std::__insert_return_type<iterator, node_type> insert_return_type;
	# endif

		template <class _Key2, class _Compare2, class _Alloc2>
			friend class _LIBCPP_TEMPLATE_VIS set;
		template <class _Key2, class _Compare2, class _Alloc2>
			friend class _LIBCPP_TEMPLATE_VIS multiset;

		_LIBCPP_INLINE_VISIBILITY
		set()
			_NOEXCEPT_(
				std::is_nothrow_default_constructible<allocator_type>::value &&
				std::is_nothrow_default_constructible<key_compare>::value &&
				std::is_nothrow_copy_constructible<key_compare>::value)
			: __tree_(value_compare()) {}

		_LIBCPP_INLINE_VISIBILITY
		explicit set(const value_compare& __comp)
			_NOEXCEPT_(
				std::is_nothrow_default_constructible<allocator_type>::value &&
				std::is_nothrow_copy_constructible<key_compare>::value)
			: __tree_(__comp) {}

		_LIBCPP_INLINE_VISIBILITY
		explicit set(const value_compare& __comp, const allocator_type& __a)
			: __tree_(__comp, __a) {}
		template <class _InputIterator>
			_LIBCPP_INLINE_VISIBILITY
			set(_InputIterator __f, _InputIterator __l,
				const value_compare& __comp = value_compare())
			: __tree_(__comp)
			{
				insert(__f, __l);
			}

		template <class _InputIterator>
			_LIBCPP_INLINE_VISIBILITY
			set(_InputIterator __f, _InputIterator __l, const value_compare& __comp,
				const allocator_type& __a)
			: __tree_(__comp, __a)
			{
				insert(__f, __l);
			}

	# if _LIBCPP_STD_VER > 11
			template <class _InputIterator>
			_LIBCPP_INLINE_VISIBILITY
			set(_InputIterator __f, _InputIterator __l, const allocator_type& __a)
				: set(__f, __l, key_compare(), __a) {}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		set(const set& __s)
			: __tree_(__s.__tree_)
			{
				insert(__s.begin(), __s.end());
			}

		_LIBCPP_INLINE_VISIBILITY
		set& operator=(const set& __s)
			{
				__tree_ = __s.__tree_;
				return *this;
			}

	# ifndef _LIBCPP_CXX03_LANG
		_LIBCPP_INLINE_VISIBILITY
		set(set&& __s)
			_NOEXCEPT_(std::is_nothrow_move_constructible<__base>::value)
			: __tree_(_VSTD::move(__s.__tree_)) {}
	# endif // _LIBCPP_CXX03_LANG

		_LIBCPP_INLINE_VISIBILITY
		explicit set(const allocator_type& __a)
			: __tree_(__a) {}

		_LIBCPP_INLINE_VISIBILITY
		set(const set& __s, const allocator_type& __a)
			: __tree_(__s.__tree_.value_comp(), __a)
			{
				insert(__s.begin(), __s.end());
			}

	# ifndef _LIBCPP_CXX03_LANG
		set(set&& __s, const allocator_type& __a);

		_LIBCPP_INLINE_VISIBILITY
		set(std::initializer_list<value_type> __il, const value_compare& __comp = value_compare())
			: __tree_(__comp)
			{
				insert(__il.begin(), __il.end());
			}

		_LIBCPP_INLINE_VISIBILITY
		set(std::initializer_list<value_type> __il, const value_compare& __comp,
			const allocator_type& __a)
			: __tree_(__comp, __a)
			{
				insert(__il.begin(), __il.end());
			}

	# if _LIBCPP_STD_VER > 11
		_LIBCPP_INLINE_VISIBILITY
		set(std::initializer_list<value_type> __il, const allocator_type& __a)
			: set(__il, key_compare(), __a) {}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		set& operator=(std::initializer_list<value_type> __il)
			{
				__tree_.__assign_unique(__il.begin(), __il.end());
				return *this;
			}

		_LIBCPP_INLINE_VISIBILITY
		set& operator=(set&& __s)
			_NOEXCEPT_(std::is_nothrow_move_assignable<__base>::value)
			{
				__tree_ = std::move(__s.__tree_);
				return *this;
			}
	# endif // _LIBCPP_CXX03_LANG

		_LIBCPP_INLINE_VISIBILITY
		~set() {
			static_assert(sizeof(__diagnose_non_const_comparator<_Key, _Compare>()), "");
		}

		_LIBCPP_INLINE_VISIBILITY
			iterator begin() _NOEXCEPT       {return __tree_.begin();}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator begin() const _NOEXCEPT {return __tree_.begin();}
		_LIBCPP_INLINE_VISIBILITY
			iterator end() _NOEXCEPT         {return __tree_.end();}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator end()   const _NOEXCEPT {return __tree_.end();}

		_LIBCPP_INLINE_VISIBILITY
			reverse_iterator rbegin() _NOEXCEPT
				{return reverse_iterator(end());}
		_LIBCPP_INLINE_VISIBILITY
		const_reverse_iterator rbegin() const _NOEXCEPT
			{return const_reverse_iterator(end());}
		_LIBCPP_INLINE_VISIBILITY
			reverse_iterator rend() _NOEXCEPT
				{return reverse_iterator(begin());}
		_LIBCPP_INLINE_VISIBILITY
		const_reverse_iterator rend() const _NOEXCEPT
			{return const_reverse_iterator(begin());}

		_LIBCPP_INLINE_VISIBILITY
		const_iterator cbegin()  const _NOEXCEPT {return begin();}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator cend() const _NOEXCEPT {return end();}
		_LIBCPP_INLINE_VISIBILITY
		const_reverse_iterator crbegin() const _NOEXCEPT {return rbegin();}
		_LIBCPP_INLINE_VISIBILITY
		const_reverse_iterator crend() const _NOEXCEPT {return rend();}

		_LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY
		bool empty() const _NOEXCEPT {return __tree_.size() == 0;}
		_LIBCPP_INLINE_VISIBILITY
		size_type size() const _NOEXCEPT {return __tree_.size();}
		_LIBCPP_INLINE_VISIBILITY
		size_type max_size() const _NOEXCEPT {return __tree_.max_size();}

		// modifiers:
	# ifndef _LIBCPP_CXX03_LANG
		template <class... _Args>
			_LIBCPP_INLINE_VISIBILITY
			 std::pair<iterator, bool> emplace(_Args&&... __args)
				{return __tree_.__emplace_unique(_VSTD::forward<_Args>(__args)...);}
		template <class... _Args>
			_LIBCPP_INLINE_VISIBILITY
			iterator emplace_hint(const_iterator __p, _Args&&... __args)
				{return __tree_.__emplace_hint_unique(__p, _VSTD::forward<_Args>(__args)...);}
	# endif // _LIBCPP_CXX03_LANG

		_LIBCPP_INLINE_VISIBILITY
		std::pair<iterator,bool> insert(const value_type& __v)
			{return __tree_.__insert_unique(__v);}
		_LIBCPP_INLINE_VISIBILITY
		iterator insert(const_iterator __p, const value_type& __v)
			{return __tree_.__insert_unique(__p, __v);}

		template <class _InputIterator>
			_LIBCPP_INLINE_VISIBILITY
			void insert(_InputIterator __f, _InputIterator __l)
			{
				for (const_iterator __e = cend(); __f != __l; ++__f)
					__tree_.__insert_unique(__e, *__f);
			}

	# ifndef _LIBCPP_CXX03_LANG
		_LIBCPP_INLINE_VISIBILITY
		 std::pair<iterator,bool> insert(value_type&& __v)
			{return __tree_.__insert_unique(_VSTD::move(__v));}

		_LIBCPP_INLINE_VISIBILITY
		iterator insert(const_iterator __p, value_type&& __v)
			{return __tree_.__insert_unique(__p, _VSTD::move(__v));}

		_LIBCPP_INLINE_VISIBILITY
		void insert(std::initializer_list<value_type> __il)
			{insert(__il.begin(), __il.end());}
	# endif // _LIBCPP_CXX03_LANG

		_LIBCPP_INLINE_VISIBILITY
		iterator  erase(const_iterator __p) {return __tree_.erase(__p);}
		_LIBCPP_INLINE_VISIBILITY
		size_type erase(const key_type& __k)
			{return __tree_.__erase_unique(__k);}
		_LIBCPP_INLINE_VISIBILITY
		iterator  erase(const_iterator __f, const_iterator __l)
			{return __tree_.erase(__f, __l);}
		_LIBCPP_INLINE_VISIBILITY
		void clear() _NOEXCEPT {__tree_.clear();}

	# if _LIBCPP_STD_VER > 14
		_LIBCPP_INLINE_VISIBILITY
		insert_return_type insert(node_type&& __nh)
		{
			_LIBCPP_ASSERT(__nh.empty() || __nh.get_allocator() == get_allocator(),
				"node_type with incompatible allocator passed to set::insert()");
			return __tree_.template __node_handle_insert_unique<
				node_type, insert_return_type>(_VSTD::move(__nh));
		}
		_LIBCPP_INLINE_VISIBILITY
		iterator insert(const_iterator __hint, node_type&& __nh)
		{
			_LIBCPP_ASSERT(__nh.empty() || __nh.get_allocator() == get_allocator(),
				"node_type with incompatible allocator passed to set::insert()");
			return __tree_.template __node_handle_insert_unique<node_type>(
				__hint, _VSTD::move(__nh));
		}
		_LIBCPP_INLINE_VISIBILITY
		node_type extract(key_type const& __key)
		{
			return __tree_.template __node_handle_extract<node_type>(__key);
		}
		_LIBCPP_INLINE_VISIBILITY
		node_type extract(const_iterator __it)
		{
			return __tree_.template __node_handle_extract<node_type>(__it);
		}
		template <class _Compare2>
		_LIBCPP_INLINE_VISIBILITY
		void merge(set<key_type, _Compare2, allocator_type>& __source)
		{
			_LIBCPP_ASSERT(__source.get_allocator() == get_allocator(),
						"merging container with incompatible allocator");
			__tree_.__node_handle_merge_unique(__source.__tree_);
		}
		template <class _Compare2>
		_LIBCPP_INLINE_VISIBILITY
		void merge(set<key_type, _Compare2, allocator_type>&& __source)
		{
			_LIBCPP_ASSERT(__source.get_allocator() == get_allocator(),
						"merging container with incompatible allocator");
			__tree_.__node_handle_merge_unique(__source.__tree_);
		}
		template <class _Compare2>
		_LIBCPP_INLINE_VISIBILITY
		void merge(multiset<key_type, _Compare2, allocator_type>& __source)
		{
			_LIBCPP_ASSERT(__source.get_allocator() == get_allocator(),
						"merging container with incompatible allocator");
			__tree_.__node_handle_merge_unique(__source.__tree_);
		}
		template <class _Compare2>
		_LIBCPP_INLINE_VISIBILITY
		void merge(multiset<key_type, _Compare2, allocator_type>&& __source)
		{
			_LIBCPP_ASSERT(__source.get_allocator() == get_allocator(),
						"merging container with incompatible allocator");
			__tree_.__node_handle_merge_unique(__source.__tree_);
		}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		void swap(set& __s) _NOEXCEPT_(std::__is_nothrow_swappable<__base>::value)
			{__tree_.swap(__s.__tree_);}

		_LIBCPP_INLINE_VISIBILITY
		allocator_type get_allocator() const _NOEXCEPT {return __tree_.__alloc();}
		_LIBCPP_INLINE_VISIBILITY
		key_compare    key_comp()      const {return __tree_.value_comp();}
		_LIBCPP_INLINE_VISIBILITY
		value_compare  value_comp()    const {return __tree_.value_comp();}

		// set operations:
		_LIBCPP_INLINE_VISIBILITY
		iterator find(const key_type& __k)             {return __tree_.find(__k);}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator find(const key_type& __k) const {return __tree_.find(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,iterator>::type
		find(const _K2& __k)                           {return __tree_.find(__k);}
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,const_iterator>::type
		find(const _K2& __k) const                     {return __tree_.find(__k);}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		size_type      count(const key_type& __k) const
			{return __tree_.__count_unique(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,size_type>::type
		count(const _K2& __k) const                    {return __tree_.__count_multi(__k);}
	# endif

	# if _LIBCPP_STD_VER > 17
		_LIBCPP_INLINE_VISIBILITY
		bool contains(const key_type& __k) const {return find(__k) != end();}
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value, bool>::type
		contains(const _K2& __k) const { return find(__k) != end(); }
	# endif // _LIBCPP_STD_VER > 17

		_LIBCPP_INLINE_VISIBILITY
		iterator lower_bound(const key_type& __k)
			{return __tree_.lower_bound(__k);}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator lower_bound(const key_type& __k) const
			{return __tree_.lower_bound(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,iterator>::type
		lower_bound(const _K2& __k)       {return __tree_.lower_bound(__k);}

		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,const_iterator>::type
		lower_bound(const _K2& __k) const {return __tree_.lower_bound(__k);}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		iterator upper_bound(const key_type& __k)
			{return __tree_.upper_bound(__k);}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator upper_bound(const key_type& __k) const
			{return __tree_.upper_bound(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,iterator>::type
		upper_bound(const _K2& __k)       {return __tree_.upper_bound(__k);}
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,const_iterator>::type
		upper_bound(const _K2& __k) const {return __tree_.upper_bound(__k);}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		std::pair<iterator,iterator> equal_range(const key_type& __k)
			{return __tree_.__equal_range_unique(__k);}
		_LIBCPP_INLINE_VISIBILITY
		std::pair<const_iterator,const_iterator> equal_range(const key_type& __k) const
			{return __tree_.__equal_range_unique(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value, std::pair<iterator,iterator>>::type
		equal_range(const _K2& __k)       {return __tree_.__equal_range_multi(__k);}
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value, std::pair<const_iterator,const_iterator>>::type
		equal_range(const _K2& __k) const {return __tree_.__equal_range_multi(__k);}
	# endif
		friend std::ostream& operator<<(std::ostream& os, const set& set) {
			os << set.__tree_;
			return os;
		}
	};

	# if _LIBCPP_STD_VER >= 17
	template<class _InputIterator,
			class _Compare = std::less<std::__iter_value_type<_InputIterator>>,
			class _Allocator = std::allocator<std::__iter_value_type<_InputIterator>>,
			class = std::enable_if_t<std::__has_input_iterator_category<_InputIterator>::value, void>,
			class = std::enable_if_t<std::__is_allocator<_Allocator>::value, void>,
			class = std::enable_if_t<!std::__is_allocator<_Compare>::value, void>>
	set(_InputIterator, _InputIterator, _Compare = _Compare(), _Allocator = _Allocator())
	-> set<std::__iter_value_type<_InputIterator>, _Compare, _Allocator>;

	template<class _Key, class _Compare = std::less<_Key>,
			class _Allocator = std::allocator<_Key>,
			class = std::enable_if_t<!std::__is_allocator<_Compare>::value, void>,
			class = std::enable_if_t<std::__is_allocator<_Allocator>::value, void>>
	set(std::initializer_list<_Key>, _Compare = _Compare(), _Allocator = _Allocator())
	-> set<_Key, _Compare, _Allocator>;

	template<class _InputIterator, class _Allocator,
			class = std::enable_if_t<std::__has_input_iterator_category<_InputIterator>::value, void>,
			class = std::enable_if_t<std::__is_allocator<_Allocator>::value, void>>
	set(_InputIterator, _InputIterator, _Allocator)
	-> set<std::__iter_value_type<_InputIterator>,
			std::less<std::__iter_value_type<_InputIterator>>, _Allocator>;

	template<class _Key, class _Allocator,
			class = std::enable_if_t<std::__is_allocator<_Allocator>::value, void>>
	set(std::initializer_list<_Key>, _Allocator)
	-> set<_Key, std::less<_Key>, _Allocator>;
	# endif

	# ifndef _LIBCPP_CXX03_LANG

	template <class _Key, class _Compare, class _Allocator>
	set<_Key, _Compare, _Allocator>::set(set&& __s, const allocator_type& __a)
		: __tree_(_VSTD::move(__s.__tree_), __a)
	{
		if (__a != __s.get_allocator())
		{
			const_iterator __e = cend();
			while (!__s.empty())
				insert(__e, _VSTD::move(__s.__tree_.remove(__s.begin())->__value_));
		}
	}

	# endif // _LIBCPP_CXX03_LANG

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator==(const set<_Key, _Compare, _Allocator>& __x,
			const set<_Key, _Compare, _Allocator>& __y)
	{
		return __x.size() == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator< (const set<_Key, _Compare, _Allocator>& __x,
			const set<_Key, _Compare, _Allocator>& __y)
	{
		return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator!=(const set<_Key, _Compare, _Allocator>& __x,
			const set<_Key, _Compare, _Allocator>& __y)
	{
		return !(__x == __y);
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator> (const set<_Key, _Compare, _Allocator>& __x,
			const set<_Key, _Compare, _Allocator>& __y)
	{
		return __y < __x;
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator>=(const set<_Key, _Compare, _Allocator>& __x,
			const set<_Key, _Compare, _Allocator>& __y)
	{
		return !(__x < __y);
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator<=(const set<_Key, _Compare, _Allocator>& __x,
			const set<_Key, _Compare, _Allocator>& __y)
	{
		return !(__y < __x);
	}

	// specialized algorithms:
	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	void
	swap(set<_Key, _Compare, _Allocator>& __x,
		set<_Key, _Compare, _Allocator>& __y)
		_NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
	{
		__x.swap(__y);
	}

	# if _LIBCPP_STD_VER > 17
	template <class _Key, class _Compare, class _Allocator, class _Predicate>
	inline _LIBCPP_INLINE_VISIBILITY
		typename set<_Key, _Compare, _Allocator>::size_type
		erase_if(set<_Key, _Compare, _Allocator>& __c, _Predicate __pred) {
	return _VSTD::__libcpp_erase_if_container(__c, __pred);
	}
	# endif

	template <class _Key, class _Compare = std::less<_Key>,
			class _Allocator = std::allocator<_Key> >
	class _LIBCPP_TEMPLATE_VIS multiset
	{
	public:
		// types:
		typedef _Key                                     key_type;
		typedef key_type                                 value_type;
		typedef std::__type_identity_t<_Compare>         key_compare;
		typedef key_compare                              value_compare;
		typedef std::__type_identity_t<_Allocator>       allocator_type;
		typedef value_type&                              reference;
		typedef const value_type&                        const_reference;

		static_assert((std::is_same<typename allocator_type::value_type, value_type>::value),
					"Allocator::value_type must be same type as value_type");

	private:
		typedef __tree<value_type, value_compare, allocator_type>      __base;
		typedef std::allocator_traits<allocator_type>                  __alloc_traits;

		__base __tree_;

	public:
		typedef typename __base::pointer                pointer;
		typedef typename __base::const_pointer          const_pointer;
		typedef typename __base::size_type              size_type;
		typedef typename __base::difference_type        difference_type;
		typedef typename __base::const_iterator         iterator;
		typedef typename __base::const_iterator         const_iterator;
		typedef _VSTD::reverse_iterator<iterator>       reverse_iterator;
		typedef _VSTD::reverse_iterator<const_iterator> const_reverse_iterator;

	# if _LIBCPP_STD_VER > 14
		typedef std::__set_node_handle<typename __base::__node, allocator_type> node_type;
	# endif

		template <class _Key2, class _Compare2, class _Alloc2>
			friend class _LIBCPP_TEMPLATE_VIS set;
		template <class _Key2, class _Compare2, class _Alloc2>
			friend class _LIBCPP_TEMPLATE_VIS multiset;

		// construct/copy/destroy:
		_LIBCPP_INLINE_VISIBILITY
		multiset()
			_NOEXCEPT_(
				std::is_nothrow_default_constructible<allocator_type>::value &&
				std::is_nothrow_default_constructible<key_compare>::value &&
				std::is_nothrow_copy_constructible<key_compare>::value)
			: __tree_(value_compare()) {}

		_LIBCPP_INLINE_VISIBILITY
		explicit multiset(const value_compare& __comp)
			_NOEXCEPT_(
				std::is_nothrow_default_constructible<allocator_type>::value &&
				std::is_nothrow_copy_constructible<key_compare>::value)
			: __tree_(__comp) {}

		_LIBCPP_INLINE_VISIBILITY
		explicit multiset(const value_compare& __comp, const allocator_type& __a)
			: __tree_(__comp, __a) {}
		template <class _InputIterator>
			_LIBCPP_INLINE_VISIBILITY
			multiset(_InputIterator __f, _InputIterator __l,
					const value_compare& __comp = value_compare())
			: __tree_(__comp)
			{
				insert(__f, __l);
			}

	# if _LIBCPP_STD_VER > 11
			template <class _InputIterator>
			_LIBCPP_INLINE_VISIBILITY
			multiset(_InputIterator __f, _InputIterator __l, const allocator_type& __a)
				: multiset(__f, __l, key_compare(), __a) {}
	# endif

		template <class _InputIterator>
			_LIBCPP_INLINE_VISIBILITY
			multiset(_InputIterator __f, _InputIterator __l,
					const value_compare& __comp, const allocator_type& __a)
			: __tree_(__comp, __a)
			{
				insert(__f, __l);
			}

		_LIBCPP_INLINE_VISIBILITY
		multiset(const multiset& __s)
			: __tree_(__s.__tree_.value_comp(),
			__alloc_traits::select_on_container_copy_construction(__s.__tree_.__alloc()))
			{
				insert(__s.begin(), __s.end());
			}

		_LIBCPP_INLINE_VISIBILITY
		multiset& operator=(const multiset& __s)
			{
				__tree_ = __s.__tree_;
				return *this;
			}

	# ifndef _LIBCPP_CXX03_LANG
		_LIBCPP_INLINE_VISIBILITY
		multiset(multiset&& __s)
			_NOEXCEPT_(std::is_nothrow_move_constructible<__base>::value)
			: __tree_(_VSTD::move(__s.__tree_)) {}

		multiset(multiset&& __s, const allocator_type& __a);
	# endif // _LIBCPP_CXX03_LANG
		_LIBCPP_INLINE_VISIBILITY
		explicit multiset(const allocator_type& __a)
			: __tree_(__a) {}
		_LIBCPP_INLINE_VISIBILITY
		multiset(const multiset& __s, const allocator_type& __a)
			: __tree_(__s.__tree_.value_comp(), __a)
			{
				insert(__s.begin(), __s.end());
			}

	# ifndef _LIBCPP_CXX03_LANG
		_LIBCPP_INLINE_VISIBILITY
		multiset(std::initializer_list<value_type> __il, const value_compare& __comp = value_compare())
			: __tree_(__comp)
			{
				insert(__il.begin(), __il.end());
			}

		_LIBCPP_INLINE_VISIBILITY
		multiset(std::initializer_list<value_type> __il, const value_compare& __comp,
			const allocator_type& __a)
			: __tree_(__comp, __a)
			{
				insert(__il.begin(), __il.end());
			}

	# if _LIBCPP_STD_VER > 11
		_LIBCPP_INLINE_VISIBILITY
		multiset(std::initializer_list<value_type> __il, const allocator_type& __a)
			: multiset(__il, key_compare(), __a) {}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		multiset& operator=(std::initializer_list<value_type> __il)
			{
				__tree_.__assign_multi(__il.begin(), __il.end());
				return *this;
			}

		_LIBCPP_INLINE_VISIBILITY
		multiset& operator=(multiset&& __s)
			_NOEXCEPT_(std::is_nothrow_move_assignable<__base>::value)
			{
				__tree_ = _VSTD::move(__s.__tree_);
				return *this;
			}
	# endif // _LIBCPP_CXX03_LANG

		_LIBCPP_INLINE_VISIBILITY
		~multiset() {
			static_assert(sizeof(__diagnose_non_const_comparator<_Key, _Compare>()), "");
		}

		_LIBCPP_INLINE_VISIBILITY
			iterator begin() _NOEXCEPT       {return __tree_.begin();}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator begin() const _NOEXCEPT {return __tree_.begin();}
		_LIBCPP_INLINE_VISIBILITY
			iterator end() _NOEXCEPT         {return __tree_.end();}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator end()   const _NOEXCEPT {return __tree_.end();}

		_LIBCPP_INLINE_VISIBILITY
			reverse_iterator rbegin() _NOEXCEPT
				{return reverse_iterator(end());}
		_LIBCPP_INLINE_VISIBILITY
		const_reverse_iterator rbegin() const _NOEXCEPT
			{return const_reverse_iterator(end());}
		_LIBCPP_INLINE_VISIBILITY
			reverse_iterator rend() _NOEXCEPT
				{return       reverse_iterator(begin());}
		_LIBCPP_INLINE_VISIBILITY
		const_reverse_iterator rend() const _NOEXCEPT
			{return const_reverse_iterator(begin());}

		_LIBCPP_INLINE_VISIBILITY
		const_iterator cbegin()  const _NOEXCEPT {return begin();}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator cend() const _NOEXCEPT {return end();}
		_LIBCPP_INLINE_VISIBILITY
		const_reverse_iterator crbegin() const _NOEXCEPT {return rbegin();}
		_LIBCPP_INLINE_VISIBILITY
		const_reverse_iterator crend() const _NOEXCEPT {return rend();}

		_LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY
		bool empty() const _NOEXCEPT {return __tree_.size() == 0;}
		_LIBCPP_INLINE_VISIBILITY
		size_type size() const _NOEXCEPT {return __tree_.size();}
		_LIBCPP_INLINE_VISIBILITY
		size_type max_size() const _NOEXCEPT {return __tree_.max_size();}

		// modifiers:
	# ifndef _LIBCPP_CXX03_LANG
		template <class... _Args>
			_LIBCPP_INLINE_VISIBILITY
			iterator emplace(_Args&&... __args)
				{return __tree_.__emplace_multi(_VSTD::forward<_Args>(__args)...);}
		template <class... _Args>
			_LIBCPP_INLINE_VISIBILITY
			iterator emplace_hint(const_iterator __p, _Args&&... __args)
				{return __tree_.__emplace_hint_multi(__p, _VSTD::forward<_Args>(__args)...);}
	# endif // _LIBCPP_CXX03_LANG

		_LIBCPP_INLINE_VISIBILITY
		iterator insert(const value_type& __v)
			{return __tree_.__insert_multi(__v);}
		_LIBCPP_INLINE_VISIBILITY
		iterator insert(const_iterator __p, const value_type& __v)
			{return __tree_.__insert_multi(__p, __v);}

		template <class _InputIterator>
			_LIBCPP_INLINE_VISIBILITY
			void insert(_InputIterator __f, _InputIterator __l)
			{
				for (const_iterator __e = cend(); __f != __l; ++__f)
					__tree_.__insert_multi(__e, *__f);
			}

	# ifndef _LIBCPP_CXX03_LANG
		_LIBCPP_INLINE_VISIBILITY
		iterator insert(value_type&& __v)
			{return __tree_.__insert_multi(_VSTD::move(__v));}

		_LIBCPP_INLINE_VISIBILITY
		iterator insert(const_iterator __p, value_type&& __v)
			{return __tree_.__insert_multi(__p, _VSTD::move(__v));}

		_LIBCPP_INLINE_VISIBILITY
		void insert(std::initializer_list<value_type> __il)
			{insert(__il.begin(), __il.end());}
	# endif // _LIBCPP_CXX03_LANG

		_LIBCPP_INLINE_VISIBILITY
		iterator  erase(const_iterator __p) {return __tree_.erase(__p);}
		_LIBCPP_INLINE_VISIBILITY
		size_type erase(const key_type& __k) {return __tree_.__erase_multi(__k);}
		_LIBCPP_INLINE_VISIBILITY
		iterator  erase(const_iterator __f, const_iterator __l)
			{return __tree_.erase(__f, __l);}
		_LIBCPP_INLINE_VISIBILITY
		void clear() _NOEXCEPT {__tree_.clear();}

	# if _LIBCPP_STD_VER > 14
		_LIBCPP_INLINE_VISIBILITY
		iterator insert(node_type&& __nh)
		{
			_LIBCPP_ASSERT(__nh.empty() || __nh.get_allocator() == get_allocator(),
				"node_type with incompatible allocator passed to multiset::insert()");
			return __tree_.template __node_handle_insert_multi<node_type>(
				_VSTD::move(__nh));
		}
		_LIBCPP_INLINE_VISIBILITY
		iterator insert(const_iterator __hint, node_type&& __nh)
		{
			_LIBCPP_ASSERT(__nh.empty() || __nh.get_allocator() == get_allocator(),
				"node_type with incompatible allocator passed to multiset::insert()");
			return __tree_.template __node_handle_insert_multi<node_type>(
				__hint, _VSTD::move(__nh));
		}
		_LIBCPP_INLINE_VISIBILITY
		node_type extract(key_type const& __key)
		{
			return __tree_.template __node_handle_extract<node_type>(__key);
		}
		_LIBCPP_INLINE_VISIBILITY
		node_type extract(const_iterator __it)
		{
			return __tree_.template __node_handle_extract<node_type>(__it);
		}
		template <class _Compare2>
		_LIBCPP_INLINE_VISIBILITY
		void merge(multiset<key_type, _Compare2, allocator_type>& __source)
		{
			_LIBCPP_ASSERT(__source.get_allocator() == get_allocator(),
						"merging container with incompatible allocator");
			__tree_.__node_handle_merge_multi(__source.__tree_);
		}
		template <class _Compare2>
		_LIBCPP_INLINE_VISIBILITY
		void merge(multiset<key_type, _Compare2, allocator_type>&& __source)
		{
			_LIBCPP_ASSERT(__source.get_allocator() == get_allocator(),
						"merging container with incompatible allocator");
			__tree_.__node_handle_merge_multi(__source.__tree_);
		}
		template <class _Compare2>
		_LIBCPP_INLINE_VISIBILITY
		void merge(set<key_type, _Compare2, allocator_type>& __source)
		{
			_LIBCPP_ASSERT(__source.get_allocator() == get_allocator(),
						"merging container with incompatible allocator");
			__tree_.__node_handle_merge_multi(__source.__tree_);
		}
		template <class _Compare2>
		_LIBCPP_INLINE_VISIBILITY
		void merge(set<key_type, _Compare2, allocator_type>&& __source)
		{
			_LIBCPP_ASSERT(__source.get_allocator() == get_allocator(),
						"merging container with incompatible allocator");
			__tree_.__node_handle_merge_multi(__source.__tree_);
		}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		void swap(multiset& __s)
			_NOEXCEPT_(std::__is_nothrow_swappable<__base>::value)
			{__tree_.swap(__s.__tree_);}

		_LIBCPP_INLINE_VISIBILITY
		allocator_type get_allocator() const _NOEXCEPT {return __tree_.__alloc();}
		_LIBCPP_INLINE_VISIBILITY
		key_compare    key_comp()      const {return __tree_.value_comp();}
		_LIBCPP_INLINE_VISIBILITY
		value_compare  value_comp()    const {return __tree_.value_comp();}

		// set operations:
		_LIBCPP_INLINE_VISIBILITY
		iterator find(const key_type& __k)             {return __tree_.find(__k);}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator find(const key_type& __k) const {return __tree_.find(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,iterator>::type
		find(const _K2& __k)                           {return __tree_.find(__k);}
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,const_iterator>::type
		find(const _K2& __k) const                     {return __tree_.find(__k);}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		size_type      count(const key_type& __k) const
			{return __tree_.__count_multi(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,size_type>::type
		count(const _K2& __k) const            {return __tree_.__count_multi(__k);}
	# endif

	# if _LIBCPP_STD_VER > 17
		_LIBCPP_INLINE_VISIBILITY
		bool contains(const key_type& __k) const {return find(__k) != end();}
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value, bool>::type
		contains(const _K2& __k) const { return find(__k) != end(); }
	# endif // _LIBCPP_STD_VER > 17

		_LIBCPP_INLINE_VISIBILITY
		iterator lower_bound(const key_type& __k)
			{return __tree_.lower_bound(__k);}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator lower_bound(const key_type& __k) const
				{return __tree_.lower_bound(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,iterator>::type
		lower_bound(const _K2& __k)       {return __tree_.lower_bound(__k);}

		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,const_iterator>::type
		lower_bound(const _K2& __k) const {return __tree_.lower_bound(__k);}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		iterator upper_bound(const key_type& __k)
				{return __tree_.upper_bound(__k);}
		_LIBCPP_INLINE_VISIBILITY
		const_iterator upper_bound(const key_type& __k) const
				{return __tree_.upper_bound(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,iterator>::type
		upper_bound(const _K2& __k)       {return __tree_.upper_bound(__k);}
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value,const_iterator>::type
		upper_bound(const _K2& __k) const {return __tree_.upper_bound(__k);}
	# endif

		_LIBCPP_INLINE_VISIBILITY
		std::pair<iterator,iterator>             equal_range(const key_type& __k)
				{return __tree_.__equal_range_multi(__k);}
		_LIBCPP_INLINE_VISIBILITY
		std::pair<const_iterator,const_iterator> equal_range(const key_type& __k) const
				{return __tree_.__equal_range_multi(__k);}
	# if _LIBCPP_STD_VER > 11
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value, std::pair<iterator,iterator>>::type
		equal_range(const _K2& __k)       {return __tree_.__equal_range_multi(__k);}
		template <typename _K2>
		_LIBCPP_INLINE_VISIBILITY
		typename std::enable_if<std::__is_transparent<_Compare, _K2>::value, std::pair<const_iterator,const_iterator>>::type
		equal_range(const _K2& __k) const {return __tree_.__equal_range_multi(__k);}
	# endif
	};

	# if _LIBCPP_STD_VER >= 17
	template<class _InputIterator,
			class _Compare = std::less<std::__iter_value_type<_InputIterator>>,
			class _Allocator = std::allocator<std::__iter_value_type<_InputIterator>>,
			class = std::enable_if_t<std::__has_input_iterator_category<_InputIterator>::value, void>,
			class = std::enable_if_t<std::__is_allocator<_Allocator>::value, void>,
			class = std::enable_if_t<!std::__is_allocator<_Compare>::value, void>>
	multiset(_InputIterator, _InputIterator, _Compare = _Compare(), _Allocator = _Allocator())
	-> multiset<std::__iter_value_type<_InputIterator>, _Compare, _Allocator>;

	template<class _Key, class _Compare = std::less<_Key>,
			class _Allocator = std::allocator<_Key>,
			class = std::enable_if_t<std::__is_allocator<_Allocator>::value, void>,
			class = std::enable_if_t<!std::__is_allocator<_Compare>::value, void>>
	multiset(std::initializer_list<_Key>, _Compare = _Compare(), _Allocator = _Allocator())
	-> multiset<_Key, _Compare, _Allocator>;

	template<class _InputIterator, class _Allocator,
			class = std::enable_if_t<std::__has_input_iterator_category<_InputIterator>::value, void>,
			class = std::enable_if_t<std::__is_allocator<_Allocator>::value, void>>
	multiset(_InputIterator, _InputIterator, _Allocator)
	-> multiset<std::__iter_value_type<_InputIterator>,
			std::less<std::__iter_value_type<_InputIterator>>, _Allocator>;

	template<class _Key, class _Allocator,
			class = std::enable_if_t<std::__has_input_iterator_category<_Allocator>::value, void>>
	multiset(std::initializer_list<_Key>, _Allocator)
	-> multiset<_Key, std::less<_Key>, _Allocator>;
	# endif

	# ifndef _LIBCPP_CXX03_LANG

	template <class _Key, class _Compare, class _Allocator>
	multiset<_Key, _Compare, _Allocator>::multiset(multiset&& __s, const allocator_type& __a)
		: __tree_(_VSTD::move(__s.__tree_), __a)
	{
		if (__a != __s.get_allocator())
		{
			const_iterator __e = cend();
			while (!__s.empty())
				insert(__e, _VSTD::move(__s.__tree_.remove(__s.begin())->__value_));
		}
	}

	# endif // _LIBCPP_CXX03_LANG

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator==(const multiset<_Key, _Compare, _Allocator>& __x,
			const multiset<_Key, _Compare, _Allocator>& __y)
	{
		return __x.size() == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator< (const multiset<_Key, _Compare, _Allocator>& __x,
			const multiset<_Key, _Compare, _Allocator>& __y)
	{
		return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator!=(const multiset<_Key, _Compare, _Allocator>& __x,
			const multiset<_Key, _Compare, _Allocator>& __y)
	{
		return !(__x == __y);
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator> (const multiset<_Key, _Compare, _Allocator>& __x,
			const multiset<_Key, _Compare, _Allocator>& __y)
	{
		return __y < __x;
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator>=(const multiset<_Key, _Compare, _Allocator>& __x,
			const multiset<_Key, _Compare, _Allocator>& __y)
	{
		return !(__x < __y);
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	bool
	operator<=(const multiset<_Key, _Compare, _Allocator>& __x,
			const multiset<_Key, _Compare, _Allocator>& __y)
	{
		return !(__y < __x);
	}

	template <class _Key, class _Compare, class _Allocator>
	inline _LIBCPP_INLINE_VISIBILITY
	void
	swap(multiset<_Key, _Compare, _Allocator>& __x,
		multiset<_Key, _Compare, _Allocator>& __y)
		_NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
	{
		__x.swap(__y);
	}

	# if _LIBCPP_STD_VER > 17
	template <class _Key, class _Compare, class _Allocator, class _Predicate>
	inline _LIBCPP_INLINE_VISIBILITY
		typename multiset<_Key, _Compare, _Allocator>::size_type
		erase_if(multiset<_Key, _Compare, _Allocator>& __c, _Predicate __pred) {
	return _VSTD::__libcpp_erase_if_container(__c, __pred);
	}
	# endif
}

_LIBCPP_POP_MACROS

# if !defined(_LIBCPP_REMOVE_TRANSITIVE_INCLUDES) && _LIBCPP_STD_VER <= 20
#  include <concepts>
#  include <cstdlib>
#  include <functional>
#  include <iterator>
#  include <stdexcept>
#  include <type_traits>
# endif

#endif // _LIBCPP_SET
