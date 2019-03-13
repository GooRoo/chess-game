#pragma once

#include "Chess/Board.hpp"

namespace chess
{
	class IBoardObserver
	{
	public:
		virtual ~IBoardObserver() = 0 {}

		virtual void onSubscribed(Board * /*board*/) {}
		virtual void onInitialized() {}
		virtual void onTurnChange(Color /*color*/) {}
		virtual void onSuccessMove(Step /*step*/, const Transition &) {}
	};

}
