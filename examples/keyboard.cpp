#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <climits>
#include "evlib/population.hpp"

//this structure is created for each letter in keyboard
struct letterData{
	int x;
	int y;
	int shortestPath;
	int temp;

	letterData(int X, int Y, int sp){
		x = X;
		y = Y;
		shortestPath = sp;
	}
};

using letterTab = std::unordered_map<int, std::vector<letterData>>;
static std::string msg = "this test messege is used for testing purpose it could be anythin quick brown fox jumps over the lazy dog";


class Keyboard{
public:
	std::string s;
	static const int size = 48;
	static constexpr std::string_view alphabet = "abcdefghijklmnopqrstuvwxyz ";
	Keyboard() : Keyboard(""){}
	Keyboard(std::string S){
		s = S;
	}
	Keyboard(std::mt19937 &rng){
		//std::uniform_int_distribution<std::mt19937::result_type> randChar(0, alphabet.size()-1);
		//Getting even correct keyboard took too long
		s = "    abc def ghi jkl mno pqrs     tuv     wxyz   ";
	}
};

//Message must be writable, else fitness is 0
bool checkGene(const Keyboard &g){
	for(auto c : msg){
		if(g.s.find(c) == std::string::npos){
			return false;
		}
	}
	return true;
}

int write(const Keyboard &g){
	if(!checkGene(g)){
		return INT_MIN;
	}
	letterTab tb;
	for(int y = 0; y < 4; ++y){
		for(int x = 0; x < 12; ++x){
			char c = g.s[x + 12*y];
			if(!tb.contains(c)){
				tb[c] = std::vector<letterData>();
			}
			tb[c].push_back(letterData(x, y, -1));
		}
	}
	
	for(auto &letter : tb[msg[0]]){
		letter.shortestPath = letter.y+(letter.x/3)+letter.x%4;
	}

	for(long unsigned int i = 0; i < msg.size(); ++i){
		char startFrom = msg[i];
		char searchFor = msg[i+1];
		for(auto &letter : tb[searchFor]){
			letter.temp = INT_MAX;	
		}
		//for each letter in message find distance from each coresponding letter on keyboard to following letters on keyboard
		for(auto &thisLetter : tb[startFrom]){
			for(auto &nextLetter : tb[searchFor]){
				int dist = std::abs(thisLetter.y - nextLetter.y) + std::abs(thisLetter.x/4-nextLetter.x/4) + nextLetter.x%4;
				int totalPath = thisLetter.shortestPath + dist + 1;
				if(totalPath < nextLetter.temp){
					nextLetter.temp = totalPath;
				}	
			}
		}	
		for(auto &letter : tb[searchFor]){
			letter.shortestPath = letter.temp;
		}
	}
	// then choose ending letter on keyboard as the one with the shortest path
	int min = INT_MAX;
	for(auto &l : tb[msg[msg.size()-1]]){
		if (l.shortestPath < min){
			min = l.shortestPath;
		}
	}
	//returns -min, because Im trying to minimalize this function
	return -min;
}



std::ostream& operator << (std::ostream &stream, const Keyboard &g){	
	return stream << g.s;
}


void mutate(Keyboard &g, float mutationRate, std::mt19937 &rng){
	std::uniform_int_distribution<std::mt19937::result_type> randomChar(0,g.alphabet.size()-1); 
	std::uniform_real_distribution<> randomFloat(0,1); 
	for(int i = 0; i < g.size; ++i){
		if (randomFloat(rng) < mutationRate){
			g.s[i] = g.alphabet[randomChar(rng)];	
		}
	}
}

Keyboard breed(const Agent<Keyboard> &a, const Agent<Keyboard> &b, std::mt19937 &rng){
	std::uniform_int_distribution<std::mt19937::result_type> randomBool(0,1); 
	std::string newKeyboard;
	for(int i = 0; i < a.g.size; ++i){
		newKeyboard += randomBool(rng) ? a.g.s[i] : b.g.s[i];
	}
	Keyboard g(newKeyboard);
	return g;
}


int main(){
	std::random_device dev;
    std::mt19937 rng(dev());

   	Population<Keyboard> p(rng, 1000);
   	for(int i = 0; i < 1000; i++){
   		if (i % 10 == 0){
   			std::cout << i/10 << "%  Best Agent: " << p.getBest() << std::endl;
   		}
   		generation(p, &write);
   	}

   	std::cout << p.getBest() << std::endl;
	p.print(std::cout);
}


