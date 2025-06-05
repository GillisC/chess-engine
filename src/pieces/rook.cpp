#include "pieces/rook.hpp"
#include "board.hpp"

Rook::Rook(Color color) : Piece(color) {}

const sf::Texture &Rook::getTexture(const TextureManager &manager) const {
  if (getColor() == WHITE) {
    return manager.get("white_rook");
  }
  return manager.get("black_rook");
}

std::vector<BoardPosition> Rook::getValidMoves(ChessBoard &board,
                                               const BoardPosition &pos) {
  std::vector<BoardPosition> validMoves = {};

  rookTravel(board, pos, -1, 0, validMoves);
  rookTravel(board, pos, 0, -1, validMoves);
  rookTravel(board, pos, 1, 0, validMoves);
  rookTravel(board, pos, 0, 1, validMoves);

  return validMoves;
}

void Rook::rookTravel(ChessBoard &board, const BoardPosition startPos, int xDir,
                      int yDir, std::vector<BoardPosition> &moveVec) {
  for (int i = 1; i < 8; i++) {
    BoardPosition offsetPos = {startPos.x() + (xDir * i),
                               startPos.y() + yDir * i};
    if (board.isInBounds(offsetPos)) {
      if (!(board.isPiece(offsetPos))) {
        moveVec.push_back(offsetPos);
      } else if (board.at(offsetPos)->getColor() ==
                 board.at(startPos)->getColor()) {
        break;
      } else if (board.at(offsetPos)->getColor() !=
                 board.at(startPos)->getColor()) {
        moveVec.push_back(offsetPos);
        break;
      }
    } else
      break;
  }
}
