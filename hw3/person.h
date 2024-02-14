#pragma once
#include "Date.h"
#include <ostream>
#include <string>
#include <vector>

namespace elections {
	class Person
	{
	private:
		std::string _name;
		int _ID;
		int _birth;
		int _PartyMember[2];     // -1=no, 0-x=member of party x ; 0-y=rep of region y
		int _voteFor;
		int _regionNum;
		
	public:
		Person(int birth=0, int ID = 100000000, const std::string name = " ", int regionNum=-1, int year = 1800);
		~Person();
		Person(const Person& p);
		bool setName(const std::string name);
		bool setID(int ID);
		bool setPartyMember(int PartyMember, int regionRep);
		bool setBirth(int birth);
		bool setRegionNum(int regionNum);
		bool setVoteFor(int voteFor);
		int getID() const { return _ID; }
		const int* getPartyMember() const { return _PartyMember; }
		const int& getBirth() const { return _birth; }
		const std::string getName() const { return _name; }
		int getVoteFor() const { return _voteFor; }
		int getRegionNum() const { return _regionNum; }

		void printBirth()const;    //this function print the birth year
		Person& operator=(const Person& p);
		bool operator==(const Person& p);
		bool operator!=(const Person& p);
		bool operator<(const Person& p);
		bool operator>(const Person& p);
		friend std::ostream& operator<<(std::ostream& os, const Person& p);
		bool save(std::ostream& out) const;
		bool load(std::istream& in);
		void checkFile(std::istream& file);
		void checkFile(std::ostream& file)const;
	};
}

