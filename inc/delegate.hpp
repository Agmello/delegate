#pragma once
#include  <iostream>
#include <vector>
#include <any>
#include <algorithm>

template<class _FunctionType, typename _dependentType>
class delegate {
public:
	void add(std::any ref, _FunctionType func) {

		functionContainer.push_back({ ref,func });
	}
	void remove(std::any ref) {
		void* t1 = &ref;
		void* t2;// = &functionContainer[0].reference;
		int i = 0;
		for (; i < functionContainer.size(); i++) {
			t2 = &functionContainer[i].reference;
			std::cout << "Comparing " << *((int*)t1) << " with " << *((int*)t2) << std::endl;
			if (*((int*)t1) == *((int*)t2))
				break;
		}
		if (i != functionContainer.size())
			functionContainer.erase(functionContainer.begin() + i);
	}
	void remove(_FunctionType func) {
		int i = 0;
		for (; i < functionContainer.size(); i++) {
			if (func == functionContainer[i].function)
				break;
		}
		if (i != functionContainer.size())
			functionContainer.erase(functionContainer.begin() + i);
	}
	void execute(_dependentType value) {
		for (auto const& func : functionContainer) {
			func.function(func.reference, value);
		}
	}

private:
	struct _delegateMembers
	{
		std::any reference;
		_FunctionType function;
	};

	std::vector<_delegateMembers> functionContainer;
};