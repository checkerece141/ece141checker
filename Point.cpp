#include "Game.hpp"
#include "Point.hpp"
using namespace std;
namespace ECE141 {
	bool Point::Jump(Game& aGame, Location& aLocation, const PieceColor aColor, const PieceKind aKind) {
		vector<Location> target;
		vector<Location> farTarget;
		if (aKind == PieceKind::king && aColor == PieceColor::blue) {
			target.push_back(Location(aLocation.row - 1, aLocation.col + 1));
			target.push_back(Location(aLocation.row - 1, aLocation.col - 1));
			target.push_back(Location(aLocation.row + 1, aLocation.col + 1));
			target.push_back(Location(aLocation.row + 1, aLocation.col - 1));
			farTarget.push_back(Location(aLocation.row - 2, aLocation.col + 2));
			farTarget.push_back(Location(aLocation.row - 2, aLocation.col - 2));
			farTarget.push_back(Location(aLocation.row + 2, aLocation.col + 2));
			farTarget.push_back(Location(aLocation.row + 2, aLocation.col - 2));
		}
		else if (aKind == PieceKind::pawn && aColor == PieceColor::blue) {
			target.push_back(Location(aLocation.row - 1, aLocation.col + 1));
			target.push_back(Location(aLocation.row - 1, aLocation.col - 1));
			farTarget.push_back(Location(aLocation.row - 2, aLocation.col + 2));
			farTarget.push_back(Location(aLocation.row - 2, aLocation.col - 2));
		}
		if (aKind == PieceKind::king && aColor == PieceColor::gold) {
			target.push_back(Location(7 - aLocation.row - 1, 7 - aLocation.col + 1));
			target.push_back(Location(7 - aLocation.row - 1, 7 - aLocation.col - 1));
			target.push_back(Location(7 - aLocation.row + 1, 7 - aLocation.col + 1));
			target.push_back(Location(7 - aLocation.row + 1, 7 - aLocation.col - 1));
			farTarget.push_back(Location(7 - aLocation.row - 2, 7 - aLocation.col + 2));
			farTarget.push_back(Location(7 - aLocation.row - 2, 7 - aLocation.col - 2));
			farTarget.push_back(Location(7 - aLocation.row + 2, 7 - aLocation.col + 2));
			farTarget.push_back(Location(7 - aLocation.row + 2, 7 - aLocation.col - 2));
		}
		else if (aKind == PieceKind::pawn && aColor == PieceColor::gold) {
			target.push_back(Location(7 - aLocation.row - 1, 7 - aLocation.col + 1));
			target.push_back(Location(7 - aLocation.row - 1, 7 - aLocation.col - 1));
			farTarget.push_back(Location(7 - aLocation.row - 2, 7 - aLocation.col + 2));
			farTarget.push_back(Location(7 - aLocation.row - 2, 7 - aLocation.col - 2));
		}
		if (aColor == PieceColor::blue) {
			for (int i = 0; i < target.size(); i++) {
				if ((Player::isValidLoc(target[i]) && Player::isValidLoc(farTarget[i]))) {
					if (aGame.getTileAt(target[i])->getPiece() != nullptr && (aGame.getTileAt(target[i])->getPiece()->getColor() == PieceColor::gold)) {
						if (aGame.getTileAt(farTarget[i])->getPiece() == nullptr) {
							aLocation = farTarget[i];
							return 1;
						}
					}
				}
			}
		}
		else if (aColor == PieceColor::gold) {
			for (int i = 0; i < target.size(); i++) {
				if ((Player::isValidLoc(target[i]) && Player::isValidLoc(farTarget[i]))) {
					if (aGame.getTileAt(target[i])->getPiece() != nullptr && (aGame.getTileAt(target[i])->getPiece()->getColor() == PieceColor::blue)) {
						if (aGame.getTileAt(farTarget[i])->getPiece() == nullptr) {
							aLocation.row = 7 - farTarget[i].row;
							aLocation.col = 7 - farTarget[i].col;
							return 1;
						}
					}
				}
			}
		}
		return 0;
	}

