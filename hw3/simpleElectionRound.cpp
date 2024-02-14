#define _CRT_SECURE_NO_WARNINGS
#include "simpleElectionRound.h"
namespace elections
{
	simpleElectionRound::simpleElectionRound(std::string regionName, int numberOfReps)
	{
		electionRound::addRegion(regionName, numberOfReps, 2);
	}
	simpleElectionRound::simpleElectionRound() {}
	simpleElectionRound::~simpleElectionRound() {}

	void simpleElectionRound::addRegion(const std::string name, int numOfRep, int type)
	{
		std::cout << "ERROR!: this is a simple election round, you can't add regions" << std::endl;
	}
	void simpleElectionRound::addPerson(std::string name, int ID, int birth, int regionNum)
	{
		try {personCheck(ID);}
		catch (std::exception& ex) { std::cout << ex.what() << std::endl; return; }
		Person* pp;
		try { pp = new Person(birth, ID, name, 0, _electionDate.getYear()); }
		catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		_rigionArr[0]->addPerson(pp);
		addRegister(pp);
	}
	void simpleElectionRound::personCheck(int ID)const
	{
		for (int i = 0; i < _registerArr.size(); i++)
		{
			if (ID == _registerArr[i]->getID())
				throw std::invalid_argument("this ID already exist");
		}
	}
	void simpleElectionRound::addRep(int ID, int partyNum, int regionNum)
	{
		Person* rep;
		try { rep = repCheck(ID, partyNum); }
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl; return;
		}
		rep->setPartyMember(partyNum, 0);
		_partyArr[partyNum].addRep(rep, false);
	}
	Person* simpleElectionRound::repCheck(int ID, int partyNum)
	{
		if (partyNum >= _partyArr.size())
			throw std::invalid_argument("wrong party");
		Person* rep = nullptr;
		for (int i = 0; i < _registerArr.size(); i++)
		{
			if (ID == _registerArr[i]->getID())
				rep = _registerArr[i];
		}
		if (rep == nullptr)
			throw std::invalid_argument("person not found");
		else if (rep->getPartyMember()[0] != -1)
			throw std::invalid_argument("the person is already a party member");
		return rep;
	}
	void simpleElectionRound::printRegions()
	{
		std::cout << *(_rigionArr[0]) << std::endl;
	}
	void simpleElectionRound::printCitizents()
	{
		for (int i = 0; i < _registerArr.size(); i++)
			std::cout << *(_registerArr[i]);
	}

}
