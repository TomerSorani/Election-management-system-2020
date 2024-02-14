#define _CRT_SECURE_NO_WARNINGS
#include "electionRound.h"
namespace elections {

	electionRound::electionRound():_resSumArr(nullptr), _resultMat(nullptr){}

	electionRound::~electionRound()
	{
		for (auto itr = _registerArr.begin(); itr != _registerArr.end(); itr++)
			delete (*itr);
		for (auto itr = _rigionArr.begin(); itr != _rigionArr.end(); itr++)
			delete (*itr);
	}
	electionRound::electionRound(const electionRound& er)
	{
		if (this != &er)
			*this = er;
	}

	void electionRound::addRegion(const std::string name, int numOfRep, int type)
	{
		region* newReg;
		try { newReg = new comReg(numOfRep, name, type); }
		catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			return;
		}
		_rigionArr.push_back(newReg);
	}
	
	void electionRound::addPerson(std::string name, int ID, int birth, int regionNum)
	{
		try { personCheck(ID, regionNum); }
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			return;
		}
		Person* pp;
		try { pp = new Person(birth, ID, name, regionNum, _electionDate.getYear()); }
		catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		catch (std::invalid_argument& ex) { std::cout << ex.what() << std::endl; return; }
		_rigionArr[regionNum]->addPerson(pp);
		addRegister(pp);
	}
	void electionRound::personCheck(int ID, int regionNum)const
	{
		if (_rigionArr.empty() || regionNum >= _rigionArr.size())
			throw std::invalid_argument("region not found");
		for (int i = 0; i < _registerArr.size(); i++)
		{
			if (ID == _registerArr[i]->getID())
				throw std::invalid_argument("this ID already exist");
		}
	}
	
	void electionRound::addParty(std::string name, int candidateID)
	{
		Person* per;
		try { per = partyCheck(candidateID); }
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			return;
		}

		Party newParty(per, name);
		_partyArr.push_back(newParty);
		per->setPartyMember(_partyArr.size() - 1, -1);
	}
	Person* electionRound::partyCheck(int candidateID)
	{
		Person* per = nullptr;
		for (auto itr=_rigionArr.begin(); itr != _rigionArr.end(); itr++)
		{
			per = (*itr)->findPerson(candidateID);
			if (per != nullptr)
				break;
		}
		if (per == nullptr)
			throw std::invalid_argument("person not found");
		if (per->getPartyMember()[0] != -1)
			throw std::invalid_argument("the person is already in a party");
		return per;
	}
	
	void electionRound::addRep(int ID, int partyNum, int regionNum)
	{
		Person* rep;
		try { rep = repCheck(ID, partyNum, regionNum); }
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			return;
		}
		try {_partyArr[partyNum].addRep(rep, false);}
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			return;
		}
		rep->setPartyMember(partyNum, regionNum);
	}
	Person* electionRound::repCheck(int ID, int partyNum, int regionNum)
	{
		if (regionNum >= _rigionArr.size())
			throw std::invalid_argument("wrong region");
		if (partyNum >= _partyArr.size())
			throw std::invalid_argument("wrong party");
		Person* rep = nullptr;
		for (auto itr =_registerArr.begin(); itr != _registerArr.end(); itr++)
		{
			if (ID == (*itr)->getID())
				rep = (*itr);
		}
		if (rep == nullptr)
			throw std::invalid_argument("person not found");
		return rep;
	}

	void electionRound:: printRegions()    //regionNum, regionName, numOfRep
	{
		for (int i = 0; i < _rigionArr.size(); i++)
		{
			comReg* cr = dynamic_cast<comReg*>(_rigionArr[i]);
			try { if (cr == nullptr) 
				throw out_of_range("dynamic_cast error");
			}
			catch (std::exception& ex) {
				cout << "Error: " << ex.what() << endl;
				return;
			}
			std::cout << "region number: " << i << *(_rigionArr[i])<<"region type: ";
			if (cr->getType() == 1)
				std::cout << "whole" << std::endl;
			else
				std::cout << "divided" << std::endl;
		}
	}
	void electionRound:: printParty()     //partyNum, name, candidate, reps
	{
		for (int i = 0; i < _partyArr.size(); i++)
		{
			std::cout << "party number " << i << ": " << _partyArr[i];
		}
	}
	void electionRound::getVote(int ID, int partyNum)
	{
		int i;
		Person* p;
		try {p = voteCheck(ID, partyNum, i); }
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			return;
		}
		p->setVoteFor(partyNum);
		_rigionArr[i]->addToVoteCounter(1);
	}
	Person* electionRound::voteCheck(int ID, int partyNum, int& i)
	{
		if (partyNum < 0 || partyNum >= _partyArr.size())
			throw invalid_argument("party does't exist");
		Person* p = nullptr;
		for (i = 0; i < _rigionArr.size(); i++)
		{
			p = _rigionArr[i]->findPerson(ID);
			if (p != nullptr)
				break;
		}
		if (p == nullptr)
			throw invalid_argument("ID does't exist");
		if (p->getVoteFor() != -1)
			throw invalid_argument("this person has already voted");
		return p;
	}
	
	void electionRound::printCitizents()
	{
		for (int i = 0; i < _registerArr.size(); i++)
		{
			std::cout << *(_registerArr[i]);
		}
	}
	void electionRound::checkRes()const
	{
		if (_rigionArr.empty())
			throw invalid_argument("there are no regions");
		if (_partyArr.empty())
			throw invalid_argument("there are no parties");
	}
	
	void electionRound::calcRes()
	{
		try {_resultMat = new int*[_rigionArr.size()];}
		catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		try { _resSumArr = new resSum[_partyArr.size()]; }
		catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		for (int i = 0; i < _partyArr.size(); i++)
		{
			_resSumArr[i]._SumVotes = 0;
			_resSumArr[i]._sumRep = 0;
			_resSumArr[i]._partyNum = i;
		}

		for (int i = 0; i < _rigionArr.size(); i++)
		{
			try { _resultMat[i] = new int[_partyArr.size()]; }
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
			for (int j = 0; j < _partyArr.size(); j++)
			{
				_resultMat[i][j] = 0;
			}
		}

		for (int i = 0; i < _registerArr.size(); i++)
		{
			if (_registerArr[i]->getVoteFor() != -1)
			{
				int regNum = _registerArr[i]->getRegionNum();
				int partyNum = _registerArr[i]->getVoteFor();
				_resultMat[regNum][partyNum]++;
			}
		}
	}
	
	void electionRound::printResult()
	{
		try { checkRes(); }
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			return;
		}
		calcRes();
		resSum* regResSumArr;
		try { regResSumArr = new resSum[_partyArr.size()]; }
		catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		for (int i = 0; i < _partyArr.size(); i++)
		{
			regResSumArr[i]._partyNum = i;
			regResSumArr[i]._sumRep = 0;
			regResSumArr[i]._SumVotes = 0;
		}
		for (int i = 0; i < _rigionArr.size(); i++)
		{
			for (int j = 0; j < _partyArr.size(); j++)
			{
				regResSumArr[j]._SumVotes += _resultMat[i][j];
				float partyVotePercent;
				if (_rigionArr[i]->getVoteCounter() != 0)
					partyVotePercent = (static_cast<float>(regResSumArr[j]._SumVotes)) / (static_cast<float>(_rigionArr[i]->getVoteCounter()));
				else
					partyVotePercent = 0;
				regResSumArr[j]._sumRep = static_cast<int> (partyVotePercent * _rigionArr[i]->getNumOfRep());
			}
			comReg* cr;
			try {
				cr = dynamic_cast<comReg*> (_rigionArr[i]);
				if (cr == nullptr)
					throw std::invalid_argument("dynamic_cast error");
			}
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; return; }

			for (int j = 0; j < _partyArr.size(); j++)
				_resSumArr[j]._SumVotes += _resultMat[i][j];

			std::cout << "regions name: " << _rigionArr[i]->getName() << ", number of representetives given by the region: "
				<< _rigionArr[i]->getNumOfRep() << std::endl;
			if (cr->getType() == 1)
				printResultType1(regResSumArr, i);
			else
				printResultType2(regResSumArr, i);
			for (int j = 0; j < _partyArr.size(); j++)
			{
				regResSumArr[j]._sumRep = 0;
				regResSumArr[j]._SumVotes = 0;
			}
		}
		bubbleSort<resSum>(_resSumArr, _partyArr.size());
		std::cout << "the list of candidats with decsending number of reps gained: " << std::endl;
		for (int i = 0; i < _partyArr.size(); i++)
		{
			std::cout << _partyArr[_resSumArr[i]._partyNum].getCandidate()->getName() << " with " <<
				_resSumArr[i]._sumRep << " reps, and " << _resSumArr[i]._SumVotes << " votes" << std::endl;
		}
		delete[] regResSumArr;
		resetResult();
	}
	
	void electionRound::printResultType1(resSum* regResSumArr, int regIndex)
	{
		int index=0, max = regResSumArr[0]._sumRep;
		for (int i = 1; i < _partyArr.size(); i++)
		{
			if (regResSumArr[i]._sumRep > max)
			{
				index = i;                      //party
				max = regResSumArr[i]._sumRep;   //votes
			}
		}
		_resSumArr[index]._sumRep += _rigionArr[regIndex]->getNumOfRep();
		std::cout << "the chosen candidate for this region: " << _partyArr[index].getCandidate()->getName() << std::endl;
		printData(regResSumArr, regIndex);
	}
	void electionRound::printData(resSum* regResSumArr, int regIndex)
	{
		for (int j = 0; j < _partyArr.size(); j++)
		{
			std::cout << "party: " << _partyArr[j].getName() << std::endl;
			try {
				if (_partyArr[j].printChosenReps(regIndex, 0, regResSumArr[j]._sumRep) < regResSumArr[j]._sumRep)
					throw std::invalid_argument("this party doesn't have enough reps to represent this region");
				else
					_partyArr[j].printChosenReps(regIndex, 1, regResSumArr[j]._sumRep);
			}
			catch (std::exception& ex) {
				cout << "Error: " << ex.what() << endl;
			}
			
			float partyVotePercent;
			if (_rigionArr[regIndex]->getVoteCounter() == 0)
				partyVotePercent = 0;
			else
				partyVotePercent = (static_cast<float>(regResSumArr[j]._SumVotes)) / (static_cast<float>(_rigionArr[regIndex]->getVoteCounter()));
			std::cout << "number of votes for this party: " << regResSumArr[j]._SumVotes << ", the vote percent is: " <<
				static_cast<int>(partyVotePercent * 100) << "%" << std::endl;
		}
		if (_rigionArr[regIndex]->getLogSize() == 0)
			_rigionArr[regIndex]->setVotePercent(0);
		else
			_rigionArr[regIndex]->setVotePercent(static_cast<float>(_rigionArr[regIndex]->getVoteCounter()) / static_cast<float>(_rigionArr[regIndex]->getLogSize()));
		std::cout << "the vote percent in this region is: " << static_cast<int>(_rigionArr[regIndex]->getVotePercent() * 100) << "%" << std::endl;
	}

	void electionRound::printResultType2(resSum* regResSumArr, int regIndex)
	{
		for (int i = 0; i < _partyArr.size(); i++)
		{
			_resSumArr[i]._sumRep += regResSumArr[i]._sumRep;
		}
		std::cout << "all the candidats that the region has given them representetives are: " << std::endl;
		resSum* SortedregResSumArr;
		try{SortedregResSumArr = new resSum[_partyArr.size()];}
		catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		for (int i = 0; i < _partyArr.size(); i++)
			SortedregResSumArr[i] = regResSumArr[i];
		bubbleSort<resSum>(SortedregResSumArr, _partyArr.size());
		for (int i = 0; i < _partyArr.size() && SortedregResSumArr[i]._sumRep>0; i++)
		{
			std::cout << _partyArr[SortedregResSumArr[i]._partyNum].getCandidate()->getName() << " with " <<
				         SortedregResSumArr[i]._sumRep << " reps given" << std::endl;
		}
		delete[] SortedregResSumArr;
		printData(regResSumArr, regIndex);
	}

	
	void electionRound::resetResult()
	{
		for (int i = 0; i < _rigionArr.size(); i++)
			delete[] _resultMat[i];
		delete[] _resultMat;
		delete[] _resSumArr;
	}

	void electionRound::saveResults()
	{
		if (_rigionArr.size() == 0 || _partyArr.size() == 0)
			return;

		try { _resultMat = new int*[_rigionArr.size()]; }
		catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		for (int i = 0; i < _rigionArr.size(); i++)
		{
			try { _resultMat[i] = new int[_partyArr.size()]; }
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
			for (int j = 0; j < _partyArr.size(); j++)
				_resultMat[i][j] = 0;
		}

		for (int i = 0; i < _registerArr.size(); i++)    //calculate the result in the mat
		{
			if (_registerArr[i]->getVoteFor() != -1)
			{
				int regNum = _registerArr[i]->getRegionNum();
				int partyNum = _registerArr[i]->getVoteFor();
				_resultMat[regNum][partyNum]++;
			}
		}

		for (int i = 0; i < _rigionArr.size(); i++)
		{
			for (int j = 0; j < _partyArr.size(); j++)
			{
				int partyVoteCounter = _resultMat[i][j];
				float partyVotePercent;
				if (_rigionArr[i]->getVoteCounter() != 0)
					partyVotePercent = (static_cast<float>(partyVoteCounter)) / (static_cast<float>(_rigionArr[i]->getVoteCounter()));
				else
					partyVotePercent = 0;
				int numOfReps = partyVotePercent * _rigionArr[i]->getNumOfRep();
				int size;
				std::vector<Person*> repsArr = _partyArr[j].getReps(numOfReps, i, size);
				_rigionArr[i]->updateChosenRepsArr(repsArr, size);
			}		
		}
		for (int i = 0; i < _rigionArr.size(); i++)
			delete[] _resultMat[i];
		delete[] _resultMat;
	}

	void electionRound::addRegister(Person* p)
	{
		_registerArr.push_back(p);
	}
	
	void electionRound::printElectionDate()const
	{
		_electionDate.printDate();
	}
	bool electionRound::setElectionDate(Date electionDate)
	{
		_electionDate = electionDate;
		return true;
	}
	electionRound& electionRound::operator=(const electionRound& er)
	{
		if (!_rigionArr.empty())
		{
			for (auto itr = _rigionArr.begin(); itr != _rigionArr.end(); itr++)
				delete (*itr);
			_rigionArr.clear();
		}
			
		if (!_partyArr.empty())
			_partyArr.clear();

		if (!_registerArr.empty())
		{
			for (auto itr = _registerArr.begin(); itr != _registerArr.end(); itr++)
				delete (*itr);
			_registerArr.clear();
		}
			
		_electionDate = er.getElectionDate();
		_resSumArr = er.getResSumArr();
		_resultMat = er.getResultMat();

		_registerArr = er.getRegisterArr();
		_rigionArr = er.getRigionArr();
		_partyArr = er.getPartyArr();

		return *this;
	}

	bool electionRound::save(std::ostream& out)const
	{
		try {
			try {
				if (!(_electionDate.save(out)))
					throw "Error saving";
			}
			catch (std::string str) {
				return false;
			}
			int regionSize = _rigionArr.size(), registerSize = _registerArr.size(), partySize = _partyArr.size();
			out.write(rcastcc(&regionSize), sizeof(regionSize));
			checkFile(out);
			out.write(rcastcc(&registerSize), sizeof(registerSize));
			checkFile(out);
			out.write(rcastcc(&partySize), sizeof(partySize));
			checkFile(out);
			for (int i = 0; i < _rigionArr.size(); i++)
			{
				try {
					if (!(_rigionArr[i]->save(out)))
						throw "Error saving";
				}
				catch (std::string str) {
					return false;
				}
			}
			for (int i = 0; i < _registerArr.size(); i++)
			{
				try {
					if (!(_registerArr[i]->save(out)))
						throw "Error saving";
				}
				catch (std::string str) {
					return false;
				}
			}
			for (int i = 0; i < _partyArr.size(); i++)
			{
				try {
					if (!(_partyArr[i].save(out)))
						throw "Error saving";
				}
				catch (std::string str) {
					return false;
				}
			}

			return out.good();
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	void electionRound::checkFile(std::istream& file)
	{
		if (!file.good())
			throw "Error reading";
	}
	void electionRound::checkFile(std::ostream& file)const
	{
		if (!file.good())
			throw "Error saving";
	}
	bool electionRound::load(std::istream& in)
	{
		try {
			int regionSize, registerSize, partySize;
			try {
				if (!(_electionDate.load(in)))
					throw "Error loading";
			}
			catch (std::string str) {
				return false;
			}
			in.read(rcastc(&regionSize), sizeof(regionSize));
			checkFile(in);
			in.read(rcastc(&registerSize), sizeof(registerSize));
			checkFile(in);
			in.read(rcastc(&partySize), sizeof(partySize));
			checkFile(in);

			if (!_rigionArr.empty())
				_rigionArr.clear();
			for (int i = 0; i < regionSize; i++)
			{
				region* newReg;
				try {newReg = new comReg;}
				catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
				_rigionArr.push_back(newReg);
				try {
					if (!(_rigionArr[i]->load(in)))
						throw "Error loading";
				}
				catch (std::string str) {
					return false;
				}
			}

			if (!_registerArr.empty())
				_registerArr.clear();
			for (int i = 0; i < registerSize; i++)
			{
				Person* p;
				try { p = new Person; }
				catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
				_registerArr.push_back(p);
				try {
					if (!(_registerArr[i]->load(in)))
						throw "Error loading";
				}
				catch (std::string str) {
					return false;
				}
			}

			if (!_partyArr.empty())
				_partyArr.clear();
			_partyArr.resize(partySize);
			for (int i = 0; i < partySize; i++)
			{
				try {
					if (!(_partyArr[i].load(in)))
						throw "Error loading";
				}
				catch (std::string str) {
					return false;
				}
			}

			for (int i = 0; i < registerSize; i++)
				loadPerson(_registerArr[i]);

			loadCandidate(partySize, registerSize);

			for (int i = 0; i < registerSize; i++)
				loadRep(_registerArr[i]);

			return in.good();
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	
	void electionRound:: loadPerson(Person* p)
	{
		_rigionArr[p->getRegionNum()]->addPerson(p);
	}
	void electionRound::loadRep(Person* rep)
	{
		if (rep->getPartyMember()[0] != -1)
		{
			if(rep->getID()!=_partyArr[rep->getPartyMember()[0]].getCandidate()->getID())
				_partyArr[rep->getPartyMember()[0]].addRep(rep, true);
		}
	}
	void electionRound::loadCandidate(int partySize,int registerSize)
	{
		for (int i = 0; i < partySize; i++)
		{
			for (int j = 0; j < registerSize; j++)
			{
				if (_partyArr[i].getCandidate()->getID() == _registerArr[j]->getID())
				{
					_partyArr[i].setCandidate(_registerArr[j]);
					return;
				}
			}
		}
	}

}