	int Point::GetDeeper(Game& aGame, Location aLocation, const PieceColor aColor, const PieceKind aKind) {
		Location front = aLocation;
		if (aKind == PieceKind::king)
			return front.row + (4 - abs(3 - front.col));
		if (aColor == PieceColor::blue) {
			front = aLocation;
		}
		else {
			front.row = 7 - aLocation.row;
			front.col = 7 - aLocation.col;
		}
		if (Player::isValidLoc(front)) {
			if (front.row == 0) {
				return 20;
			}
			else {
				return 7 - front.row + (4 - abs(3 - front.col));
			}
		}
		return 0;
	}
	Location Point::GetNearstEnemy(Game& aGame, Location aLocation, const PieceColor aColor){
		int Row = aLocation.row;
		int Col = aLocation.col;
		for (int i = 1; i < 8; i++) {
			for (int j = 0; j < 2 * i; j+=2) {
				Location a(Row - i + j, Col - i);
				Location b(Row + i, Col - i + j);
				Location c(Row + i - j, Col + i);
				Location d(Row - i, Col + i -j);
				if (Player::isValidLoc(a) && aGame.getTileAt(a)->getPiece() != nullptr && aGame.getTileAt(a)->getPiece()->getColor() != aColor) {
					cout << "hello" << endl;
					return a;
				}
				if (Player::isValidLoc(b) && aGame.getTileAt(b)->getPiece() != nullptr && aGame.getTileAt(b)->getPiece()->getColor() != aColor) {
					return b;
				}
				if (Player::isValidLoc(c) && aGame.getTileAt(c)->getPiece() != nullptr && aGame.getTileAt(c)->getPiece()->getColor() != aColor) {
					return c;
				}
				if (Player::isValidLoc(d) && aGame.getTileAt(d)->getPiece() != nullptr && aGame.getTileAt(d)->getPiece()->getColor() != aColor) {
					return d;
				}
			}
		}
		return aLocation;
    }
	int Point::PoliceAndThief(Game& aGame, Location aLocation, const PieceColor aColor) {
		if (aGame.countAvailablePieces(PieceColor::blue) > aGame.countAvailablePieces(PieceColor::gold)&& (aGame.countAvailablePieces(PieceColor::blue) + aGame.countAvailablePieces(PieceColor::gold))<10) {
			if (aColor == PieceColor::blue) {
				return (15-(abs(GetNearstEnemy(aGame, aLocation, aColor).col - aLocation.col)+abs((GetNearstEnemy(aGame, aLocation, aColor).row - aLocation.row))));
			}
			else {
				return 2*(abs(GetNearstEnemy(aGame, aLocation, aColor).col - aLocation.col) + abs((GetNearstEnemy(aGame, aLocation, aColor).row - aLocation.row))+ abs(3 - aLocation.col));
			}
		}
		else  if((aGame.countAvailablePieces(PieceColor::blue) + aGame.countAvailablePieces(PieceColor::gold)) < 10){
			if (aColor == PieceColor::gold) {
				int temp = (15 - (abs(GetNearstEnemy(aGame, aLocation, aColor).col - aLocation.col) + abs((GetNearstEnemy(aGame, aLocation, aColor).row - aLocation.row))));
				return  temp;
			}
			else {
				return 2*(abs(GetNearstEnemy(aGame, aLocation, aColor).col - aLocation.col) + abs((GetNearstEnemy(aGame, aLocation, aColor).row - aLocation.row))+ abs(3 - aLocation.col));
			}
		}
		return 0;
	}

