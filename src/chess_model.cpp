#include "chess_model.hpp"
#include "board_position.hpp"
#include <sstream>
#include <string>
#include <utility>

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

ChessBoard& ChessModel::getBoard()
{
    return _board;
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

    if (!m.captured.has_value() && m.primaryPiece->getType() != PieceType::Pawn)
        _halfMoves++;
    else
        // Reset if a pawn is advanced or capture has been made
        _halfMoves = 0;

    if (_currentTurn == Color::Black)
        _fullMoves++;

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

void ChessModel::setTurn(Color c)
{
    _currentTurn = c;
}

std::string ChessModel::getFEN()
{
    // FEN notation encodes the state of a chessboard into a single string
    // It consists of 6 parts:
    // 1. Position of pieces on the board, forward-slash separated ranks of pieces, white pieces in
    // uppercase and black in lowercase
    // 2. "to move" which side is the next to move, either w (white) or b (black)
    // 3. Castling availability, KQkq for example says that all both sides can castle to king and queen side
    // 4. En passant, if an en passant target square is available that will be encoded with usual chess notation ex "d4"
    // 5. Halfmoves since last advancement of a pawn or capture of a piece
    // 6. Fullmoves increment after each move by black
    std::string boardState = "";
    std::string toMove, castling, enPassantTarget, halfMoves, fullMoves;
    
    for (int i = 0; i < 8; i++)
    {
        int empty = 0;
        for (int j = 0; j < 8; j++)
        {
            auto piece = _board[i][j];
            if (piece)
            {
                if (empty != 0)  
                {
                    boardState += std::to_string(empty);
                    empty = 0;
                }
                char sym = pieceToSymbol(piece);
                boardState += sym;
            }
            else
            {
                empty++;
                if (empty == 8) 
                {
                    boardState += std::to_string(empty);
                }
                else if (j == 7 && empty != 0)
                {
                    boardState += std::to_string(empty);
                }
            }
        }
        if (i != 7) boardState += '/';

    }

    // Set toMove
    if (_currentTurn == Color::White) toMove = "w";
    else toMove = "b";

    // Set castling
    std::string wk, wq, bk, bq;
    auto wKing = _board.at(BoardPosition{4, 7});
    auto leftWRook = _board.at(BoardPosition{0, 7});
    auto rightWRook = _board.at(BoardPosition{7, 7});

    auto bKing = _board.at(BoardPosition{4, 0});
    auto leftBRook = _board.at(BoardPosition{0, 0});
    auto rightBRook = _board.at(BoardPosition{7, 0});

    if (wKing && wKing->getTimesMoved() == 0)
    {
        // King side castling
        if (rightWRook && rightWRook->getTimesMoved() == 0)
            wk = "K";
        else
            wk = "-";
        // Queen side castling
        if (leftWRook && leftWRook->getTimesMoved() == 0)
            wq = "Q";
        else
            wq = "-";
    }
    else
    {
        wk = "-";
        wq = "-";
    }

    if (bKing && bKing->getTimesMoved() == 0)
    {
        // King side castling
        if (rightBRook && rightBRook->getTimesMoved() == 0)
            bk = "k";
        else
            bk = "-";
        // Queen side castling
        if (leftBRook && leftBRook->getTimesMoved() == 0)
            bq = "q";
        else
            bq = "-";
    }
    else 
    {
        bk = "-";
        bq = "-";
    }

    castling = wk + wq + bk + bq;

    // En passant
    auto enPTarget = _board.getEnPassantTarget();
    if (enPTarget.has_value()) enPassantTarget = BoardPosition::positionToNotation(enPTarget.value());
    else enPassantTarget = "-";

    return boardState + " " + 
           toMove + " " + 
           castling + " " + 
           enPassantTarget + " " + 
           std::to_string(getHalfMoves()) + " " + 
           std::to_string(getFullMoves());
}

void ChessModel::loadFEN(const std::string& fenString)
{
    std::string boardLayout, toMove, castling, enPassant;
    unsigned int halfMoves, fullMoves;

    ChessBoard board;
    board.clear();

    std::istringstream iss(fenString);
    iss >> boardLayout >> toMove >> castling >> enPassant >> halfMoves >> fullMoves;

    // Extract each rank of the board layout to a vector
    std::vector<std::string> ranks;
    std::stringstream ss(boardLayout);
    std::string row;
    while(std::getline(ss, row, '/'))
    {
        ranks.push_back(row);
    }

    for (int rank = 0; rank < 8; ++rank) {
        const std::string& rowStr = ranks[rank];
        int file = 0; // column index

        for (char c : rowStr) {
            if (std::isdigit(c)) {
                file += c - '0'; // skip empty squares
            } else {
                Color color = std::isupper(c) ? Color::White : Color::Black;
                PieceType type = charToPieceType(std::tolower(c));
                board.place(type, color, BoardPosition(file, rank));
                ++file;
            }
        }
    }

    // Set toMove
    if (toMove == "w") setTurn(Color::White);
    else setTurn(Color::Black);
    
    // Set castling
    char lwr, rwr, lbr, rbr;
    rwr = castling[0];
    lwr = castling[1];
    lbr = castling[2];
    rbr = castling[3];

    if (rwr == '-')
    {
        auto piece = _board.at("h8");
        if (piece && piece->getType() == PieceType::Rook)
            piece->incrementMoved();
    }
    if (lwr == '-')
    {
        auto piece = _board.at("a8");
        if (piece && piece->getType() == PieceType::Rook)
            piece->incrementMoved();
    }
    if (rbr == '-')
    {
        auto piece = _board.at("h1");
        if (piece && piece->getType() == PieceType::Rook)
            piece->incrementMoved();
    }
    if (lbr == '-')
    {
        auto piece = _board.at("a1");
        if (piece && piece->getType() == PieceType::Rook)
            piece->incrementMoved();
    }

    // Set enpassant
    if (enPassant != "-")
        board.setEnPassantTarget(BoardPosition::notationToPosition(enPassant));


    setHalfMoves(halfMoves);
    setFullMoves(fullMoves);

    _board = board;
}

unsigned int ChessModel::getHalfMoves() const
{
    return _halfMoves;
}

unsigned int ChessModel::getFullMoves() const
{
    return _fullMoves;
}

void ChessModel::setHalfMoves(unsigned int val)
{
    _halfMoves = val;
}

void ChessModel::setFullMoves(unsigned int val)
{
    _fullMoves = val;
}
// ========= Private =============

void ChessModel::toggleTurn()
{
    _currentTurn = (_currentTurn == Color::White) ? Color::Black : Color::White;
}


char ChessModel::pieceToSymbol(std::shared_ptr<Piece> p)
{
    if (p->getColor() == Color::White)
    {
        switch (p->getType())
        {
            case PieceType::Pawn: return 'P';
            case PieceType::Rook: return 'R';
            case PieceType::Knight: return 'N';
            case PieceType::Bishop: return 'B';
            case PieceType::Queen: return 'Q';
            case PieceType::King: return 'K';
        }
    }
    else
    {
        switch (p->getType())
        {
            case PieceType::Pawn: return 'p';
            case PieceType::Rook: return 'r';
            case PieceType::Knight: return 'n';
            case PieceType::Bishop: return 'b';
            case PieceType::Queen: return 'q';
            case PieceType::King: return 'k';
        }
    }
}

PieceType ChessModel::charToPieceType(char c)
{
    switch (c)
    {
        case 'p': return PieceType::Pawn;
        case 'n': return PieceType::Knight;
        case 'b': return PieceType::Bishop;
        case 'r': return PieceType::Rook;
        case 'q': return PieceType::Queen;
        case 'k': return PieceType::King;
        default: throw std::invalid_argument("Unknown piece character");
    }
}
