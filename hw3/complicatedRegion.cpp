#define _CRT_SECURE_NO_WARNINGS

#include"comlicatedRegion.h"
namespace elections {
	comReg::comReg(int numOfRep, const std::string name, int type):region::region(numOfRep, name)
	{
		setType(type);
	}
	comReg::comReg(const comReg& cr)
	{
		if (this != &cr)
			*this = cr;
	}
	comReg::~comReg() {}
	bool comReg::setType(int type)
	{
		_type = type;
		return true;
	}
	comReg& comReg::operator=(const comReg& cr)
	{
		region::operator=(cr);
		_type = cr.getType();
		return *this;
	}
	bool comReg::operator==(const comReg& cr)
	{
		return (_type == cr.getType() && region::operator==(cr));
	}
	bool comReg::operator!=(const comReg& cr)
	{
		return !(*this == cr);
	}
	bool comReg::save(std::ostream& out) const
	{
		try {
			out.write(rcastcc(&_type), sizeof(_type));
			checkFile(out);
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
		return region::save(out);
	}
	bool comReg::load(std::istream& in)
	{
		try {
			in.read(rcastc(&_type), sizeof(_type));
			checkFile(in);
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
		return region::load(in);
	}

}