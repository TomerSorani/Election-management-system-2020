#pragma once
namespace elections {
	
		class resSum
		{
		public:
			int _SumVotes, _sumRep, _partyNum;

			resSum& operator= (const resSum& r)
			{
				_SumVotes = r._SumVotes;
				_sumRep = r._sumRep;
				_partyNum = r._partyNum;
				return *this;
			}
			bool operator> (const resSum& r)
			{
				return (_sumRep > r._sumRep);
			}
			bool operator< (const resSum& r)
			{
				return (_sumRep < r._sumRep);
			}
			bool operator== (const resSum& r)
			{
				return (_SumVotes == r._SumVotes && _sumRep == r._sumRep && _partyNum == r._partyNum);
			}
			bool operator!= (const resSum& r)
			{
				return !(*this == r);
			}
		};
	}