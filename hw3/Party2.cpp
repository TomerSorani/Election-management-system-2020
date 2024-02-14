#define _CRT_SECURE_NO_WARNINGS
#include "Party2.h"
namespace elections
{
	Party::Party(Person* per, const std::string name) :_candidate(nullptr)
	{
		setName(name);
		setCandidate(per);
	}
	Party::Party(const Party& other)
	{
		if (this != &other)
			*this = other;
	}
	Party::~Party(){}
	bool Party::setName(const std::string name)
	{
		_name = name;
		return true;
	}
	bool Party::setCandidate(Person* per)
	{
		_candidate = per;
		return true;
	}

	Party& Party:: operator=(const Party& p)
	{
		setName(p.getName());
		setCandidate(p.getCandidate());
		_repArr = p._repArr;
		return *this;
	}

	void Party::addRep(Person* rep, bool load)
	{
		if(rep->getPartyMember()[0]!=-1 && !load)
			throw std::invalid_argument("this person is already party member");
		if (_repArr.empty())
			_repArr.push_back(rep);
		else
		{
			DynamicArray<Person*>::iterator i = _repArr.begin();
			for (; i != _repArr.end(); i++)
			{
				if (rep->getPartyMember()[1] - (*i)->getPartyMember()[1] <= 0)
					break;
			}
			if (i == _repArr.end())
				_repArr.push_back(rep);
			else
				_repArr.insert(i, rep);
		}
	}

	void Party::printReps()const
	{
		int regNum = -1;
		std::cout << "representetives names: " << std::endl;
		for (int i = 0; i < _repArr.size(); i++)
		{
			if (regNum != _repArr[i]->getPartyMember()[1])
			{
				regNum = _repArr[i]->getPartyMember()[1];
				std::cout << "all the represenetives that represent region: " << regNum << std::endl;
			}
			std::cout << _repArr[i]->getName() << std::endl;
		}
	}

	int Party::printChosenReps(int regionNum, bool flag, int maxReps)
	{
		int j = 0;
		for (DynamicArray<Person*>::iterator i = _repArr.begin(); i != _repArr.end(); i++)
		{
			if ((*i)->getPartyMember()[1] == regionNum && j < maxReps)
			{
				if (flag)
					std::cout << (*i)->getName() << std::endl;
				j++;
			}
		}
		if (flag)
			return 0;
		else
			return j;
	}

	std::vector<Person*> Party::getReps(int numOfReps, int regionNum, int& size)
	{
		std::vector<Person*> resArr;
		int j = 0;
		for (int i = 0; i < _repArr.size() && j < numOfReps; i++)
		{
			if (_repArr[i]->getPartyMember()[1] == regionNum)
			{
				resArr.push_back(_repArr[i]);
				j++;
			}
		}
		size = j;
		return resArr;
	}

	std::ostream& operator<<(std::ostream& os, const Party& p)
	{
		std::cout << p.getName() << ", candidate: " << p.getCandidate()->getName() << std::endl;
		p.printReps();
		return os;
	}
	bool Party::operator==(const Party& p)
	{
		return (_candidate == p.getCandidate());
	}
	bool Party::operator!=(const Party& p)
	{
		return !(*this == p);
	}
	bool Party::operator<(const Party& p)
	{
		return (_name < p.getName());
	}
	bool Party::operator>(const Party& p)
	{
		return (_name > p.getName());
	}
	bool Party::save(std::ostream& out)const
	{
		try {
			int size = _name.size();
			out.write(rcastcc(&size), sizeof(size));
			checkFile(out);
			out.write(_name.data(), size * sizeof(char));
			checkFile(out);
			try {
				if (!(_candidate->save(out)))
					throw "Error saving";
			}
			catch (std::string str) {
				return false;
			}
			return out.good();
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	bool Party::load(std::istream& in)
	{
		try {
			int size;
			in.read(rcastc(&size), sizeof(size));
			checkFile(in);
			char* str;
			try { str = new char[size + 1]; }
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
			in.read(rcastc(str), size * sizeof(char));
			str[size] = '\0';
			_name = str;
			delete[] str;
			checkFile(in);
			if (_candidate != nullptr)
				delete[]_candidate;
			_candidate = new Person;
			try {
				if (!(_candidate->load(in)))
					throw "Error loading";
			}
			catch (std::string str) {
				return false;
			}
			return in.good();
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	void Party::checkFile(std::istream& file)
	{
		if (!file.good())
			throw "Error reading";
	}
	void Party::checkFile(std::ostream& file)const
	{
		if (!file.good())
			throw "Error saving";
	}
}