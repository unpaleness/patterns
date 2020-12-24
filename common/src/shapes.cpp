#include <shapes.hpp>

#include <iostream>
#include <string>
#include <unordered_map>

namespace shapes {

namespace {

const std::unordered_map<Shape, std::string> kShapeMap = {
    {Shape::kNone, "\u2219"},  // dot
    {Shape::kSquare, "\u25a0"},
    {Shape::kTriangle, "\u25b2"},
};

const std::unordered_map<Color, std::string> kColorMap = {
    {Color::kDefault, "\033[0m"},
    {Color::kRed, "\033[31m"},
    {Color::kGreen, "\033[32m"},
};

/* 0 4 1
   5   5 - positions of each frame tile
   2 4 3 */
const std::unordered_map<Frame, std::array<std::string, 6>> kFrameMap = {
    {Frame::kNone, {" ", " ", " ", " ", " ", " "}},
    {Frame::kSingle,
     {"\u250c", "\u2510", "\u2514", "\u2518", "\u2500", "\u2502"}},
    {Frame::kDouble,
     {"\u2554", "\u2557", "\u255a", "\u255d", "\u2550", "\u2551"}},
};

}  // namespace

Figure::Figure() {
  std::cout << "Constructing Figure\n";
}
void Figure::SetShape(Shape shape) {
  shape_ = shape;
}
void Figure::SetColor(Color color) {
  color_ = color;
}
void Figure::SetFrame(Frame frame) {
  frame_ = frame;
}
void Figure::draw() const {
  const auto& frames = kFrameMap.at(frame_);
  std::cout << kColorMap.at(color_) << frames.at(0) << frames.at(4)
            << frames.at(1) << '\n'
            << frames.at(5) << kShapeMap.at(shape_) << frames.at(5) << '\n'
            << frames.at(2) << frames.at(4) << frames.at(3)
            << kColorMap.at(Color::kDefault) << '\n';
}

Square::Square() {
  std::cout << "Constructing Square\n";
  SetShape(Shape::kSquare);
}
RedSquare::RedSquare() {
  std::cout << "Constructing RedSquare\n";
  SetColor(Color::kRed);
}
GreenSquare::GreenSquare() {
  std::cout << "Constructing GreenSquare\n";
  SetColor(Color::kGreen);
}
Triangle::Triangle() {
  std::cout << "Constructing Triangle\n";
  SetShape(Shape::kTriangle);
}
RedTriangle::RedTriangle() {
  std::cout << "Constructing RedTriangle\n";
  SetColor(Color::kRed);
}
GreenTriangle::GreenTriangle() {
  std::cout << "Constructing GreenTriangle\n";
  SetColor(Color::kGreen);
}

}  // namespace shapes
