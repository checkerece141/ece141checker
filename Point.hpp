#ifndef Point_hpp
#define Point_hpp

#include  "stdio.h"
#include <vector>
#include "Piece.hpp"
#include "Player.hpp"
#include <math.h>
namespace ECE141 {
	class Point {
	public:
		static bool Jump(Game& aGame, Location& aLocation, const PieceColor aColor, const PieceKind aKind);
		static int TakenByOpponent(Game& aGame, Location aLocation, const PieceColor aColor);
		static bool Occupy(Game& aGame, Location aLocation, const PieceColor aColor);
		static int GetDeeper(Game& aGame, Location aLocation, const PieceColor aColor, const PieceKind aKind);
		static int StandBehind(Game& aGame, Location aLocation, const PieceColor aColor);
		static int PoliceAndThief(Game& aGame, Location aLocation, const PieceColor aColor);
		static Location GetNearstEnemy(Game& aGame, Location aLocation, const PieceColor aColor);
};
#pragma once



}
#endif /* Piece_hpp */
