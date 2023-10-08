#ifndef POPULATION
#define POPULATION
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include "agent.hpp"


template<typename Genome>
class Population{
	Agent<Genome> bestAgent;
	std::vector<Agent<Genome>> agents;
	int populationSize;
	std::mt19937 rng; 
public:
	Population(std::mt19937 &generator, int ps = 1000){
		populationSize = ps;
		rng = generator;
   		for(int i = 0; i < populationSize; ++i){
			Genome g(rng);
   			Agent<Genome> a(g);
   			insertToPopulation(a);
		}
		bestAgent = agents[0];
	}

	Agent<Genome> getBest(){
		return bestAgent;
	}
	void insertToPopulation(Agent<Genome> a){
		agents.push_back(a);
	}
	
	//evaluates all non evaluated agents and checks if there wasnt agent better then best so far
	void evaluate(int (*func)(const Genome &g)){
		for (auto &a : agents){
			if (!a.evaluated){
				a.fitness = func(a.g);
				a.evaluated = true;
			}
		}
		//at first best agent is not evaluated so it was impossible to compare it to anything
		Agent best = *std::max_element(agents.begin(), agents.end());
		if (!bestAgent.evaluated){
			bestAgent.fitness = func(bestAgent.g); 
			bestAgent.evaluated = true;
		}
		if (bestAgent < best){
			bestAgent.g = best.g;
			bestAgent.fitness = best.fitness;
		}
	}
	
	//Tournament selection - gets k agents randomly from this->agents and select best one
	//Agents can be in parents more then once 
	std::vector<Agent<Genome>> makeParents(int tournamentSize){
		std::vector<Agent<Genome>> parents;
		std::uniform_int_distribution<std::size_t> randAgent(0, populationSize-1);
		for(int x = 0; x < populationSize; ++x){
			std::vector<Agent<Genome>> tournament;
			for(int k = 0; k < tournamentSize; ++k){
				tournament.push_back(agents[randAgent(rng)]);
			}
			parents.push_back(*std::max_element(tournament.begin(), tournament.end()));
		}
		return parents;
	}

	//For whole population it gets pair of agents and breed them together
	//Mutations are handled here
	void populate(std::vector<Agent<Genome>> &parents, float mutationRate){
		std::vector<Agent<Genome>> newPopulation;
		for(int i = 0; i < populationSize/2; ++i){
			Agent<Genome> parent1 = parents[2*i];		
			Agent<Genome> parent2 = parents[2*i+1];		
			Agent<Genome> child1 = Agent(breed(parent1, parent2, rng));
			Agent<Genome> child2 = Agent(breed(parent2, parent1, rng));
			mutate(child1.g, mutationRate, rng);
			mutate(child2.g, mutationRate, rng);
			newPopulation.push_back(child1);
			newPopulation.push_back(child2);
		}
		agents = newPopulation;
	}

	void print(std::ostream &o){
		o << "--- Population ---\n";
		for(auto a : agents){
			o << a << "\n";
		}
		o << "--------------------";
		o << std::endl;
	}
};

template<typename Genome>
void generation(Population<Genome> &p, int (*func)(const Genome &g), float mutationRate = 0.01){
	p.evaluate(func);
	std::vector<Agent<Genome>> parents = p.makeParents(2);
	p.populate(parents, mutationRate);
	p.evaluate(func);
}

#endif 
