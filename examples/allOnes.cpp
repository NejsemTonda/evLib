#include "evlib/population.hpp"
#include <numeric>
#include <iostream>

class Pattern{
public:
	static const int size = 50;
	std::vector<int> ones;
	Pattern() : Pattern(std::vector<int> ()){}
	Pattern(std::vector<int> Ones){
		ones = Ones;
	}
	Pattern(std::mt19937 &rng){
		std::uniform_int_distribution<std::mt19937::result_type> randomBool(0,1); 
   		for(int x = 0; x < size; ++x){
   			ones.push_back(randomBool(rng));
   		}
	}
};

std::ostream& operator << (std::ostream &stream, const Pattern &g){	
	for(int x : g.ones){
		stream << x;
	}
	return stream;
}

int sum(const Pattern &g){
	return std::accumulate(g.ones.begin(), g.ones.end(), 0);;
}

void mutate(Pattern &g, float mutationRate, std::mt19937 &rng){
	std::uniform_int_distribution<std::mt19937::result_type> randInt(0,1); 
	std::uniform_real_distribution<> randomFloat(0,1); 
	for(int i = 0; i < g.size; ++i){
		if (randomFloat(rng) < mutationRate){
			g.ones[i] = randInt(rng);	
		}
	}
}

Pattern breed(const Agent<Pattern> &a, const Agent<Pattern> &b, std::mt19937 &rng){
	std::uniform_int_distribution<std::mt19937::result_type> randomBool(0,1); 
	std::vector<int> newPattern;
	for(int i = 0; i < a.g.size; ++i){
		newPattern.push_back(randomBool(rng) ? a.g.ones[i] : b.g.ones[i]);
	}
	Pattern g(newPattern);
	return g;
}



int main(){
  	std::random_device dev;
    std::mt19937 rng(dev());

	Population<Pattern> p(rng, 1000);
	for(int x = 0; x < 100; ++x){
		generation(p, &sum);
	}
	p.print(std::cout);
	std::cout << p.getBest() << std::endl;
}


