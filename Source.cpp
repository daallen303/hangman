/*
CSCI 111-002
Final Assignment
11/20/14
By: Danny Allen
The purpose of this program is to create a unique version of Hangman
Algorythm steps:
1.read in text document with words and randomly select one for the player to guess
2. Player enters letters until they either guess the word correctly or until the stickfigure gets hanged
3..After each letter is guessed put it in the used letter bank
4. if guess is incorrect take away one guess
5.Ask user to play again
*/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "ConsoleColor.h"
#include <locale>

using namespace std;
const int MAX_WORDS = 100;
const int MAX_GUESSES = 100;
const int MAX_EV = 100;

void writeWord(string random);
void check(string random, string& random2, char guesses[], int& count, int& wrong, string evidenceGood[], string evidenceBad[], string proofofInnocence[], string guess);
bool checkLetter(char guesses[], int count);
void change(string& random2);
void guessWord(string random, string evidenceBad[], string proofofInnocence[], string& guess, string& random2);
void evidenceAgainst(string evidenceBad[]);
void evidenceFor(string evidenceGood[]);
void readDataGood(string evidenceGood[], string proofofInnocence[]);
void readDataBad(string evidenceBad[], string proofofGuilt[]);
void drawFreeMan();
void drawHanged();
void backgroundstory();
void convicted(string proofofGuilt[]);
void freedom(string proofofInnocence[]);
void easterEgg1();
void easterEgg2();


int main()
{
	backgroundstory();
	string play = "yes";
	string evidenceBad[MAX_EV] = {};
	string evidenceGood[MAX_EV] = {};
	string proofofInnocence[4] = {};
	string proofofGuilt[4] = {};
	readDataGood(evidenceGood, proofofInnocence);
	readDataBad(evidenceBad, proofofGuilt);
	string HangWordsList[MAX_WORDS] = {};
	
	
	ifstream fin;
	int i = 0;
	fin.open("Words.txt");
	while (fin)
	{

		fin >> HangWordsList[i];
		//cout << HangWordsList[i] << endl;
		i++;
	}

	fin.close();
	srand(time(NULL));
	
	do{
		char guesses[MAX_GUESSES] = { '_' };
		int count = 0;
		int wrong = 6;
		string random = HangWordsList[rand() % 21];
		string random2 = random;
		string guess = " ";
		change(random2);
		writeWord(random);
		while (wrong != 0 && random != random2)
		{
			cout << "Please Enter a letter to see if it is in the word or enter # to guess the word" << endl;
			cin >> guesses[count];
			checkLetter(guesses, count);
			if (checkLetter(guesses, count) != false)
			{
				check(random, random2, guesses, count, wrong, evidenceGood, evidenceBad, proofofInnocence, guess);
			}
			if (checkLetter(guesses, count) == false)
			{
				cout << "You Already guessed that letter, guess again!" << endl;
			}
			if (random2 == random)
			{
				freedom(proofofInnocence);
				drawFreeMan();
				break;
			}
			count += 1;
		}

		if (wrong == 0)
		{
			cout << random << endl;
			convicted(proofofGuilt);
			drawHanged();
		}
		cout << " If you want to play again type yes and hit enter, anything else will close the program." << endl;
		cin >> play;
         	} while (play == "yes");
	   return 0;

}

void writeWord(string random)
{
	for (int i = 0; i < random.length(); i++)
	{
		cout << "_ ";
	}
	cout << endl;
}
void change(string& random2)
{
	char ch = '_';
	for (int i = 0; i < random2.length(); i++)
	{
		random2[i] = ch;
	}
}
bool checkLetter(char guesses[], int count)
{
    
	int j = 0;
	if (count != 0){
		while (j < count){
			if (tolower(guesses[count]) == tolower(guesses[j]) && guesses[count] != '#')
			{
				return false;
			}
			    j++;
		}
	}
	else if (count == 0 )
	{
		return true;
	}
}

