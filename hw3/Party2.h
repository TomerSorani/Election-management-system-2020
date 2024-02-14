#pragma once
#include"region.h"
#include "DynamicArray.h"
#include <vector>
#include <string>
namespace elections
{
	class Party
	{
	private:
		std::string _name;
		Person* _candidate;
		DynamicArray<Person*> _repArr;

	public:
		Party(Person* per = nullptr, const std::string name = " ");
		Party(const Party& other);
		~Party();
		int getLogSize()const { return _repArr.size(); }
		int getPhiSize()const { return _repArr.capacity(); }
		Person* getCandidate() const { return _candidate; }
		const std::string getName() const { return _name; }
		bool setName(const std::string name);
		bool setCandidate(Person* per);

		Party& operator=(const Party& p);

		//this function add new representetive to representetive array in a sorted way
		void addRep(Person* rep, bool load);

		//this function print the representetives in the party by name
		void printReps()const;

		//this function print the representetives acording to the vote percent of the party in the specific region
		int printChosenReps(int regionNum, bool flag, int maxReps);

		//this function return the chosen reps in the region
		std::vector<Person*> getReps(int numOfReps, int regionNum, int& size);

		friend std::ostream& operator<<(std::ostream& os, const Party& p);
		bool operator==(const Party& p);
		bool operator!=(const Party& p);
		bool operator<(const Party& p);
		bool operator>(const Party& p);

		bool save(std::ostream& out) const;
		bool load(std::istream& in);
		void checkFile(std::istream& file);
		void checkFile(std::ostream& file)const;
	};
}