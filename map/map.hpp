#pragma once
#include "./pair.hpp"
#include "./RBTree.hpp"

namespace ft {

	template<
			class Key,
			class T,
			class Compare = std::less<Key>,
			class Allocator = std::allocator<std::pair<const Key, T>>
			>
	class map {
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename allocator_type::difference_type difference_type;
			typedef typename allocator_type::size_type size_type;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
			friend class map;
			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator()(const value_type& x, const value_type& y) const {
					return comp(x.first, y.first);
				}
		};
		private:	
			typedef ft::RBTree<value_type, value_compare, allocator_type> rep_type;
			rep_type t;

		
		public:
			// constructors
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : t(comp, alloc) {}
			// template <class InputIterator>
			// map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : t(comp, alloc) {
			// 	t.insert_unique(first, last);
			// }
			// map(const map& x) : t(x.t) {}

		// {	// iterators
		// 	typedef typename rep_type::iterator iterator;
		// 	typedef typename rep_type::const_iterator const_iterator;
		// 	iterator begin() { return t.begin(); }
		// 	iterator end() { return t.end(); }
		// 	const_iterator begin() const { return t.begin(); }
		// 	const_iterator end() const { return t.end(); }
		// 	// reverse_iterator rbegin() { return t.rbegin(); }
		// 	// reverse_iterator rend() { return t.rend(); }
		// 	// const_reverse_iterator rbegin() const { return t.rbegin(); }
		// 	// const_reverse_iterator rend() const { return t.rend(); }

		// 	// capacity
		// 	bool empty() const { return t.empty(); }
		// 	size_type size() const { return t.size(); }
		// 	size_type max_size() const { return t.max_size(); }

		// 	// element access
		// 	mapped_type& operator[](const key_type& k) {
		// 		return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
		// 	}

		// 	// modifiers
		// 	ft::pair<iterator, bool> insert(const value_type& x) { return t.insert_unique(x); }
		// 	iterator insert(iterator position, const value_type& x) { return t.insert_unique(position, x); }
		// 	template <class InputIterator>
		// 	void insert(InputIterator first, InputIterator last) { t.insert_unique(first, last); }
		// 	void erase(iterator position) { t.erase(position); }
		// 	size_type erase(const key_type& x) { return t.erase(x); }
		// 	void erase(iterator first, iterator last) { t.erase(first, last); }
		// 	void swap(map& x) { t.swap(x.t); }
		// 	void clear() { t.clear(); }

		// 	// observers
		// 	key_compare key_comp() const { return t.key_comp(); }
		// 	value_compare value_comp() const { return t.value_comp(); }

		// 	// operations
		// 	iterator find(const key_type& x) { return t.find(x); }
		// 	const_iterator find(const key_type& x) const { return t.find(x); }
		// 	size_type count(const key_type& x) const { return t.count(x); }
		// 	iterator lower_bound(const key_type& x) { return t.lower_bound(x); }
		// 	const_iterator lower_bound(const key_type& x) const { return t.lower_bound(x); }
		// 	iterator upper_bound(const key_type& x) { return t.upper_bound(x); }
		// 	const_iterator upper_bound(const key_type& x) const { return t.upper_bound(x); }
		// 	ft::pair<iterator, iterator> equal_range(const key_type& x) { return t.equal_range(x); }
		// 	ft::pair<const_iterator, const_iterator> equal_range(const key_type& x) const { return t.equal_range(x); }

		// 	// allocator
		// 	allocator_type get_allocator() const { return t.get_allocator(); }

		// 	// operators
		// 	map& operator=(const map& x) {
		// 		t = x.t;
		// 		return *this;
		// 	}
		// }
			// destructor
			// ~map() {
			// 	t.clear();
			// }		
		
	};
}