void check(string random, string& random2, char guesses[], int& count, int& wrong, string evidenceGood[], string evidenceBad[],string proofofInnocence[], string guess)
{
	int jump = 0;
	int len = random.length();
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j <= count; j++){
			if (guesses[j] == '#' && i == len - 1 && j == count){
				guessWord(random, evidenceBad, proofofInnocence, guess, random2);
				jump = 100;
				break;
			}
			if (tolower(guesses[j]) == tolower(random[i])){
				random2[i] = random[i];
				if (j == count)
				{
					jump += 1;
				}
			}
		}
	}
	cout << endl;
	if (jump > 0 && jump!=100)
	{
		evidenceFor(evidenceGood);
	}
	if (jump == 0)
	{
		wrong -= 1;
		evidenceAgainst(evidenceBad);
	}
	for (int k = 0; k < random2.length(); k++)
	{
		cout << random2[k] << " ";
	}
	cout << endl;
}
void guessWord(string random, string evidenceBad[], string proofofInnocence[], string& guess, string& random2)
{
	cout << "Enter your guess... if you dare" << endl;
	cin >> guess;
	if (guess == random) 
	{
		random2 = guess;
    }
	if (guess == "tacocat")
	{
		easterEgg1();
	}
	if (guess == "snowfall")
	{
		easterEgg2();
	}
	else if (guess != random && guess!= "tacocat" && guess != "honeybadger"){
		cout << red << "Your guess was wrong... " << white;
        evidenceAgainst(evidenceBad);
	}
}
void easterEgg2()
{
	for (int i = 0; i < 300; i++)
	{
		cout << white << " ''''' ' '' '' '' ' '  '  '' ''  ''  ''  ' ' ''' '' '  ' ''  ''  ";
		cout << " '  '  ' '' ''  ' '' ''  '  '  ''  '''  ' '' '  ''  ''  ''  ' '";
	}
}
void easterEgg1()
{
	for (int i = 0; i < 1000; i++)
	{
		cout << "T" << green << "a" << red << "c" << yellow << "o" << white << "c" << green << "a"<< red << "t !";
	}
	cout << endl;
}
void readDataGood(string evidenceGood[], string proofofInnocence[])
{
	int i = 0;
	ifstream fin;
	fin.open("EvidenceInDefense.txt");
	while(fin && i < MAX_EV)
	{
		 getline(fin, evidenceGood[i]);
		 i++;
	} 
	fin.close();
	int j = 0;
	fin.open("ProofofInnocence.txt");
	while (fin && j < 4)
	{
		getline(fin, proofofInnocence[j]);
		j++;
	}
	fin.close();
}
void readDataBad(string evidenceBad[], string proofofGuilt[])
{

	int i = 0;
	ifstream fin;
	fin.open("EvidenceAgainst.txt");
	while (fin && i < MAX_EV)
	{
		getline(fin, evidenceBad[i]);
		i++;
	}
	fin.close();
	int j = 0;
	fin.open("ProofofGuilt.txt");
	while (fin && j < 4)
	{
		getline(fin, proofofGuilt[j]);
		j++;
	}
	fin.close();
}
void evidenceAgainst(string evidenceBad[])
{
	cout << red << "Evidence is being presented by the Prosecutor..." << white << endl;
	cout << endl;
	cout << red << evidenceBad[rand() % 9] << white;
	cout << endl;
}
void convicted(string proofofGuilt[])
{
	cout << blue << proofofGuilt[rand() % 4] << white <<endl;
}
void freedom(string proofofInnocence[])
{
	cout << blue << proofofInnocence[rand() % 4] << white << endl;
}
void evidenceFor(string evidenceGood[])
{
	cout << green << "Evidence is being presented by the defense..." << white << endl;
	cout << endl;
	cout << green << evidenceGood[rand() % 9] << white;
	cout << endl;
}

void backgroundstory()
{
	cout << "There has been a most horrible crime committed!" << endl;
	cout << "A women on the eve of this morning December 11, 1888 was" << endl;
	cout << "struck down by a candle stick in her study!" << endl;
	cout << "Found in the study was the body of the victim by the name of " << endl;
	cout << "Mary Ann Sue, a bloodied candle stick,a pile of gunpowder, size 9 male shoe" << endl;
	cout << "belonging to the left foot, a strange blue paste, a piece of leather " << endl;
	cout << "(what it belongs to is unknown), and the bible turned open to a" << endl;
	cout << "very peculiar page. The accused before you is a blacksmith" << endl;
	cout << "by the name of Hank R Jones jr. We are here to decide " << endl;
	cout << "if he should be innocent and walk as a free man or... " << endl;
	cout << "To hang as a murderer!" << endl;
	cout << endl;
	cout << endl;
	cout << " Guess the word below to unviel clues and help the jury" << endl;
}
void drawFreeMan()
{
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	    cout << yellow << "         _________" << endl;
	    cout << yellow << "        |         |" << endl;
		cout << yellow << "   _____|         |_____"<< endl;
		cout << yellow << "  (_____________________)"<<endl;
	    cout << white  << "       /          \\ " << endl;
	              cout << "     {|   (o)(o)   |} " << endl;
		          cout << "      |"<< blue << "   ' " << white << " >     |     " << endl;
		          cout << "       \\" << blue << "  '" << white << "^^^^^^  /" << endl;
		          cout << "        \\" << blue << " '" << white << "(||||) /" << endl;
		          cout << "         \\       /" << endl;
		          cout << "        I'M FREE!!!!!!" << endl;
		 
}

void drawHanged()
{
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
   cout << yellow << "============o=========" << endl;
	  cout << red << "||          |       ||"<< endl;
	         cout << "||          |       ||" << endl;
	         cout << "||          O       || " << endl;
	         cout << "||         /l\\      ||"<< endl;
	         cout << "||          l       || "  << endl;
	         cout << "||________ / \\_____ ||" << endl;
	         cout << "||        |         ||" << endl;
	         cout << "||        '         ||" << endl;
	cout <<yellow << "======================" << white << endl;
}
