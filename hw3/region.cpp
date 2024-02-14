#define _CRT_SECURE_NO_WARNINGS
#include "region.h"
#include"comlicatedRegion.h"
namespace elections {

	region::region(int numOfRep, const std::string name)
	{
		if(numOfRep<=0)
			throw std::invalid_argument("negative number of representatives");
		_voteCounter = 0;
		_votePercent = 0;
		_numOfRep = numOfRep;
		setName(name);
	}
	region::region(const region& r)
	{
		if (this != &r)
			*this = r;
	}
	region::~region(){}
	bool region::setName(const std::string name)
	{
		_name = name;
		return true;
	}
	bool region::setVotePercent(float percent)
	{
		_votePercent = percent;
		return true;
	}
	bool region::setVoteCounter(int num)
	{
		_voteCounter = num;
		return true;
	}
	void region::addToVoteCounter(int num)
	{
		_voteCounter += num;
	}
	
	void region::addPerson(Person* p)
	{		
		_personArr.push_back(p);
	}
	
	bool region::setNumOfRep(int numOfRep)
	{
		_numOfRep = numOfRep;
		return true;
	}

	void region::updateChosenRepsArr(std::vector<Person*> repsArr, int size)
	{
		for (int i = 0; i < size; i++)
			_chosenRepsArr.push_back(repsArr[i]);
		repsArr.clear();
	}

	region& region:: operator=(const region& r)
	{
		setName(r.getName());
		setNumOfRep(r.getNumOfRep());
		setVotePercent(r.getVotePercent());
		setVoteCounter(r.getVoteCounter());
		_personArr = r._personArr;
		return *this;
	}
	void region::printPersons()const
	{
		
		for (auto itr = _personArr.begin(); itr != _personArr.end(); itr++)
		{
			std::cout << "name: " << (*itr)->getName() << " ID: " << (*itr)->getID();
			std::cout << " birth year: ";
			(*itr)->printBirth();
		}
	}
	Person* region::findPerson(int ID)
	{
		for (auto itr = _personArr.begin(); itr != _personArr.end(); itr++)
		{
			if ((*itr)->getID() == ID)
				return (*itr);
		}
		return nullptr;
	}
	
	std::ostream& operator<<(std::ostream& os, const region& r)
	{
		std::cout << " region name: " << r.getName() <<
			", number of representetives: " << r.getNumOfRep() << std::endl;	
		return os;
	}
	bool region::operator==(const region& r)
	{
		if (_name != r.getName() || _voteCounter != r.getVoteCounter() || _numOfRep != r.getNumOfRep() ||
			            _votePercent != r.getVotePercent() || _personArr != r._personArr)
			return false;
		return true;
	}
	bool region::operator!=(const region& r)
	{
		return !(*this==r);
	}
	bool region::operator<(const region& r)
	{
		return _numOfRep < r.getNumOfRep();
	}
	bool region::operator>(const region& r)
	{
		return _numOfRep > r.getNumOfRep();
	}

	bool region::save(std::ostream& out)const
	{
		try {
			int size = _name.length();
			out.write(rcastcc(&size), sizeof(size));
			checkFile(out);
			out.write(_name.data(), size * sizeof(char));
			checkFile(out);
			out.write(rcastcc(&_voteCounter), sizeof(_voteCounter));
			checkFile(out);
			out.write(rcastcc(&_numOfRep), sizeof(_numOfRep));
			checkFile(out);
			out.write(rcastcc(&_votePercent), sizeof(_votePercent));
			checkFile(out);

			return out.good();
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	bool region::load(std::istream& in)
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
			in.read(rcastc(&_voteCounter), sizeof(_voteCounter));
			checkFile(in);
			in.read(rcastc(&_numOfRep), sizeof(_numOfRep));
			checkFile(in);
			in.read(rcastc(&_votePercent), sizeof(_votePercent));
			checkFile(in);
			if (!(_personArr.empty()))
				_personArr.clear();
			if (!(_chosenRepsArr.empty()))
				_chosenRepsArr.clear();
			return in.good();
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	void region::checkFile(std::istream& file)
	{
		if (!file.good())
			throw "Error reading";
	}
	void region::checkFile(std::ostream& file)const
	{
		if (!file.good())
			throw "Error saving";
	}
}

