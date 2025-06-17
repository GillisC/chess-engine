#include "chess_model.hpp"

ChessModel::ChessModel() : 
    _owned_board(), _board(_owned_board) 
{
    controllers[Color::White] = std::make_unique<HumanController>();
    controllers[Color::Black] = std::make_unique<EngineController>();
}

ChessModel::ChessModel(ChessBoard& board) :
    _board(board) 
{
    controllers[Color::White] = std::make_unique<HumanController>();
    controllers[Color::Black] = std::make_unique<HumanController>();
}

std::shared_ptr<Piece> ChessModel::atBoardPosition(const BoardPosition& pos)
{
    return _board.at(pos);
}

bool ChessModel::isPiece(const BoardPosition& pos)
{
    return _board.at(pos) != nullptr;
}

std::vector<Move> ChessModel::getMoves(const BoardPosition& pos)
{
    if (!_board.isPiece(pos))
    {
        return {};
    }
    std::vector<Move> possibleMoves = atBoardPosition(pos)->getValidMoves(_board, pos);

    std::vector<Move> validMoves = {};
    auto current = _currentTurn;

    // Filter out moves which lead to the king in check
    for (auto& move : possibleMoves)
    {
        _board.executeMove(move);
        if (!_board.isKingInCheck(current)) validMoves.push_back(move);
        _board.undoMove(move);
    }
    return validMoves;
}

std::vector<Move> ChessModel::getAllLegalMoves(Color color)
{
    std::vector<Move> legalMoves;

    for (auto it = _board.begin(); it != _board.end(); ++it)
    {
        auto square = *it;
        auto pos = it.position();

        if (square != nullptr && square->getColor() == color)
        {
            auto moves = getMoves(pos);
            for (Move m : moves)
            {
                legalMoves.push_back(m);
            }
        }
    }
    return legalMoves;
}

void ChessModel::executeMove(const Move m)
{
    _board.executeMove(m);
    toggleTurn();
    startTurn();
}

void ChessModel::startTurn()
{
    // Get the current controller
    auto& currentController = controllers[_currentTurn];
    
    if (currentController->type() == ControllerType::Engine)
    {
        auto legalMoves = getAllLegalMoves(_currentTurn);
        Move move = currentController->chooseMove(legalMoves, _board);
        executeMove(move);
    }
}

void ChessModel::movePiece(const BoardPosition& from, const BoardPosition& to)
{
    _board.move(from, to);
    toggleTurn();
}


Color ChessModel::getTurn()
{
    return _currentTurn;
}

// ========= Private =============

void ChessModel::toggleTurn()
{
    _currentTurn = (_currentTurn == Color::White) ? Color::Black : Color::White;
}



