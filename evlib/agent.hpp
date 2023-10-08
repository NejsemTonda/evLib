#ifndef AGENT
#define AGENT
#include <iostream>
#include <string>

template<typename Genome>
struct Agent{
	Genome g;
	int fitness;
	bool evaluated = false;
	inline bool operator < (const Agent<Genome> &other){
		if(!evaluated || !other.evaluated){
			std::cout << "Something went terribly wrong, one of the agents is not evaluated" << std::endl;
		}
		return (fitness < other.fitness);
	}
	Agent(){}
	Agent(Genome newGen){
		g = newGen;
	}
	Agent& copy(const Agent& other){
		this->g = other.g;
	}
};

template<typename Genome>
inline std::ostream& operator << (std::ostream &stream, const Agent<Genome> &a){	
	auto x = a.evaluated ? std::to_string(a.fitness) : "None";
	return stream << "Agent:{" << a.g << "}; fitness:{" << x << "}";
}

#endif
