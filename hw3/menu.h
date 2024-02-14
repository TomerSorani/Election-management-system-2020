#pragma once
#include "simpleElectionRound.h"

namespace elections
{
	class menu
	{
	public:
		menu() {};
		~menu() {};
		void printStartMenu();
		electionRound* oneStart();
		electionRound* twoStart();
		void printMainMenu();
		void one(electionRound* ed);
		void two(electionRound* ed);
		void three(electionRound* ed);
		void four(electionRound* ed);
		void five(electionRound* ed);
		void six(electionRound* ed);
		void seven(electionRound* ed);
		void eight(electionRound* ed);
		void nine(electionRound* ed);
		void ten(electionRound* ed);
		void eleven(electionRound* ed);
		electionRound* twelve(electionRound* ed);
	};
	
}
