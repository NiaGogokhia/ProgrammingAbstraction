/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <vector>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "set.h"
#include <ctime>
#include <cstdlib>
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();


//roll dice
char cubeSide(string str){
	int randNumber = 0;
	//rand between 0 and 5
	randNumber = randomInteger(0, 5);
	char c = str[randNumber];
	return c;
}

//random cubes for cells
Vector<string> randomCubes(Vector<string> cubes){
	for(int i = 0; i < cubes.size(); i++){
		int rand = randomInteger(i, cubes.size()-1);
		string temp = cubes[i];
		cubes[i] = cubes[rand];
		cubes[rand] = temp;
	}
	return cubes;
}
Vector<Vector<bool> > backtrackingGrid(int size){
	Vector<Vector<bool> > used;
	for(int i = 0; i < size; i++){
		Vector<bool> line;
		for(int k = 0; k < size; k++){
			line.push_back(false);
		}
		used.push_back(line);
	}
	return used;
}

//returns grid of chars which is ready to display
Vector<Vector<char> >assembleBoard(Vector<string> list, int size){
	Vector<string> cubes = randomCubes(list);
	Vector<Vector<char> > board;

	string chars;
	for(int i = 0; i < cubes.size(); i++){
		char c = cubeSide(cubes[i]);
		chars+=c;
	}

	int index = 0;
	for(int i = 0; i < size; i++){
		Vector<char>line;
		for(int k = 0; k < size; k++){
			line.push_back(chars[index]);
			index++;
		}
		board.push_back(line);
	}
	return board;
}

string toUpper(string word){
	string updated;
	for(int i = 0; i < word.size(); i++){
		updated+= toupper(word[i]);
	}
	return updated;
}

//checks if board contains the word player entered
bool boardContainsWord(string &word, Vector<Vector<char> > &boardL, Vector<Vector<bool> > used, int i, int k, int index){
	if(index > word.size()-1)return true;
	if(i < 0 || k < 0 || i > boardL.size()-1 || k > boardL[0].size()-1 || used[i][k] || boardL[i][k] != word[index]) return false;
	used[i][k] = true;
	return (boardContainsWord(word, boardL, used, i+1, k, index+1) ||
			boardContainsWord(word, boardL, used, i-1, k, index+1) ||
			boardContainsWord(word, boardL, used, i, k+1, index+1) ||
			boardContainsWord(word, boardL, used, i, k-1, index+1) ||
			boardContainsWord(word, boardL, used, i+1, k+1, index+1) ||
			boardContainsWord(word, boardL, used, i+1, k-1, index+1) ||
			boardContainsWord(word, boardL, used, i-1, k+1, index+1) ||
			boardContainsWord(word, boardL, used, i-1, k-1, index+1));
}

void checkWord(string &word, Lexicon & dictionary, Set<string> &playerWords, Vector<Vector<char> > &boardL, int size){
	string updatedWord = toUpper(word);

	if(word.length() < 4) cout << "Minimum length of word is 4." << endl;
	else if(!dictionary.contains(updatedWord))cout << "The entered word does not exist." << endl;
	else if(playerWords.contains(updatedWord))cout << "The entered word is already in your list." << endl;
	else{
		Vector<Vector<bool> > used = backtrackingGrid(size);
		int counter = 0;
		for(int i = 0; i < boardL.size(); i++){
			if(counter != 0)break;
			for(int k = 0; k < boardL[0].size(); k++){
				if(boardContainsWord(updatedWord, boardL, used, i, k, 0)){
					recordWordForPlayer(updatedWord, HUMAN);
					playerWords.insert(updatedWord);
					counter++;
					break;
				}
			}
		}
	}
}
void playerTurn(Vector<Vector<char> > &boardL, Set<string> &playerWords, Lexicon & dictionary, int size){
	cout << "Enter the words you can find and press ENTER to finish your turn." << endl;
	while(true){
		cout << "Enter the word: ";
		string word = getLine();
		if(word.size() == 0) break;
		else checkWord(word, dictionary, playerWords, boardL, size);
	}
}

