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

TEST_CASE("Export game state using FEN", "[backend]")
{
    ChessModel model;
    std::string expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    REQUIRE(model.getFEN() == expected);
}
