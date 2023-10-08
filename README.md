# Václav Krňák - Knihovna pro evoluční algoritmy
Jednoduchá knihovna na řešení optimalizačních úloh pomocí Genetických algoritmů.  

## Motivace
Hlavní motivací této knihovny je najít co nejoptimálnější řešení úlohy se klávesnicemi T9 na tlačítkových mobilech.  

### Klávesnice
Máme klávesnici o rozměrech 3x4 tlačítek. Na každém tlačítku můžou být až 4 písmenka. Na klasické klávesnici T9 jsou písmenka seřazena abecedně, což nemusí být nejlepší rozmístění pro tlačítka. Mějme tedy nějakou zprávu (v své implementaci jsem použil zprávu "this test messege is used for testing purpose it could be anythin quick brown fox jumps over the lazy dog") a chceme najít rozložení písmenek na této klávesnici takové, že zprávu lze napsat co nejméně kroky.  
Prstem začínáme na pozici (1,1). Co se počítá jako krok:  
* Posunutí prstu (+-(1,0), +-(0,1))
* Stisknutí tlačítka (pokud je na tlačítku "abcd" a my chceme napsat "d", je třeba tlačítku stisknout 4x)
* Počkání na zadání v případě, že chceme napsat dvě písmenka na stejném tlačítku (pokud je na tlačítku "abcd" a my chceme napsat "da", je třeba 4x stisknout, počkat na zadání, 1x stisknout)

Na klávesnici není možné se pohybovat diagonálně nebo modulárně. Písmenka se na klávesnici mohou opakovat

## Uživatelská dokumetace 
Knihovnu je třeba importovat:  
> ```#include "path/to/lib/population.hpp"``` 

Na stejné cestě by se měl nacházet i soubor ```agent.hpp```, pokud tomu tak není, je třeba jej importovat zvlášť  
Uživatel musí implementovat nějakou datovou strukturu, která bude udržovat argumenty pro funkci, jenž chce optimalizovat (Genom agenta):
* ```class Data{}```

Dále jsou potřeba následují funkce:
*  ```int fitness(const Data &g)``` která ```Data``` ohodnotí (f: Data -> Int). Knihovna se tuto funkci snaží optimalizovat
* ```void mutate(Data &g, float mutationRate, std::mt19937 &rng)``` funkce, která na datové struktuře provede mutaci (malou změnu)
* ```Data breed(const Agent<Data> &a, const Agent<Data> &b, std::mt19937 &rng)```, která z dvou struktur vytvořit nějakou její kombinaci.

Pak už lze vytvořit populaci:  
> ```p = population<Data> (rng, ps = 1000);```  

kde rng je náhodný generátor čísel ```std::mt19937``` a ```ps``` velikost populace   
Voláním funkce:  
> ```generation(p, &fitness);```  

Se pak spouští jedna generace evolučního algoritmu   
Pokud navíc uživatel implementuje i ```std::ostream& operator << (std::ostream &stream, const Data &g)```, tak lze celou populaci vytisknout zavoláním ```p.print(std::cout)```  

funkce ```p.getBest()``` vrátí nejlepší dosuď nalezený výsledek

## [Programátorská dokumentace](https://gitlab.mff.cuni.cz/teaching/nprg041/2021-22/bednarek/krnakva/-/blob/master/docs/programDoc.md)

## Výsledek
Přiklad s klávesnicí jsem implementoval v souboru ```examples/keyboard.cpp``` a nechal jsem ho běžet, nejlepší výsledek, co jsem dostal vypadal takto:


_ebd | anll | tyzz  
gdov | ukcl | inhq  
plrl | sedg | _tmb  
um_j | owxv | frch  

Dokázal zprávu napsat v 259 krocích, což je oproti normální klávesnici, která tu samou zprávu napíše v 393 krocích, docela pěkné zlepšení.
