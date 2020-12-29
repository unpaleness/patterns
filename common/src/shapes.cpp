#include <shapes.hpp>

#include <array>
#include <iostream>
#include <unordered_map>

#include <platform.hpp>

namespace shapes {

namespace {

const std::unordered_map<Shape, wchar_t> kShapeMap = {
    {Shape::kNone, L'\u2219'},  // dot
    {Shape::kSquare, L'\u25a0'},
    {Shape::kTriangle, L'\u25b2'},
};

const std::unordered_map<Color, platform::ConsoleColor> kColorMap = {
    {Color::kDefault, platform::kDefaultColor},
    {Color::kRed, platform::kRedColor},
    {Color::kGreen, platform::kGreenColor},
};

/* 0 4 1
   5   5 - positions of each frame tile
   2 4 3 */
const std::unordered_map<Frame, std::array<wchar_t, 6>> kFrameMap = {
    {Frame::kNone, {' ', ' ', ' ', ' ', ' ', ' '}},
    {Frame::kSingle,
     {L'\u250c', L'\u2510', L'\u2514', L'\u2518', L'\u2500', L'\u2502'}},
    {Frame::kDouble,
     {L'\u2554', L'\u2557', L'\u255a', L'\u255d', L'\u2550', L'\u2551'}},
};

}  // namespace

Figure::Figure() {
  std::wcout << "Constructing Figure\n";
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
  const auto last_console_color = platform::GetConsoleColor();
  platform::SetConsoleColor(kColorMap.at(color_));

  const auto& frames = kFrameMap.at(frame_);
  std::wcout << frames.at(0) << frames.at(4) << frames.at(1) << '\n'
             << frames.at(5) << kShapeMap.at(shape_) << frames.at(5) << '\n'
             << frames.at(2) << frames.at(4) << frames.at(3) << '\n';

  platform::SetConsoleColor(last_console_color);
}

Square::Square() {
  std::wcout << "Constructing Square\n";
  SetShape(Shape::kSquare);
}
RedSquare::RedSquare() {
  std::wcout << "Constructing RedSquare\n";
  SetColor(Color::kRed);
}
GreenSquare::GreenSquare() {
  std::wcout << "Constructing GreenSquare\n";
  SetColor(Color::kGreen);
}
Triangle::Triangle() {
  std::wcout << "Constructing Triangle\n";
  SetShape(Shape::kTriangle);
}
RedTriangle::RedTriangle() {
  std::wcout << "Constructing RedTriangle\n";
  SetColor(Color::kRed);
}
GreenTriangle::GreenTriangle() {
  std::wcout << "Constructing GreenTriangle\n";
  SetColor(Color::kGreen);
}

}  // namespace shapes
