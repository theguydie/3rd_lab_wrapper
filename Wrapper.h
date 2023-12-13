#pragma once
#include <stdexcept>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>

template<typename T, typename ...Args>
class Wrapper {
public:
	using Mtype = int(T::*)(Args...);

	Wrapper(T* t, Mtype _method, const std::initializer_list<std::pair<std::string, int>>& args) : classWrap(t), method(_method) {
		for (auto const& v : args) { argNames.push_back(v.first); }
	};
	int executeWrapped(const std::unordered_map<std::string, int>& args) {
		std::vector<int> values;
		for (auto const& name : argNames)
		{
			if (args.find(name) == args.end())
			{
				throw std::runtime_error("invalid argument: " + name);
			}

			values.push_back(args.at(name));
		}
		return executeWrapped(values, std::make_index_sequence<sizeof...(Args)>());
	}
private:
	T* classWrap;
	Mtype method;
	std::vector<std::string> argNames;

	template <std::size_t... S>
	int executeWrapped(const std::vector<int>& values, std::index_sequence<S...>)
	{
		assert(classWrap && method);
		return (classWrap->*method)(values[S]...);
	}
};
