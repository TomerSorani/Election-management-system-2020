#pragma once
#include "person.h"
#include <string>

namespace elections {

	class region {
	protected:
		std::string _name;
		int _voteCounter;
		int _numOfRep;
		float _votePercent;
		std::vector<Person*> _personArr;
		std::vector<Person*> _chosenRepsArr;     //result of the election
		
	public:
		region(int numOfRep=1, const std::string name = " ");
		virtual~region();
		region(const region& r);
		const std::string getName() const { return _name; }
		float getVotePercent() const { return _votePercent; }
		int getVoteCounter() const { return _voteCounter; }
		int getLogSize()const { return _personArr.size(); }
		int getPhiSize()const { return _personArr.capacity(); }
		int getNumOfRep() const { return _numOfRep; }
		bool setNumOfRep(int numOfRep);
		bool setName(const std::string name);
		bool setVotePercent(float percent);
		bool setVoteCounter(int num);

		region& operator=(const region& r);

		//this function add 1 to the vote counter or the region
		void addToVoteCounter(int num);

		//this function add person to the person array
		void addPerson(Person* p);

		//this function print all of the persons in the region providing name, ID and birth 
		void printPersons()const;

		//this function get ID and return pointer to the person. nullpter if not found
		Person* findPerson(int ID);

		//this function save the chosen reps
		void updateChosenRepsArr(std::vector<Person*> repsArr, int size);

		friend std::ostream& operator<<(std::ostream& os, const region& r);

		virtual bool operator==(const region& r);
		virtual bool operator!=(const region& r);
		bool operator<(const region& r);
		bool operator>(const region& r);
		
		virtual bool save(std::ostream& out) const;
		virtual bool load(std::istream& in);
		void checkFile(std::istream& file);
		void checkFile(std::ostream& file)const;
	};
}