#pragma once
#include "List.h"
struct CSS {
	int selNum = 0;
	int attriNum = 0;

	List<char*> selectors;
	List<char*> attributes;
	List<char*> values;
};
