#pragma once
#include"Party2.h"
#include "comlicatedRegion.h"
#include "resSum.h"

namespace elections {
	class electionRound
	{
	protected:
		Date _electionDate;
		std::vector<region*> _rigionArr;
		std::vector<Person*> _registerArr;
		std::vector<Party> _partyArr;
		resSum* _resSumArr;
		int** _resultMat;
		
	public:
		electionRound();
		virtual~electionRound();
		electionRound(const electionRound& er);

		const Date& getElectionDate()const { return _electionDate; }
		resSum* getResSumArr()const { return _resSumArr; }
		std::vector<region*> getRigionArr()const { return _rigionArr; }
		std::vector<Party> getPartyArr()const { return _partyArr; }
		std::vector<Person*> getRegisterArr()const { return _registerArr; }
		int** getResultMat()const { return _resultMat; }
		int getRegLogSize()const { return _rigionArr.size(); }
		int getRegPhiSize()const { return _rigionArr.capacity(); }
		int getParLogSize()const { return _partyArr.size(); }
		int getParPhiSize()const { return _partyArr.capacity(); }
		int getRegisterLogSize()const { return _registerArr.size(); }
		int getRegisterPhiSize()const { return _registerArr.capacity(); }
		bool setElectionDate(Date electionDate);

		//this function add new region to the region array
		virtual void addRegion(const std::string name, int numOfRep, int type);

		//this function add new person to the person array in the given region number
		virtual void addPerson(std::string name, int ID, int birth, int regionNum);

		//check the person input
		void personCheck(int ID, int regionNum)const;

		//this function add new parrty to the party array if the input is correct
		void addParty(std::string name, int candidateID);

		//check the party input
		Person* partyCheck(int candidateID);

		//this function add new representetive to the given party if the input is correct
		virtual void addRep(int ID, int partyNum, int regionNum);

		//check the rep input
		Person* repCheck(int ID, int partyNum, int regionNum);

		//this function print all the regions, providing region's number, name and number of representetives in it
		virtual void printRegions(); //regionNum, regionName, numOfRep

		//this function print all the citizents from the regions
		virtual void printCitizents(); //name, ID, birth, region

		//this function print all the partie, providing party's number, name, the candidate and the representetives
		void printParty(); //partyNum, name, candidate, reps

		//this function get ID and party number, the function will update the vote counterin the specific region
		//and update the person's intended vote, if the input is correct
		void getVote(int ID, int partyNum);

		//check the vote input
		Person* voteCheck(int ID, int partyNum, int& i);


		//this function prints all the regions names and the number of representetives given by each region
		//and which candidate has beed chosen in the region. also print the number of votes and percent each party got
		//and the winning candidate;
		void printResult();

		//print specified details of a whole region
		void printResultType1(resSum* regResSumArr, int regIndex);

		//print specified details of a divided region
		void printResultType2(resSum* regResSumArr, int regIndex);

		//print the result in a region
		void printData(resSum* regResSumArr, int regIndex);


		//this function add the person to the register list
		void addRegister(Person* p);

		//this function delete the result mat
		void resetResult();

		//this function print the election date
		void printElectionDate()const;

		//this function save the chosen reps in each region
		void saveResults();
		//check if there are existing regions and parties
		void checkRes()const;
		//calculates a matrix which stores all the votes given to the parties in each region
		void calcRes();

		electionRound& operator=(const electionRound& er);

		bool save(std::ostream& out) const;
		bool load(std::istream& in);
		void checkFile(std::istream& file);
		void checkFile(std::ostream& file)const;

		protected:
		void loadPerson(Person* p);
		void loadRep(Person* rep);
		void loadCandidate(int partySize, int registerSize);

		//template method bubble sort
		template <class T>
		void bubbleSort(T* Arr, int size)
		{
			for (int i = 0; i < size - 1; i++)
			{
				for (int j = 0; j < size - i - 1; j++)
				{
					if (Arr[j] < Arr[j + 1])
					{
						T temp = Arr[j];
						Arr[j] = Arr[j + 1];
						Arr[j + 1] = temp;
					}
				}
			}
		}
	};

}