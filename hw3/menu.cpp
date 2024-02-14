#include "menu.h"
namespace elections {
	using namespace std;

	void menu::printStartMenu()
	{
		cout << "to create a new election round, please press 1" << endl;
		cout << "to load an existing election round, please press 2" << endl;
		cout << "to exit, please press 3" << endl;
	}
	electionRound* menu::oneStart()
	{
		int d, m, y, type;
		electionRound* ed;
		cout << "please enter the election type. 0=regular, 1=simple" << endl;
		cin >> type;
		if (type == 0)
		{
			try { ed = new electionRound; }
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		}
		else
		{
			string name;
			int numOfReps;
			cout << "please enter the name of the region and the number of reps: " << endl;
			cin >> name >> numOfReps;
			try { ed = new simpleElectionRound(name, numOfReps); }
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		}
		bool flag = true;
		while (flag)
		{
			cout << "please enter the election date (dd  mm  yyyy): " << endl;
			cin >> d >> m >> y;
			try {
				Date date(d, m, y);
				flag = false;
			}
			catch (std::exception& ex) {
				cout << "Error: " << ex.what() << endl;
				flag = true;
			}
		}
		Date electionDate(d, m, y);
		ed->setElectionDate(electionDate);
		return ed;
	}
	electionRound* menu::twoStart()
	{
		electionRound* ed;
		string name;
		cout << "please enter the name of the file:" << endl;
		cin >> name;

		ifstream infile;
		infile.open(name, ios::binary);
		if (!infile)
		{
			cout << "error infile" << endl;
			exit(-1);
		}
		int type;
		infile.read(rcastc(&type), sizeof(type));
		if (!infile.good()) {
			cout << "Error reading" << endl;
			exit(-1);
		}
		if (type == 0)
		{
			try { ed = new electionRound; }
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		}
		else
		{
			try { ed = new simpleElectionRound; }
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		}
		try {
			if (!(ed->load(infile)))
				throw "Error loading";
			else
				std::cout << "load successfully" << std::endl;
		}
		catch (std::string str) {
			cout << str << endl;
		}
		infile.close();
		return ed;
	}
	void menu::printMainMenu()
	{
		cout << endl;
		cout << "to add a region, please press 1" << endl;
		cout << "to add a citizen, please press 2" << endl;
		cout << "to add a party, please press 3" << endl;
		cout << "to add a person as a party rep, please press 4" << endl;
		cout << "to print all of the regions, please press 5" << endl;
		cout << "to print all of the citizens, please press 6" << endl;
		cout << "to print all of the parties, please press 7" << endl;
		cout << "to vote, please press 8" << endl;
		cout << "to print the election result, please press 9" << endl;
		cout << "to exit, please press 10" << endl;
		cout << "to save this election round, please press 11" << endl;
		cout << "to load an existing election round, please press 12" << endl;
	}
	void menu::one(electionRound* ed)
	{
		string name;
		int numOfReps, type;
		cout << "please enter the region kind. 1=whole, 2=divided: " << endl;
		cin >> type;
		cout << "please enter the name of the region and the number of reps: " << endl;
		cin >> name >> numOfReps;
		ed->addRegion(name, numOfReps, type);
	}
	void menu::two(electionRound* ed)
	{
		string name;
		int y, ID, regNum;
		cout << "please enter the name of the citizen: " << endl;
		cin >> name;
		cout << "please enter ID: " << endl;
		cin >> ID;
		cout << "please enter Birth year: " << endl;
		cin >> y;
		cout << "please enter the region serial number: " << endl;
		cin >> regNum;
		ed->addPerson(name, ID, y, regNum);
	}
	void menu::three(electionRound* ed)
	{
		string name;
		int ID;
		cout << "please enter the name of the party: " << endl;
		cin >> name;
		cout << "please enter the ID of the candidate: " << endl;
		cin >> ID;
		ed->addParty(name, ID);
	}
	void menu::four(electionRound* ed)
	{
		int ID, partyNum, regNum;
		cout << "please enter the ID of the existing person: " << endl;
		cin >> ID;
		cout << "please enter the party serial number: " << endl;
		cin >> partyNum;
		cout << "please enter the region serial number: " << endl;
		cin >> regNum;
		ed->addRep(ID, partyNum, regNum);
	}
	void menu::five(electionRound* ed)
	{
		ed->printRegions();
	}
	void menu::six(electionRound* ed)
	{
		ed->printCitizents();
	}
	void menu::seven(electionRound* ed)
	{
		ed->printParty();
	}
	void menu::eight(electionRound* ed)
	{
		int ID, partyNum;
		cout << "please enter the ID of the existing person: " << endl;
		cin >> ID;
		cout << "please enter the party serial number: " << endl;
		cin >> partyNum;
		ed->getVote(ID, partyNum);
	}
	void menu::nine(electionRound* ed)
	{
		ed->printResult();
	}
	void menu::ten(electionRound* ed)
	{
		ed->saveResults();
	}
	void menu::eleven(electionRound* ed)
	{
		string name;
		cout << "please enter the name of the file:" << endl;
		cin >> name;
		ofstream outfile;
		outfile.open(name, ios::trunc | ios::binary);
		if (!outfile)
		{
			cout << "error outfile" << endl;
			exit(-1);
		}
		int type;
		if (typeid(*ed) == typeid(electionRound))
			type = 0;
		else
			type = 1;
		outfile.write(rcastc(&type), sizeof(type));
		if (!outfile.good()) {
			cout << "Error reading" << endl;
			exit(-1);
		}
		try {
			if (!(ed->save(outfile)))
				throw "Error saving";
			else
				std::cout << "save successfully" << std::endl;
		}
		catch (std::string str) {
			cout << str << endl;
		}
		outfile.close();
	}
	electionRound* menu::twelve(electionRound* ed)
	{
		string name;
		cout << "please enter the name of the file:" << endl;
		cin >> name;

		ifstream infile;
		infile.open(name, ios::binary);
		if (!infile)
		{
			cout << "error infile" << endl;
			exit(-1);
		}
		ed->~electionRound();
		int type;
		infile.read(rcastc(&type), sizeof(type));
		if (!infile.good()) {
			cout << "Error reading" << endl;
			exit(-1);
		}
		if (type == 0)
		{
			try { ed = new electionRound; }
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		}
		else
		{
			try { ed = new simpleElectionRound; }
			catch (std::bad_alloc& ex) { std::cout << ex.what() << std::endl; exit(-1); }
		}
		try {
			if (!(ed->load(infile)))
				throw "Error loading";
			else
				std::cout << "load successfully" << std::endl;
		}
		catch (std::string str) {
			cout << str << endl;
		}
		infile.close();
		return ed;
	}
}