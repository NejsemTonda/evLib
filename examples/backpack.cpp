#include "evlib/agent.hpp"
#include "evlib/population.hpp"
#include <iostream>

class Inventory{
public:
	static const int size = 50;
	std::vector<int> items;
	Inventory() : Inventory(std::vector<int> ()){}
	Inventory(std::vector<int> Items){
		items = Items;
	}
	Inventory(std::mt19937 &rng){
   		for(int x = 0; x < size; ++x){
			// Starts with epmty invetory. Getting anything that was bellow limit took too long
   			items.push_back(0);
   		}
	}
};

std::ostream& operator << (std::ostream &stream, const Inventory &g){	
	std::string s = "";
	for(int x : g.items){
		s += x ? "0" : "1";
	}
	return stream << s;
}

//This struct is just named tuple
struct Item{
	int value;
	int weight;
	Item(int v, int w){
		value = v;
		weight = w;
	}
};

int sum(const Inventory &g){
	//All possible items
	const std::vector<Item> backpack {Item(14, 131),Item(40, 58),Item(16, 3),Item(31, 129),Item(39, 18),Item(48, 116),Item(8, 238),Item(19, 133),Item(42, 123),Item(37, 77),Item(45, 96),Item(49, 114),Item(43, 111),Item(3, 70),Item(33, 89),Item(3, 136),Item(36, 69),Item(39, 144),Item(41, 3),Item(29, 28),Item(34, 111),Item(28, 41),Item(46, 42),Item(4, 103),Item(9, 71),Item(10, 33),Item(23, 150),Item(23, 101),Item(44, 151),Item(15, 15),Item(16, 109),Item(3, 149),Item(3, 107),Item(25, 81),Item(50, 129),Item(26, 177),Item(8, 102),Item(49, 130),Item(7, 116),Item(1, 74),Item(27, 60),Item(5, 39),Item(50, 73),Item(13, 106),Item(10, 27),Item(12, 144),Item(38, 233),Item(30, 95),Item(13, 96),Item(10, 100)};
	const int maxWeight = 1000;
	int totalWeight = 0;
	int value = 0;
	for(int i = 0; i < g.size; ++i){
		if(g.items[i]){
			value += backpack[i].value;
			totalWeight += backpack[i].weight;
			if (totalWeight > maxWeight) return 0;
		}
	}
	return value;
}

void mutate(Inventory &g, float mutationRate, std::mt19937 &rng){
	std::uniform_int_distribution<std::mt19937::result_type> randInt(0,1); 
	std::uniform_real_distribution<> randomFloat(0,1); 
	for(int i = 0; i < g.size; ++i){
		if (randomFloat(rng) < mutationRate){
			g.items[i] = randInt(rng);	
		}
	}
}

Inventory breed(const Agent<Inventory> &a, const Agent<Inventory> &b, std::mt19937 &rng){
	std::uniform_int_distribution<std::mt19937::result_type> randomBool(0,1); 
	std::vector<int> newInventory;
	for(int i = 0; i < a.g.size; ++i){
		newInventory.push_back(randomBool(rng) ? a.g.items[i] : b.g.items[i]);
	}
	Inventory g(newInventory);
	return g;
}



int main(){
  	std::random_device dev;
    std::mt19937 rng(dev());

	Population<Inventory> p(rng, 1000);
	for(int x = 0; x < 100; ++x){
		generation(p, &sum);
	}
	p.print(std::cout);
	std::cout << p.getBest() << std::endl;
}


