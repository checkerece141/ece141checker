//
//  Player.hpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include "Point.hpp"
#include "Piece.hpp"
#include <iostream>
namespace ECE141 {

	class Game; //forward declare...  

	class Player {
	public:
		Player();
		virtual bool      takeTurn(Game& aGame, Orientation aDirection, std::ostream& aLog);
		const PieceColor  color;
		static int        pcount; //how many created so far?
		static bool isValidLoc(Location aLoc);
	};

	class YuxiPlayer :public Player {
		virtual bool takeTurn(Game& aGame, Orientation aDirection, std::ostream& aLog);
	};
}



#endif /* Player_hpp */
