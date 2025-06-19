#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "board.hpp"
#include "chess_model.hpp"

TEST_CASE("Pawn movement", "[pawn][movement]")
{
    ChessBoard board;
    board.clear();
    board.place(PieceType::Pawn, Color::White, "a7");
    auto piece = board.at(BoardPosition{0, 6});

    SECTION("Correctly placed")
    {
        REQUIRE(piece != nullptr);
    }
    SECTION("Has two valid moves")
    {
        REQUIRE(piece->getValidMoves(board, {0, 6}).size() == 2);
    }
}

TEST_CASE("Successful castling", "[king][rook][movement]")
{
    ChessBoard board;
    board.clear();

    board.place(PieceType::King, Color::White, "e8");
    board.place(PieceType::Rook, Color::White, "a8");
    board.place(PieceType::Rook, Color::White, "h8");

    REQUIRE(board.at({4, 7})->getType() == PieceType::King);
    REQUIRE(board.at(BoardPosition{0, 7})->getType() == PieceType::Rook);
    REQUIRE(board.at({7, 7})->getType() == PieceType::Rook);
    REQUIRE(!board.at({4, 6}));

    auto king = board.at({4, 7});
    if (!king) std::cout << "king is null" << std::endl;
    std::vector<Move> moves = king->getValidMoves(board, {4, 7});
    REQUIRE(moves.size() == 7);
}

TEST_CASE("Undo Moves", "[move]")
{
    ChessBoard board;
    board.clear();

    board.place(PieceType::Pawn, Color::White, "b6");
    Move move(
        ChessBoard::convertNotation("b6"),
        ChessBoard::convertNotation("b5"),
        board
    );
    board.executeMove(move);
    REQUIRE(board.at("b5") != nullptr);
    REQUIRE(board.at("b6") == nullptr);

    board.undoMove(move);
    REQUIRE(board.at("b5") == nullptr);
    REQUIRE(board.at("b6") != nullptr);
    REQUIRE(board.at("b6")->getTimesMoved() == 0);
}

TEST_CASE("Check works", "[king][move-generation]")
{
    ChessBoard board;
    board.clear();
    ChessModel model(board);

    board.place(PieceType::King, Color::White, "d6");
    board.place(PieceType::Rook, Color::Black, "f6");
    auto piece = board.at("d6");
    REQUIRE(piece != nullptr);
    REQUIRE(board.isKingInCheck(Color::White));

    auto validMoves = model.getMoves(ChessBoard::convertNotation("d6"));
    std::cout << "model valid king moves: " << validMoves.size() << std::endl;
    REQUIRE(validMoves.size() == 6);
    // REQUIRE(piece->getValidMoves(board, ChessBoard::convertNotation("d6")).size() == 6);
}

TEST_CASE("Export game state using FEN", "[backend][fen]")
{
    ChessModel model;
    std::string expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    REQUIRE(model.getFEN() == expected);
}


TEST_CASE("Import game state using FEN", "[backend][fen]") {
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    ChessModel model;
    model.loadFEN(fen);  // Assuming this sets up the board from a FEN string

    REQUIRE(model.getFEN() == fen);
}

TEST_CASE("Load full game state from FEN", "[backend][fen]") {
    std::string fen = "rnbqkbnr/pp1ppppp/8/2p5/8/8/PPPPPPPP/RNBQKBNR b KQkq c6 3 2";

    ChessModel model;
    model.loadFEN(fen);

    ChessBoard& board = model.getBoard();

    // 1. Round-trip test
    REQUIRE(model.getFEN() == fen);

    // 2. Active color
    REQUIRE(model.getTurn() == Color::Black);

    // 3. Castling rights
    // REQUIRE(model.canCastle(Color::White, CastleSide::KingSide));
    // REQUIRE(model.canCastle(Color::White, CastleSide::QueenSide));
    // REQUIRE(model.canCastle(Color::Black, CastleSide::KingSide));
    // REQUIRE(model.canCastle(Color::Black, CastleSide::QueenSide));

    // 4. En passant square
    REQUIRE(board.getEnPassantTarget().has_value());
    REQUIRE(board.getEnPassantTarget().value() == ChessBoard::convertNotation("c6"));

    // 5. Halfmove clock
    REQUIRE(model.getHalfMoves() == 3);

    // 6. Fullmove number
    REQUIRE(model.getFullMoves() == 2);

    // 7. Board setup checks
    auto pieceC5 = board.at("c4");
    REQUIRE(pieceC5 != nullptr);
    REQUIRE(pieceC5->getType() == PieceType::Pawn);
    REQUIRE(pieceC5->getColor() == Color::Black);

    auto pieceD8 = board.at("d8");
    REQUIRE(pieceD8 != nullptr);
    REQUIRE(pieceD8->getType() == PieceType::Queen);
    REQUIRE(pieceD8->getColor() == Color::White);
}

