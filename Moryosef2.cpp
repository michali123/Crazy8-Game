#include <iostream>
#include <cstdlib>
#include <ctime>    // Enables use of time() function
#include <vector>
#include <algorithm>
using namespace std;

class Card {
	int number; // 1-13

	char suit; //Spades, Clubs, Diamonds, Hearts

public:
	Card(const char s = 'S', const int n = 0) { // Constructor
		suit = s;
		number = n;
	}
	char getSuit() {
		return suit;
	}
	int getNumber() {
		return number;
	}
	friend ostream& operator<<(ostream&, const Card&);
};

ostream& operator<<(ostream& o, const Card& c) {
	o << c.suit;
	switch (c.number) {
	case 1:
		o << 'A';
		break; // Replaces 1 w/ A
	case 11:
		o << 'J';
		break; // Replaces 11 w/ J
	case 12:
		o << 'Q';
		break; // Replaces 12 w/ Q
	case 13:
		o << 'K';
		break; // Replaces 13 w/ K
	default:
		o << c.number; // Everything between 2 and 10 is the same
	}
	return o;
}

class Player {
	string m_name;
public:
	vector<Card> m_deck; //hand
	Player(const string& n = "") :
			m_name(n) {
		m_deck.reserve(6);
	}
	void push_back(const Card& c) {
		m_deck.push_back(c);
	}
	int numCardsInHand() {
		return m_deck.size();
	}
	friend ostream& operator<<(ostream&, const Player& p);
};

ostream& operator<<(ostream& o, const Player& p) {
	char letter = 'a';
	for (int i = 0, len = p.m_deck.size(); i < len; ++i) {
		o << "(" << letter << ")" << " " << p.m_deck[i] << " ";
		++letter;
	}
	o << "(z) draw" << endl;
	return o;
}

