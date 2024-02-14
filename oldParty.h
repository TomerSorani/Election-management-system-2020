#pragma once
#include"region.h"
namespace elections
{
	class Party
	{
	private:
		char* _name;
		int _logSize, _phiSize;
		Person* _candidate;
		Person** _repArr;
		
	public:
		Party(Person* per = nullptr, const char* name = " ");
		Party(const Party& other);
		~Party();
		int getLogSize()const { return _logSize; }
		int getPhiSize()const { return _phiSize; }
		Person* getCandidate() const { return _candidate; }
		const char* getName() const { return _name; }
		bool setName(const char* name);
		bool setCandidate(Person* per);
		bool setLogSize(int logSize);
		bool setPhiSize(int phiSize);

		Party& operator=(const Party& p);

		//this function add new representetive to representetive array in a sorted way
		bool addRep(Person* rep);
		
		//this function print the representetives in the party by name
		void printReps()const;

		//this function print the representetives acording to the vote percent of the party in the specific region
		int printChosenReps(int regionNum, bool flag, int maxReps);

		//this function return the chosen reps in the region
		Person** getReps(int numOfReps, int regionNum, int& size);

		friend std::ostream& operator<<(std::ostream& os, const Party& p);

		bool save(std::ostream& out) const;
		bool load(std::istream& in);
		bool checkFile(std::istream& file);
		bool checkFile(std::ostream& file)const;
	};
}