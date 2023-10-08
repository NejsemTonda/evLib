#include "evlib/population.hpp"
#include <iostream>

class YouDataStructure{
	YouDataStructure() : YouDataStructure(std::vector<int> ()){}
	YouDataStructure(std::mt19937 &rng){
   		}
	}
};

std::ostream& operator << (std::ostream &stream, const YouDataStructure &g){	
	//Here implement how should your dataStructure be printed
}

int fitness(const YouDataStructure &g){
	//Library allways maximalize this function
}

void mutate(YouDataStructure &g, float mutationRate, std::mt19937 &rng){
	//Here implement mutation of your dataStructure
}

YouDataStructure breed(const Agent<YouDataStructure> &a, const Agent<YouDataStructure> &b, std::mt19937 &rng){
	//Here implement how two Agent should breed (must return new dataStructur)
	YouDataStructure d();
	return d;
}



int main(){
  	std::random_device dev;
    std::mt19937 rng(dev());

	Population<YouDataStructure> p(rng);
	generation(p, &fitness);
	p.print(std::cout);
}