int main() {
	vector<Card> deck;
	for (int i = 1; i <= 13; ++i) {
		deck.push_back(Card('S', i)); // Populates the vector w/ Spades
	}
	for (int i = 1; i <= 13; ++i) {
		deck.push_back(Card('C', i)); // Populates the vector w/ Clubs
	}
	for (int i = 1; i <= 13; ++i) {
		deck.push_back(Card('D', i)); // Populates the vector w/ Diamonds
	}
	for (int i = 1; i <= 13; ++i) {
		deck.push_back(Card('H', i)); // Populates the vector w/ Hearts
	}
	srand(time(0));
	random_shuffle(deck.begin(), deck.end()); //Randomly shuffles the deck

	vector<Player> players; // Populates the vector w/ amount of players
	players.push_back(Player("You"));
	players.push_back(Player("Player1"));
	players.push_back(Player("Player2"));
	players.push_back(Player("Player3"));

	for (int i = 0, len = players.size(); i < len; ++i) { //Gives each player a hand
		for (int j = 0; j < 6; ++j) { // Gives each player 6 cards
			Card c = deck.back();
			players[i].push_back(c);
			deck.pop_back();
		}
	}
	cout << "Pile has " << deck.back() << " <--- your turn" << endl; //first card in pile
	cout << endl;

	char choice, position = 'a', yes_no;
	vector<Card> top;
	int i = 0;
	bool win = false;
	while ((!win) || (deck.size() != 0)) {
		cout << players[i] << endl;
		cout << "Which one to play? press 'z' to draw " << endl;
		cin >> choice;
		if (choice == '?') {
			cout << "Player 1" << players[1] << endl;
			cout << "Player 2" << players[2] << endl;
			cout << "Player 3" << players[3] << endl;
			cout << "Which one to play? press 'z' to draw " << endl;
			cin >> choice;
		}
		unsigned int j = 0;
		for (j = 0; j <= players[j].m_deck.size(); ++j) { //checking my hand
			if (choice == position) {
				cout << "Pile has " << players[0].m_deck.at(j) << endl;
				top.push_back(players[0].m_deck.at(j));
				players[0].m_deck.erase(players[0].m_deck.begin() + j);
				if (players[j].m_deck.size() == 0) {
					cout << "you won!" << endl;
					win = true;
					break;
				}
				break;
			} else
				position++;

			if (choice == 'z') { //if player chose to draw
				players[0].m_deck.push_back(deck.back());
				deck.pop_back();
				cout << "Your pile: \n" << players[0] << endl;
				cout << "draw again? type 'y' for yes or any letter if no. ";
				cin >> yes_no;
				while (yes_no == 'y') {
					players[0].m_deck.push_back(deck.back());
					deck.pop_back();
					cout << "Your pile" << endl;
					cout << players[0];
					cout << "draw again? type 'y' for yes or any letter if no. "
							<< endl;
					cin >> yes_no;
				}
				cout << "Which card you play with?" << endl;
				cin >> choice;
			}

		}

		for (unsigned int count_player = 1; count_player < players.size();
				++count_player) {
			int unsigned h = 0;
			bool found = false; //as long as player hasn't put down a card
			/*cout << "Player" << count_player << " has"<< endl;
			 for (int i = 0 ; i < players[count_player].m_deck.size() ; i++){
			 cout << players[count_player].m_deck.at(i) << " " ;
			 }*/
			cout << endl;
			while ((h != players[count_player].m_deck.size() - 1) && (!found)) {
				if (players[count_player].m_deck.at(h).getNumber() == 8) { //if player has crazy 8
					top.push_back(players[count_player].m_deck.at(h));
					cout << "Player " << count_player << " chose "
							<< players[count_player].m_deck.at(h) << endl;
					players[count_player].m_deck.erase(
							players[count_player].m_deck.begin() + h);
					if (players[count_player].m_deck.size() == 0) {
						cout << "Player" << count_player << " won." << endl;
						win = true;
						break;
					}
					int D, H, C, S;
					for (int g = 0; g < players[count_player].numCardsInHand();
							++g) { //checking what suite player has the most
						if (players[count_player].m_deck.at(g).getSuit() == 'D')
							D++;
						if (players[count_player].m_deck.at(g).getSuit() == 'H')
							H++;
						if (players[count_player].m_deck.at(g).getSuit() == 'C')
							C++;
						if (players[count_player].m_deck.at(g).getSuit() == 'S')
							S++;
					}
					if ((D > H) && (D > C) && (D > S)) {
						cout << "Player " << count_player << " declared suite D"
								<< endl;
						cout << "Pile has D*" << endl;
					} else if ((H > D) && (H > S) && (H > C)) {
						cout << "Player " << count_player << " declared suite H"
								<< endl;
						cout << "Pile has H*" << endl;
					} else if ((C > H) && (C > S) && (C > D)) {
						cout << "Player " << count_player << " declared suite C"
								<< endl;
						cout << "Pile has C*" << endl;
					} else if ((S > H) && (S > C) && (S > D)) {
						cout << "Player " << count_player << " declared suite S"
								<< endl;
						cout << "Pile has S*" << endl;
					} else { // if there is no highest suite player declares his crazy 8 suite.
						cout << "Player " << count_player << " declared suite"
								<< top.back().getSuit() << endl;
						cout << "Pile has " << top.back().getSuit() << "*"
								<< endl;
					}
					found = true;
				}
				h++;
			}
			h = 0;
			// if player doesn't have crazy 8 in his deck
			while ((!found) && (deck.size() > 0)) {
				if (top.back().getNumber()
						== players[count_player].m_deck.at(h).getNumber()) { //if player has the same number
					top.push_back(players[count_player].m_deck.at(h)); //putting card on the pile
					cout << "Player " << count_player << " chose "
							<< players[count_player].m_deck.at(h) << endl;
					if (players[count_player].m_deck.size() == 0) {
						cout << "Player" << count_player << " won." << endl;
						win = true;
						break;
					}
					players[count_player].m_deck.erase(
							players[count_player].m_deck.begin() + h); //erasing card from player's hand
					cout << "Pile has " << top.back() << endl;
					found = true;

				}
				if (top.back().getSuit()
						== players[count_player].m_deck.at(h).getSuit()) { //if player has the same suite
					top.push_back(players[count_player].m_deck.at(h)); //putting card on the pile
					cout << "Player " << count_player << " chose "
							<< players[count_player].m_deck.at(h) << endl;
					players[count_player].m_deck.erase(
							players[count_player].m_deck.begin() + h); //erasing card from player's hand
					if (players[count_player].m_deck.size() == 0) {
						cout << "Player" << count_player << " won." << endl;
						win = true;
						break;
					}
					cout << "Pile has " << top.back() << endl;
					found = true;
				}
				if ((!found)
						&& (h == players[count_player].m_deck.size() - 1)) { //player draws card from pile and puts a card on pile
					players[count_player].m_deck.push_back(deck.back());
					deck.pop_back();
					cout << "Player " << count_player << " is drawing... "
							<< endl;
				}
				if (deck.size() == 0) {
					cout << "Game ended, all deck cards are used" << endl;
					break;
				}
				h++;
			}
			h = 0;
		}
	}

	cout << "[ Final card distributions ]" << endl;
	for (int i = 0; i < 4; i++) {
		for (unsigned int l = 0; l < players[i].m_deck.size(); l++) {
			cout << "Player " << i << "    " << players[i] << endl;
		}
	}
	return 0;
}

