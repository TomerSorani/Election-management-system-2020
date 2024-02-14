#pragma once
#include "electionRound.h"
namespace elections
{
	class simpleElectionRound :public electionRound
	{
	private:

	public:
		simpleElectionRound(std::string regionName, int numberOfReps);
		simpleElectionRound();
		~simpleElectionRound();

		//this function add new region to the region array
		virtual void addRegion(const std::string name, int numOfRep, int type);

		//this function add new person to the person array in the given region number
		virtual void addPerson(std::string name, int ID, int birth, int regionNum);

		//check the person input
		void personCheck(int ID)const;

		//this function add new representetive to the given party if the input is correct
		void addRep(int ID, int partyNum, int regionNum);

		//check the rep input
		Person* repCheck(int ID, int partyNum);

		//this function print all the regions, providing region's number, name and number of representetives in it
		void printRegions(); //regionNum, regionName, numOfRep

		//this function print all the citizents from the regions
		void printCitizents(); //name, ID, birth, region

		
	};
}
