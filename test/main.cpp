#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "board.hpp"

TEST_CASE("Pawn movement", "[pawn][movement]")
{
    ChessBoard board;
    board.clear();
    board.place(PieceType::Pawn, Color::White, "a7");
    auto piece = board.at({0, 6});

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
    REQUIRE(board.at({0, 7})->getType() == PieceType::Rook);
    REQUIRE(board.at({7, 7})->getType() == PieceType::Rook);
    REQUIRE(!board.at({4, 6}));

    auto king = board.at({4, 7});
    if (!king) std::cout << "king is null" << std::endl;
    std::vector<BoardPosition> moves = king->getValidMoves(board, {4, 7});
    REQUIRE(moves.size() == 7);
}
