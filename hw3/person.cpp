#define _CRT_SECURE_NO_WARNINGS
#include"person.h"

namespace elections
{
	Person::Person(int birth, int ID, const std::string name, int regionNum, int year)
	{
		try{ if(year-birth<18)
			throw std::invalid_argument("Invalid age");}
		catch (std::invalid_argument& ex) { throw ex; }
		_voteFor = -1;
		setName(name);
		setPartyMember(-1, -1);
		try{ if(ID/100000000<1|| ID/ 100000000>9)
			throw std::invalid_argument("Invalid ID");}
		catch (std::invalid_argument& ex) { throw ex; }
		setID(ID);
		setBirth(birth);
		setRegionNum(regionNum);
	}
	
	Person::~Person(){}
	Person::Person(const Person& p)
	{
		if (this != &p)
			*this = p;
	}
	bool Person::setName(const std::string name)
	{
		_name = name;
		return true;
	}
	bool Person::setID(int ID)
	{
		_ID = ID;
		return true;
	}
	bool Person::setPartyMember(int PartyMember, int regionRep)
	{
		_PartyMember[0] = PartyMember;
		_PartyMember[1] = regionRep;
		return true;
	}
	bool Person::setBirth(int birth)
	{
		_birth = birth;
		return true;
	}
	bool Person::setVoteFor(int voteFor)
	{
		_voteFor = voteFor;
		return true;
	}
	void Person::printBirth()const
	{
		std::cout << _birth << std::endl;
	}
	bool Person::setRegionNum(int regionNum)
	{
		_regionNum = regionNum;
		return true;
	}
	Person& Person::operator=(const Person& p)
	{
		setName(p.getName());
		setID(p.getID());
		setBirth(p.getBirth());
		setPartyMember(p.getPartyMember()[0], p.getPartyMember()[1]);
		_voteFor = p.getVoteFor();
		_regionNum = p.getRegionNum();
		return *this;
	}
	bool Person::operator==(const Person& p)
	{
		return (_ID == p.getID());
	}
	bool Person::operator!=(const Person& p)
	{
		return !(*this == p);
	}
	bool Person::operator<(const Person& p)
	{
		return (_regionNum < p.getRegionNum());
	}
	bool Person::operator>(const Person& p)
	{
		return (_regionNum > p.getRegionNum());
	}
	std::ostream& operator<<(std::ostream& os, const Person& p)
	{
		std::cout << "name: " << p.getName() << " ID: " << p.getID()
			<< " from region " << p.getRegionNum() << ", birth: " << p.getBirth() << std::endl;
		return os;
	}
	
	bool Person::save(std::ostream& out)const
	{
		try {
			int size = _name.size();
			out.write(rcastcc(&size), sizeof(size));
			checkFile(out);
			out.write(_name.data(), size * sizeof(char));
			checkFile(out);
			out.write(rcastcc(&_ID), sizeof(_ID));
			checkFile(out);
			out.write(rcastcc(&_birth), sizeof(_birth));
			checkFile(out);
			out.write(rcastcc(&_PartyMember[0]), sizeof(int));
			checkFile(out);
			out.write(rcastcc(&_PartyMember[1]), sizeof(int));
			checkFile(out);
			out.write(rcastcc(&_voteFor), sizeof(_voteFor));
			checkFile(out);
			out.write(rcastcc(&_regionNum), sizeof(_regionNum));
			checkFile(out);
			return out.good();
		}
		 catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	bool Person::load(std::istream& in)
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
			in.read(rcastc(&_ID), sizeof(_ID));
			checkFile(in);
			in.read(rcastc(&_birth), sizeof(_birth));
			checkFile(in);
			in.read(rcastc(&_PartyMember[0]), sizeof(int));
			checkFile(in);
			in.read(rcastc(&_PartyMember[1]), sizeof(int));
			checkFile(in);
			in.read(rcastc(&_voteFor), sizeof(_voteFor));
			checkFile(in);
			in.read(rcastc(&_regionNum), sizeof(_regionNum));
			checkFile(in);
			return in.good();
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	void Person::checkFile(std::istream& file)
	{
		if (!file.good()) 
			throw "Error reading";
	}
	void Person::checkFile(std::ostream& file)const
	{
		if (!file.good())
			throw "Error saving";
	}
}