//searchs for possible words on board
void searchForWord(Vector<Vector<char> > &boardL, Set<string> &playerWords, Set<string> &computerWords, Lexicon & dictionary, int i, int k, string curr, Vector<Vector<bool> > used, int size){
	if(i < 0 || k < 0 || i > boardL.size()-1 || k > boardL[0].size()-1 || used[i][k] || curr.size() == size*size || !dictionary.containsPrefix(curr)) return;
	curr += boardL[i][k];
	used[i][k] = true;
	if(dictionary.contains(curr)){
		if(!playerWords.contains(curr) && !computerWords.contains(curr) && curr.size() >= 4){
			recordWordForPlayer(curr, COMPUTER);
			computerWords.insert(curr);
		}
	}else if(!dictionary.containsPrefix(curr)) return;
	searchForWord(boardL, playerWords, computerWords, dictionary, i+1, k, curr, used, size);
	searchForWord(boardL, playerWords, computerWords, dictionary, i-1, k, curr, used, size);
	searchForWord(boardL, playerWords, computerWords, dictionary, i, k+1, curr, used, size);
	searchForWord(boardL, playerWords, computerWords, dictionary, i, k-1, curr, used, size);
	searchForWord(boardL, playerWords, computerWords, dictionary, i+1, k+1, curr, used, size);
	searchForWord(boardL, playerWords, computerWords, dictionary, i+1, k-1, curr, used, size);
	searchForWord(boardL, playerWords, computerWords, dictionary, i-1, k+1, curr, used, size);
	searchForWord(boardL, playerWords, computerWords, dictionary, i-1, k-1, curr, used, size);
}
void computerTurn(Vector<Vector<char> > &boardL, Set<string> &playerWords, Set<string> &computerWords, Lexicon & dictionary, int size){
	Vector<Vector<bool> > used = backtrackingGrid(size);
	//from each cell of grid searches for words recursively
	for(int i = 0; i < boardL.size(); i++){
		for(int k = 0; k < boardL[0].size(); k++){
			searchForWord(boardL, playerWords, computerWords, dictionary, i, k, "", used, size);
		}
	}
}
//takes player entries as cubes
Vector<string> customized(int size){
	if(size == 4)cout << "Enter 16 strings with 6 characters" <<endl;
	if(size == 5)cout << "Enter 25 strings with 6 characters" <<endl;
	Vector<string> cubes;
	for(int i = 0; i < size*size; i ++){
		string cube = getLine();
		if(cube.length() != 6){
			cout << "The length of the string should be 6 as cube has 6 sides." << endl;
			i--;
		}else{
			string updated = toUpper(cube);
			cubes.push_back(updated);
		}
	}
	return cubes;
}
/* Main program */

int main() {
	Lexicon dictionary("EnglishWords.dat");
	while(true){
		GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
		initGBoggle(gw);
	    welcome();
		giveInstructions();

		cout << "Would you like to play Standard Size Boggle or Big Boggle?" << endl;
		cout << "Enter Standard or Big" << endl;
		string gameSize = getLine();
		while(true){
			if(gameSize == "Standard" || gameSize == "Big") break;
			cout << "Enter Standard or Big" << endl;
			gameSize = getLine();
		} 
		int size = 0;
		if(gameSize == "Standard") size = 4;
		else if(gameSize == "Big") size = 5;

		cout << "Would you like to play Standard Boggle or Customized one?" << endl;
		cout << "Enter Standard or Customized" << endl;
		string gameType = getLine();
		while(true){
			if(gameType == "Standard" || gameType == "Customized") break;
			cout << "Enter Standard or Customized" << endl;
			gameType = getLine();
		}
		Vector<Vector<char> > boardL;

		if(gameType == "Standard"){
			Vector<string> cubes;
			for(int i = 0; i < size*size; i++){
				if(size == 4)cubes.push_back(STANDARD_CUBES[i]);
				if(size == 5)cubes.push_back(BIG_BOGGLE_CUBES[i]);
			}
			boardL = assembleBoard(cubes, size);
			drawBoard(size, size);
			for(int i = 0; i < size; i++){
				for (int k = 0; k < size; k++) {
					labelCube(i, k, boardL[i][k]);
				}
			}
		}else if(gameType == "Customized"){
			Vector<string> cubes = customized(size);
			boardL = assembleBoard(cubes, size);
			drawBoard(size, size);
			for(int i = 0; i < size; i++){
				for (int k = 0; k < size; k++) {
					labelCube(i, k, boardL[i][k]);
				}
			}
		}
		
		Set<string> playerWords;
		Set<string> computerWords;
		
		playerTurn(boardL, playerWords, dictionary, size);
		computerTurn(boardL, playerWords, computerWords, dictionary, size);
		cout << "Press enter if you would like to play again, else enter 'Exit'." << endl;
		string answer = getLine();
		if(answer == "Exit"){
			gw.close();
			break;
		}
	}
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]