#ifndef REFLECTION_H_
#define REFLECTION_H_

#include <array>
#include <string_view>


#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, ...)																	\
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)															\
  macro(a1)																						\
  __VA_OPT__(, FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define STRINGIFY(ARG) #ARG

#define CLASS_INFO(CLASS_NAME, ...)																\
	CLASS_NAME_DEF(CLASS_NAME)																	\
	__VA_OPT__(EXPOSE_MEMBERS(CLASS_NAME, __VA_ARGS__))											\
	static_assert(true, "")

#define CLASS_NAME_DEF(CLASS_NAME)																\
	inline static constexpr auto Name()															\
	{																							\
		return #CLASS_NAME;																		\
	}										
#define EXPOSE_MEMBERS(CLASS_NAME, MEMBER_COUNT, ...)											\
	inline auto Members()																		\
	{																							\
		return std::tie(__VA_ARGS__);															\
	}																							\
																								\
	inline auto Members() const																	\
	{																							\
		return std::tie(__VA_ARGS__);															\
	}																							\
																								\
	inline static const auto Names()															\
	{																							\
		/*static_assert(MEMBER_COUNT == std::tuple_size<CLASS_NAME{}.Members()>);*/				\
		return std::array<std::string_view, MEMBER_COUNT>{FOR_EACH(STRINGIFY, __VA_ARGS__)};	\
	}																							\
																								\
	template<typename T>																		\
	void Apply(T&& _function)																	\
	{																							\
		auto members = Members();																\
		std::apply(																				\
			[&_function]<typename... ClassTypes>(ClassTypes&... _args)							\
		{																						\
			((_function(_args)), ...);															\
		}																						\
		, members);																				\
	}																							\

#endif