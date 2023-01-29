#pragma once

namespace ft {
	template <typename KeyType, typename ValueType>
	class pair {
	public:
		typedef KeyType key_type;
		typedef ValueType value_type;

		key_type first;
		value_type second;

		// Default constructor
		pair() : first(), second() {}

		// Copy constructor
		template <typename U, typename V>
		pair(const pair<U, V> &p) : first(p.first), second(p.second) {}

		// Parameterized constructor
		pair(const key_type &k, const value_type &v) : first(k), second(v) {}

		// Assignment operator
		pair &operator=(const pair &p) {
			if (this != &p) {
				first = p.first;
				second = p.second;
			}
			return *this;
		}
	};

	template <typename KeyType, typename ValueType>
	pair<KeyType, ValueType> make_pair(KeyType k, ValueType v) {
		return (pair<KeyType, ValueType>(k, v));
	}

	template <typename KeyType, typename ValueType>
	bool operator==(const pair<KeyType, ValueType> &lhs, const pair<KeyType, ValueType> &rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <typename KeyType, typename ValueType>
	bool operator!=(const pair<KeyType, ValueType> &lhs, const pair<KeyType, ValueType> &rhs) {
		return !(lhs == rhs);
	}

	template <typename KeyType, typename ValueType>
	bool operator<(const pair<KeyType, ValueType> &lhs, const pair<KeyType, ValueType> &rhs) {
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <typename KeyType, typename ValueType>
	bool operator<=(const pair<KeyType, ValueType> &lhs, const pair<KeyType, ValueType> &rhs) {
		return !(rhs < lhs);
	}

	template <typename KeyType, typename ValueType>
	bool operator>(const pair<KeyType, ValueType> &lhs, const pair<KeyType, ValueType> &rhs) {
		return (rhs < lhs);
	}

	template <typename KeyType, typename ValueType>
	bool operator>=(const pair<KeyType, ValueType> &lhs, const pair<KeyType, ValueType> &rhs) {
		return !(lhs < rhs);
	}
};
