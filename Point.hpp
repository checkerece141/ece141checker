#ifndef Point_hpp
#define Point_hpp

#include  "stdio.h"
#include <vector>
#include "Piece.hpp"
#include "Player.hpp"
namespace ECE141 {
	class Point {
	public:
		static bool Jump(Game& aGame, Location& aLocation, const PieceColor aColor, const PieceKind aKind);
		static int TakenByOpponent(Game& aGame, Location aLocation, const PieceColor aColor);
		static bool Occupy(Game& aGame, Location aLocation, const PieceColor aColor);
};
#pragma once



}
#endif /* Piece_hpp */
