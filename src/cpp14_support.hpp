#ifndef cpp14_support
#define cpp14_support

namespace std{
	template< class T, class U >
	constexpr bool is_same_v = is_same<T, U>::value;
} // namespace std

#endif