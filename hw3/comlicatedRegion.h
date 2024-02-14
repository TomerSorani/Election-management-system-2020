#pragma once
#include "region.h"
namespace elections {
	class comReg: public region
	{
	private:
		int _type;   // 1=whole  , 2=divided
	public:
	comReg(int numOfRep=1, const std::string name=" ", int type=-1);
	comReg(const comReg& cr);
	virtual ~comReg();
	int getType() const { return _type; }
	bool setType(int type);
	comReg& operator=(const comReg& cr);
	virtual bool operator==(const comReg& cr);
	virtual bool operator!=(const comReg& cr);
	virtual bool save(std::ostream& out) const;
	virtual bool load(std::istream& in);
	};

}
