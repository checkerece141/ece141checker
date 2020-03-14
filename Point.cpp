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
		else if(aKind == PieceKind::pawn && aColor == PieceColor::blue){
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
		Location LocTempa(aLocation.row - 1, aLocation.col + 1);
		Location LocTempb(aLocation.row - 1, aLocation.col - 1);
		Location LocTempc(7-(aLocation.row + 1), 7-(aLocation.col + 1));
		Location LocTempd(7-(aLocation.row + 1), 7-(aLocation.col - 1));
		Location LocTempa2(aLocation.row - 2, aLocation.col + 2);
		Location LocTempb2(aLocation.row - 2, aLocation.col - 2);
		Location LocTempc2(7-(aLocation.row + 2), 7-(aLocation.col + 2));
		Location LocTempd2(7-(aLocation.row + 2), 7-(aLocation.col - 2));
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
						cout << (aGame.getTileAt(target[i])->getPiece()->getColor() == PieceColor::gold) << endl;
						if (aGame.getTileAt(farTarget[i])->getPiece() == nullptr) {
							aLocation.row = 7 - farTarget[i].row;
							aLocation.col = 7 - farTarget[i].col;
							return 1;
						}
					}
				}
			}
			if ((Player::isValidLoc(LocTempc) && Player::isValidLoc(LocTempc2))) {
				if (aGame.getTileAt(LocTempc)->getPiece()!=nullptr&& (aGame.getTileAt(LocTempc)->getPiece()->getColor()==PieceColor::blue)) {
					cout <<(aGame.getTileAt(LocTempc)->getPiece()->getColor()==PieceColor::gold)<<endl;
					if (aGame.getTileAt(LocTempc2)->getPiece() == nullptr) {
						aLocation.row = 7 - LocTempc2.row;
						aLocation.col = 7 - LocTempc2.col;
						return 1;
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
			front.push_back(Location(7-aLocation.row + 1, 7-aLocation.col + 1));
			front.push_back(Location(7-aLocation.row + 1, 7-aLocation.col - 1));
			front.push_back(Location(7-aLocation.row - 1, 7-aLocation.col + 1));
			front.push_back(Location(7-aLocation.row - 1, 7-aLocation.col - 1));
			behind.push_back(Location(7-aLocation.row - 1, 7-aLocation.col - 1));
			behind.push_back(Location(7-aLocation.row - 1, 7-aLocation.col + 1));
			behind.push_back(Location(7-aLocation.row + 1, 7-aLocation.col - 1));
			behind.push_back(Location(7-aLocation.row + 1, 7-aLocation.col + 1));
		}
		for (int i = 0; i < front.size(); i++) {
			if (Player::isValidLoc(front[i]) && Player::isValidLoc(behind[i])) {
				if (i<=1&& (aGame.getTileAt(front[i])->getPiece()!=nullptr) &&(aGame.getTileAt(front[i])->getPiece()->getColor() != aColor) && (aGame.getTileAt(behind[i])->getPiece() == nullptr)) {
					return -10;
				}
				else if (i > 1 && (aGame.getTileAt(front[i])->getPiece() != nullptr) &&(aGame.getTileAt(front[i])->getPiece()->getKind()==PieceKind::king) && (aGame.getTileAt(front[i])->getPiece()->getColor() != aColor) && (aGame.getTileAt(behind[i])->getPiece() == nullptr)) {
					return -10;
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