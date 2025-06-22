#include "engine_controller.hpp"
#include <random>

Move EngineController::chooseMove(std::vector<Move>& legalMoves, ChessBoard& board)
{
    std::cout << "Engine chooseing move" << std::endl;
    // Store the move and the evaluation score when executed
    std::vector<std::pair<size_t, int>> scoredMoves;
    int score;
    // A little hacky, gets which color that the engine is playing for
    Color color = legalMoves[0].primaryPiece->getColor();
    
    size_t index = 0;
    for (auto& move : legalMoves)
    {
        board.executeMove(move);
        // Evalutate the board with the move executed

        // Evalutes the board solely based on material present
        score = materialEvalutation(board);

        // Evalutes based on piece placement


        scoredMoves.push_back(std::pair(index, score));
        board.undoMove(move);

        ++index;
    }
    
    if (color == Color::White)
    {
        // Maximize score for white
        std::sort(scoredMoves.begin(), scoredMoves.end(),
                  [](const std::pair<size_t, int>& a, const std::pair<size_t, int>& b) 
        {
            return a.second > b.second;
        });

    }
    else
    {
        // Minimize score for black 
        std::sort(scoredMoves.begin(), scoredMoves.end(),
                  [](const std::pair<size_t, int>& a, const std::pair<size_t, int>& b) 
        {
            return a.second < b.second;
        });
    }

    std::vector<std::pair<size_t, int>> topScores;
    int topScore = scoredMoves[0].second;
    
    for (auto& pair: scoredMoves)
    {
        if (pair.second == topScore) topScores.push_back(pair);
        else break;
    }

    // Pick a random of the top scoring moves
    auto size = topScores.size(); 
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, size - 1); // Uniform range [0, n-1]
    
    std::cout << "Engine found: " << topScores.size() << "/" << legalMoves.size() << 
                 " moves with the same score: " << topScores[0].second << std::endl;
    return legalMoves[topScores[distrib(gen)].first];
}

// =============== PRIVATE ==================
int EngineController::materialEvalutation(ChessBoard& board)
{
    int score = 0;
    for (auto it = board.begin(); it != board.end(); ++it) 
    {
        auto piece = *it;
        if (piece)
        {
            int val = pieceValue(piece);
            score += (piece->getColor() == Color::White) ? val : -val;
        }
    }
    return score;
}

int EngineController::pieceValue(std::shared_ptr<Piece> piece)
{
    switch (piece->getType())
    {
        case PieceType::Pawn: return 100;
        case PieceType::Knight: return 320;
        case PieceType::Bishop: return 330;
        case PieceType::Rook: return 500;
        case PieceType::Queen: return 900;
        case PieceType::King: return 20000;
        default: return 0;
    }
}
