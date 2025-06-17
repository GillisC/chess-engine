#include "engine_controller.hpp"
#include <random>

Move EngineController::chooseMove(std::vector<Move>& legalMoves, ChessBoard& board) const
{
   // For now just make a random move
    auto size = legalMoves.size(); 
   static std::random_device rd;
   static std::mt19937 gen(rd());
   std::uniform_int_distribution<> distrib(0, size - 1); // Uniform range [0, n-1]

   return legalMoves[distrib(gen)];
}
