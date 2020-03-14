//
//  Player.cpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Player.hpp"
#include "Game.hpp"

using namespace std;
namespace ECE141 {
  
  int Player::pcount = 0; //init our static member to track # of players...
  
  static PieceColor autoColor() { //auto assigns a color
    return (++Player::pcount % 2) ? PieceColor::blue : PieceColor::gold;
  }
  
  Player::Player() : color(autoColor()) {}
 
  bool Player::isValidLoc(Location aLoc) {
	  if (aLoc.col < 8 && aLoc.row < 8 && aLoc.col >= 0 && aLoc.row >= 0)
		  return true;
	  else
		  return false;
  }
  bool Player::takeTurn(Game& aGame, Orientation aDirection, std::ostream& aLog) {
	  return false;
  }
  bool YuxiPlayer::takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog) {
	  /*for (int i = 0; i < 8; i++) {
		  cout << i << " ";
	  }
	  cout << endl;
	  for (int i = 0; i < 8; i++) {
		  for (int j = 0; j < 8; j++) {
			  Location visual(i, j);
			  if((aGame.getTileAt(visual)->getPiece()==nullptr))
				  cout<<"0 ";
			  else if ((aGame.getTileAt(visual)->getPiece()->getColor() == PieceColor::blue))
				  cout << "B ";
			  else if ((aGame.getTileAt(visual)->getPiece()->getColor() == PieceColor::gold))
				  cout << "G ";
		  }
		  cout << endl;
	  }*/
    size_t theCount=aGame.countAvailablePieces(color);
	Location bestLoc(-1,-1);
	int bestScore = -100;
	Piece* thatPiece;
		for (int pos = 0; pos < theCount; pos++) {
			//NOTICE HOW WE CHECK FOR CAPTURED PIECES?
			if (const Piece* thePiece = aGame.getAvailablePiece(this->color, pos)) {
				Location PieceLoc = thePiece->getLocation();
				PieceKind kind = thePiece->getKind();
				vector<Location> target;
				if (kind == PieceKind::king) {
					target.push_back(Location(PieceLoc.row - 1, PieceLoc.col + 1));
					target.push_back(Location(PieceLoc.row - 1, PieceLoc.col - 1));
					target.push_back(Location(PieceLoc.row + 1, PieceLoc.col + 1));
					target.push_back(Location(PieceLoc.row + 1, PieceLoc.col - 1));
				}
				else if (color == PieceColor::blue) {
					target.push_back(Location(PieceLoc.row - 1, PieceLoc.col + 1));
					target.push_back(Location(PieceLoc.row - 1, PieceLoc.col - 1));
				}
				else {
					target.push_back(Location(PieceLoc.row + 1, PieceLoc.col + 1));
					target.push_back(Location(PieceLoc.row + 1, PieceLoc.col - 1));
				}
				vector<int> score(4, 0); 
				if (color == PieceColor::blue) {
					Location tempLoc(PieceLoc);
					bool isJump = 0;
					while (Point::Jump(aGame, tempLoc, color, kind)) {
						isJump = 1;
						cout << "Move Jump: " << PieceLoc.row << " " << PieceLoc.col << " to " << tempLoc.row << " " << tempLoc.col << endl;
						aGame.movePieceTo(*thePiece, tempLoc);
					}
					if (isJump == 1)
						return true;
					int index = 0;
					for (auto x : target) {
						if (isValidLoc(x) && !Point::Occupy(aGame, x, color)) {
							cout << "Move from: " << PieceLoc.row << " " << PieceLoc.col << " to " << x.row << " " << x.col << endl;
							score[index] += Point::TakenByOpponent(aGame, x, color);
							index++;
							cout << "Get Caught? " << Point::TakenByOpponent(aGame, x, color) << endl;
							aGame.movePieceTo(*thePiece, x);
							return true;
						}
					}
				}
					if (color == PieceColor::gold) {
						Location tempLoc(PieceLoc);
						bool isJump = 0;
						while (Point::Jump(aGame, tempLoc, color, kind)) {
							isJump = 1;
							cout << "Move Jump: " << PieceLoc.row << " " << PieceLoc.col << " to " << tempLoc.row << " " << tempLoc.col << endl;
							aGame.movePieceTo(*thePiece, tempLoc);
						}
						if (isJump == 1)
							return true;
						for (auto x : target) {
							if (isValidLoc(x) && !Point::Occupy(aGame, x, color)) {
								cout << "Move from: " << PieceLoc.row << " " << PieceLoc.col << " to " << x.row << " " << x.col << endl;
								cout << "Get Caught? " << Point::TakenByOpponent(aGame, x, color) << endl;
								aGame.movePieceTo(*thePiece, x);
								return true;
							}
						}
					}
				}
	    }
    return false; //if you return false, you forfeit!
  }
}
