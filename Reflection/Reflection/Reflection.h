#ifndef REFLECTION_H_
#define REFLECTION_H_

#include <array>
#include <string_view>

#define CLASS_INFO(CLASS_NAME, ...)													\
	CLASS_NAME_DEF(CLASS_NAME)														\
	__VA_OPT__(EXPOSE_MEMBERS(__VA_ARGS__))											\
	static_assert(true, "")

#define CLASS_NAME_DEF(CLASS_NAME)													\
	inline static constexpr auto Name()												\
	{																				\
		return #CLASS_NAME;															\
	}										

#define STRINGIFY_FOR_EACH(ARG, ...)												\
	, #ARG																			\
	__VA_OPT__(STRINGIFY_FOR_EACH(__VA_ARGS__))

#define STRINGIFY(ARG, ...)															\
	#ARG																			\
	__VA_OPT__(STRINGIFY_FOR_EACH(__VA_ARGS__))

#define EXPOSE_MEMBERS(MEMBER_COUNT, ...)											\
	inline auto Members()															\
	{																				\
		return std::tie(__VA_ARGS__);												\
	}																				\
																					\
	inline auto Members() const														\
	{																				\
		return std::tie(__VA_ARGS__);												\
	}																				\
																					\
	inline static const auto Names()												\
	{																				\
		return std::array<std::string_view, MEMBER_COUNT>{STRINGIFY(__VA_ARGS__)};	\
	}																				\
																					\
	template<typename T>															\
	void Apply(T&& _function)														\
	{																				\
		auto members = Members();													\
		std::apply(																	\
			[&_function]<typename... ClassTypes>(ClassTypes&... _args)				\
		{																			\
			((_function(_args)), ...);												\
		}																			\
		, members);																	\
	}																				\

#endif