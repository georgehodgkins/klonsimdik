#include <list>
// class representing manipulable game state
// Suit numbers: 0=spades, 1=clubs, 2=diamonds, 3=hearts

namespace klondiksim {

class game {

	private:
	// piles on the table
	std::list<int> piles[7];
	// backmost face-up card in each pile
	std::list<int>::iterator tops[7];
	// sequenced suits
	std::list<int> suits[4];
	// draw pile (face-down)
	std::list<int> draw;
	// push pile (face-up)
	std::list<int> push;
	// backmost available card in the push pile (for multi-draw variants)
	std::list<int>::iterator pushback;

	
	public:
	// constructor from a deck
	game(std::forward_list<int>);
	// pull from draw pile
	new_draw(int);
	// move card from draw to a pile
	draw_to_pile(int, int);
	// move card from draw to suits
	draw_to_suits(int);
	// move card(s) from pile to pile
	pile_to_pile(int, int, int);
	// move card from pile to suits
	pile_to_suits(int);
	// move card from suits to pile
	suits_to_pile(int, int);
};

/* Constructs a new game from an ordered set of card representations
 *
 * @param deal 52-element forward_list<int> containing every number 0-51 exactly once
 */
game::game(const std::forward_list<int>& deal) {
	
	// validate setup parameter to ensure that it contains every card once
	bool param_check[52] = {false};
	for (auto it = deal.begin(); it != deal.end(); ++it) {
		if (*it > 51) { // invalid entry in list
			throw std::invalid_argument("Invalid value in setup deck");
		} else if (param_check[*it]) { // number has already been seen
			throw std::invalid_argument("Multiple value in setup deck");
		} else { // value ok, check it off the list
			param_check[*it] = true;
		}
	}

	auto deal_it = deal.begin();
	
	// deal piles
	for (int p = 0; p < 7; ++p) {
	       for (int x = 0; x < p+1; ++x) {
		       piles[p].push_back(*deal_it);
		       ++deal_it;
	       }
	       tops[p] = piles[p].end();
	}

	// remainder goes to draw pile
	draw.insert(draw.end(), deal_it, deal.end());
}