	int Point::StandBehind(Game& aGame, Location aLocation, const PieceColor aColor) {
		vector<Location> target;
		vector<Location> farTarget;
		if (aColor == PieceColor::blue) {
			target.push_back(Location(aLocation.row - 1, aLocation.col + 1));
			target.push_back(Location(aLocation.row - 1, aLocation.col - 1));
			farTarget.push_back(Location(aLocation.row - 2, aLocation.col + 2));
			farTarget.push_back(Location(aLocation.row - 2, aLocation.col - 2));
		}
		else if ( aColor == PieceColor::gold) {
			target.push_back(Location(7 - aLocation.row - 1, 7 - aLocation.col + 1));
			target.push_back(Location(7 - aLocation.row - 1, 7 - aLocation.col - 1));
			farTarget.push_back(Location(7 - aLocation.row - 2, 7 - aLocation.col + 2));
			farTarget.push_back(Location(7 - aLocation.row - 2, 7 - aLocation.col - 2));
		}
		for (int i = 0; i < target.size(); i++) {
			if ((Player::isValidLoc(target[i]) && Player::isValidLoc(farTarget[i]))) {
				if (aGame.getTileAt(target[i])->getPiece() == nullptr) {
					if (aGame.getTileAt(farTarget[i])->getPiece() != nullptr && (aGame.getTileAt(farTarget[i])->getPiece()->getColor() == aColor)) {
						return 8;
					}
				}
			}
		}
		return 0;
	}

	int Point::TakenByOpponent(Game &aGame, Location aLocation, const PieceColor aColor) {
		vector<Location> front;
		vector<Location> behind;
		if (aColor == PieceColor::blue) {
			front.push_back(Location(aLocation.row - 1, aLocation.col + 1));
			front.push_back(Location(aLocation.row - 1, aLocation.col - 1));
			front.push_back(Location(aLocation.row + 1, aLocation.col + 1));
			front.push_back(Location(aLocation.row + 1, aLocation.col - 1));
			behind.push_back(Location(aLocation.row + 1, aLocation.col - 1));
			behind.push_back(Location(aLocation.row + 1, aLocation.col + 1));
			behind.push_back(Location(aLocation.row - 1, aLocation.col - 1));
			behind.push_back(Location(aLocation.row - 1, aLocation.col + 1));
		}
		else {
			front.push_back(Location(7-aLocation.row - 1, 7-aLocation.col + 1));
			front.push_back(Location(7-aLocation.row - 1, 7-aLocation.col - 1));
			front.push_back(Location(7-aLocation.row + 1, 7-aLocation.col + 1));
			front.push_back(Location(7-aLocation.row + 1, 7-aLocation.col - 1));
			behind.push_back(Location(7-aLocation.row + 1, 7-aLocation.col - 1));
			behind.push_back(Location(7-aLocation.row + 1, 7-aLocation.col + 1));
			behind.push_back(Location(7-aLocation.row - 1, 7-aLocation.col - 1));
			behind.push_back(Location(7-aLocation.row - 1, 7-aLocation.col + 1));
		}
		for (int i = 0; i < front.size(); i++) {
			if (Player::isValidLoc(front[i]) && Player::isValidLoc(behind[i])) {
				if (i<=1&& (aGame.getTileAt(front[i])->getPiece()!=nullptr) &&(aGame.getTileAt(front[i])->getPiece()->getColor() != aColor) && (aGame.getTileAt(behind[i])->getPiece() == nullptr)) {
					return -15;
				}
				else if (i > 1 && (aGame.getTileAt(front[i])->getPiece() != nullptr) &&(aGame.getTileAt(front[i])->getPiece()->getKind()==PieceKind::king) && (aGame.getTileAt(front[i])->getPiece()->getColor() != aColor) && (aGame.getTileAt(behind[i])->getPiece() == nullptr)) {
					return -15;
				}
			}
		}
		return 0;
	}
	
	bool Point::Occupy(Game& aGame, Location aLocation, const PieceColor aColor) {
		Location temp(7 - aLocation.row, 7 - aLocation.col);
		if (aColor == PieceColor::blue) {
			if (aGame.getTileAt(aLocation)->getPiece() != nullptr)
				return true;
			else
				return false;
		}
		else {
			if (aGame.getTileAt(temp)->getPiece() != nullptr)
				return true;
			else
				return false;
		}
	}
}
