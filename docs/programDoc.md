## Programátorská dokumentace
Knihovna se skláda s dvou souborů ```population.hpp``` a ```agent.hpp```

### ```agent.hpp```
Tento soubor obsahuje pouze implementaci pro třídu ```Agent```, která slouží jako obalová třída pro datovou strukturu (genom) implementovanou uživatelem. Obsahuje tyto data
* ```Genome g``` Datová struktura od uživatele, touto strukturou je i třída parametrizována
* ```int fitness``` Pokud agent byl už ohodnocený, jeho fitness je uložena zde
* ```bool evaluated``` Pokud byl agent již ohodnocený, tato hodnota je nastavena na ```true```, jinak ```false```

Agenty je možné mezi sebou porovnávat operátorem ```<``` a je pro ně implementovaný operátor ```<<```, který je lze vytisknout

### ```population.hpp```
Třída ```Population``` je hlavní třídou této knihovny, drží si tato data:
* ```std::vector<Agent<Genome>> agents```, který si udržuje všechny agenty v populaci
* ```Agent<Genome> bestAgent```, který si pamatuje agenta s dosuď nelepší nalezenou fitness
* ```int populationSize``` velikost populace, defaultně nastaveno na 1000
* ```std::mt19937 rng``` náhodný generátor čísel, který kostruktor této třídy musí obdržet od uživatele

Třída population má implenetované tyto funkce:
* ```Agent<Genome> getBest()``` vrátí agenta s dosuď nelepší nalezenou fitness
* ```void insertToPopulation(Agent<Genome> a)``` ```Agent a``` vloží do vektoru ```agents```
* ```void evaluate(int (*func)(const Genome &g))``` funkce, která ohodnotí všechny dosuď neohodnocené agenty z ```agents```, a ```bestAgent``` pokud nebyl dosud ohodnocený. Dále pokud je nejlepší agent z této populace lepší než ```bestAgent```, tak je ```bestAgent``` tímto agentem nahrazen
* ```std::vector<Agent<Genome>> makeParents(int tournamentSize)``` Jedná se o prosté implementování turnajové selekce, několik (tournamentSize defaultně 2) agentů je náhodně z populace vybráno a ten nejlepší z nich je vložen do ```std::vector<Agent<Genome>> parents```, tento vektor pak funkce vrací
* ```void populate(std::vector<Agent<Genome>> &parents, float mutationRate)``` z vektoru ```parents``` vždy vybere dva agenty ```a1, a2```, vytvoří dva různé potomky zkřížením ```a1``` s ```a2``` a pak ```a2``` s ```a1``` (funkce ```breed``` od uživatele), oba potomky pak zmutuje (funkce ```mutate``` od uživatele) a výsledné potomky pak vloží do vektoru ```newPopulation``` která tato funkce vrací
* ```void print(std::ostream &o)``` pro každého agenta z populace se zavolá ```o << agent```

Funkce generation ```void generation(Population<Genome> &p, int (*func)(const Genome &g), float mutationRate = 0.01)``` pak jenom tyto funkce zavolá ve vhodném pořadí.
