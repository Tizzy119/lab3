// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iterator>
#include <cstdlib>
#include <string>
#include <ctime>

#include <iostream>
#include <stdio.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	srand(time(NULL));

	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	vectorOfSlavs.push_back(slavs);

	for (int i=1; i<n; i++)
			{
				int x=rand() % vectorOfSlavs.size();
				vectorOfSlavs.insert( vectorOfSlavs.begin()+x, slavs+i );
			}

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	vector <Slav *> :: iterator vectoriterator = vectorOfSlavs.begin();

	for (vectoriterator; vectoriterator != vectorOfSlavs.end(); vectoriterator++)
	{
		//Print Slav names
		cout << (*vectoriterator) -> description() << endl;
	}

	//vector <Slav*>::iterator it_vos; 

	//for (it_vos=vectorOfSlavs.begin(); it_vos!=vectorOfSlavs.end(); it_vos++)
		//cout << (*it_vos)->description() << endl;


	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	for (int i=n-1; i>=0; i--)
		{
			setOfSlavs.insert(vectorOfSlavs[i]);
			vectorOfSlavs.pop_back();
		}

	vectorOfSlavs.clear();
	
	REPORT_CONTAINERS;
	printf("## map\n");
	
	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	set <Slav*>::iterator it_sos;
	map <Slav*, Slav*>::iterator it_mos;
	for (it_sos=setOfSlavs.begin(); it_sos!=setOfSlavs.end(); it_sos++)
	{
		mapOfSlavs[*it_sos]=*(it_sos++)+1;
	}

	setOfSlavs.clear();


	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	for(it_mos=mapOfSlavs.begin(); it_mos!=mapOfSlavs.end(); it_mos++)
	{
		cout << (it_mos->first)-> description() << "   " << (it_mos->second)-> description() << endl;
	}

	
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for (int i=0; i<n; i++)
	{
		queueOfSlavs.push(slavs + i);
	}
	
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	while (!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	while(!stackOfSlavs.empty())
	{
		cout<<stackOfSlavs.top()->description() << endl;
		stackOfSlavs.pop();
	}
	cout<<endl;

	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
