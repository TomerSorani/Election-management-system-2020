#define _CRT_SECURE_NO_WARNINGS
#include "Party.h"
namespace elections
{
	Party::Party(Person* per, const char* name):_candidate(nullptr), _repArr(nullptr), _name(nullptr)
	{
		_logSize = 0;
		_phiSize = 1;
		setName(name);
		setCandidate(per);
		_repArr = new Person*[_phiSize];
	}
	Party::Party(const Party& other)
	{
		if (this != &other)
			*this = other;
	}
	Party::~Party()
	{
		delete[]_name;
		delete[]_repArr;
	}
	bool Party::setLogSize(int logSize)
	{
		_logSize = logSize;
		return true;
	}
	bool Party::setPhiSize(int phiSize)
	{
		_phiSize = phiSize;
		return true;
	}
	bool Party::setName(const char* name)
	{
		if (_name != nullptr)
			delete[] _name;
		int size = strlen(name) + 1;
		_name = new char[size];
		strcpy(_name, name);
		return true;
	}
	bool Party::setCandidate(Person* per)
	{
		if (_candidate != nullptr)
			delete _candidate;
		_candidate = per;
		return true;
	}

	Party& Party:: operator=(const Party& p)
	{
		setName(p.getName());
		setLogSize(p.getLogSize());
		setPhiSize(p.getPhiSize());
		setCandidate(p.getCandidate());
		_repArr = new Person*[_phiSize];
		for (int i = 0; i < _logSize; i++)
		{
			_repArr[i] = p._repArr[i];
		}
		return *this;
	}

	bool Party::addRep(Person* rep)
	{
		if (_logSize == _phiSize)
		{
			_phiSize *= 2;
			Person** newArr = new Person*[_phiSize];
			for (int i = 0; i < _logSize; i++)
			{
				newArr[i] = _repArr[i];
			}
			delete[]_repArr;
			_repArr = newArr;
		}
		if (_repArr == nullptr)
			_repArr[_logSize] = rep;
		else
		{
			int i;
			for (i = 0; i < _logSize; i++)
			{
				if (rep->getPartyMember()[1]-_repArr[i]->getPartyMember()[1] <= 0)
					break;
			}
			if (i == _logSize)
				_repArr[_logSize] = rep;
			else
			{
				for (int j = _logSize - 1; j >= i; j--)
					_repArr[j + 1] = _repArr[j];
				_repArr[i] = rep;
			}
		}
		_logSize++;
		return true;
	}

	void Party::printReps()const
	{
		int regNum = -1;
		std::cout << "representetives names: " << std::endl;
		for (int i = 0; i < _logSize; i++)
		{
			if (regNum != _repArr[i]->getPartyMember()[1])
			{
				regNum = _repArr[i]->getPartyMember()[1];
				std::cout << "all the represenetives that represent region: " << regNum<< std::endl;
			}
			std::cout << _repArr[i]->getName()<<std::endl;
		}
	}

	int Party::printChosenReps(int regionNum, bool flag, int maxReps)
	{
		int i, j = 0;
		for (i = 0; i < _logSize; i++)
		{
			if (_repArr[i]->getPartyMember()[1] == regionNum && j < maxReps)
			{
				if(flag)
					std::cout << _repArr[i]->getName() << std::endl;
				j++;
			}
		}
		if (flag)
			return 0;
		else
			return j;
	}

	Person** Party::getReps(int numOfReps, int regionNum, int& size)
	{
		Person** resArr = new Person*[numOfReps];
		int j = 0;
		for (int i = 0; i < _logSize && j < numOfReps; i++)
		{
			if (_repArr[i]->getPartyMember()[1] == regionNum)
				resArr[j++] = _repArr[i];
		}
		size = j;
		if (j < numOfReps)
		{
			Person** resArr2 = new Person*[j];
			for (int i = 0; i < j; i++)
				resArr2[i] = resArr[i];
			delete[] resArr;
			return resArr2;
		}
		return resArr;
	}

	std::ostream& operator<<(std::ostream& os, const Party& p)
	{
		std::cout <<p.getName() << ", candidate: " <<p.getCandidate()->getName() << std::endl;
		p.printReps();
		return os;
	}

	bool Party::save(std::ostream& out)const
	{
		int size = strlen(_name);
		out.write(rcastcc(&size), sizeof(size));
		if (!checkFile(out)) exit(-1);
		out.write(rcastcc(_name), size * sizeof(char));
		if (!checkFile(out)) exit(-1);
		out.write(rcastcc(&_phiSize), sizeof(_phiSize));
		if (!checkFile(out)) exit(-1);
		_candidate->save(out);

		return out.good();
	}
	bool Party::load(std::istream& in)
	{
		int size;
		in.read(rcastc(&size), sizeof(size));
		if (!checkFile(in)) exit(-1);
		if (_name != nullptr)
			delete[]_name;
		_name = new char[size + 1];
		in.read(rcastc(_name), size * sizeof(char));
		if (!checkFile(in)) exit(-1);
		_name[size] = '\0';
		_logSize = 0;
		in.read(rcastc(&_phiSize), sizeof(_phiSize));
		if (!checkFile(in)) exit(-1);
		if (_candidate != nullptr)
			delete[]_candidate;
		_candidate = new Person;
		_candidate->load(in);

		if (_repArr != nullptr)
			delete[]_repArr;
		_repArr = new Person*[_phiSize];
		
		return in.good();
	}
	bool Party::checkFile(std::istream& file)
	{
		if (!file.good()) {
			std::cout << "Error reading" << std::endl;
			return false;
		}
		return true;
	}
	bool Party::checkFile(std::ostream& file)const
	{
		if (!file.good()) {
			std::cout << "Error reading" << std::endl;
			return false;
		}
		return true;
	}
}