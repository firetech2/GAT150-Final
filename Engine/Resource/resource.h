#pragma once
#include <string>

namespace tech
{
	class Resource
	{
	public:
		virtual bool Create(std::string name, ...) = 0;

	};
}