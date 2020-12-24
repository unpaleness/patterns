#include "pattern.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace builder {

namespace {

enum class Shape { kNone, kSquare, kTriangle };

const std::unordered_map<Shape, std::string> kShapeMap = {
    {Shape::kNone, "\u2219"},  // dot
    {Shape::kSquare, "\u25a0"},
    {Shape::kTriangle, "\u25b2"},
};

enum class Color { kDefault, kRed, kGreen };

const std::unordered_map<Color, std::string> kColorMap = {
    {Color::kDefault, "\033[0m"},
    {Color::kRed, "\033[31m"},
    {Color::kGreen, "\033[32m"},
};

enum class Frame { kNone, kSingle, kDouble };

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

class Figure final {
 public:
  Figure() { std::cout << "Constructing Figure\n"; }
  void SetShape(Shape shape) { shape_ = shape; }
  void SetColor(Color color) { color_ = color; }
  void SetFrame(Frame frame) { frame_ = frame; }
  void draw() const {
    const auto& frames = kFrameMap.at(frame_);
    std::cout << kColorMap.at(color_) << frames.at(0) << frames.at(4)
              << frames.at(1) << '\n'
              << frames.at(5) << kShapeMap.at(shape_) << frames.at(5) << '\n'
              << frames.at(2) << frames.at(4) << frames.at(3)
              << kColorMap.at(Color::kDefault) << '\n';
  }

 private:
  Shape shape_{Shape::kNone};
  Color color_{Color::kDefault};
  Frame frame_{Frame::kNone};
};

class Builder {
 public:
  Builder() { Reset(); }
  virtual ~Builder(){};
  virtual void Form() const = 0;
  virtual void Paint() const = 0;
  virtual void Frame() const = 0;
  void Reset() { figure_ = std::make_unique<Figure>(); }
  std::unique_ptr<Figure> GetFigure() {
    auto finished_figure_ptr = std::move(figure_);
    Reset();
    return std::move(finished_figure_ptr);
  }

 protected:
  std::unique_ptr<Figure> figure_;
};

class GreenFramedTriangleBuilder final : public Builder {
 public:
  GreenFramedTriangleBuilder() : Builder() {
    std::cout << "Constructing GreenFramedTriangleBuilder\n";
  }
  virtual void Form() const override final {
    figure_->SetShape(Shape::kTriangle);
  }
  virtual void Paint() const override final {
    figure_->SetColor(Color::kGreen);
  }
  virtual void Frame() const override final {
    figure_->SetFrame(Frame::kSingle);
  }
};

class RedDoubleFramedSquareBuilder final : public Builder {
 public:
  RedDoubleFramedSquareBuilder() : Builder() {
    std::cout << "Constructing RedDoubleFramedSquareBuilder\n";
  }
  virtual void Form() const override final {
    figure_->SetShape(Shape::kSquare);
  }
  virtual void Paint() const override final { figure_->SetColor(Color::kRed); }
  virtual void Frame() const override final {
    figure_->SetFrame(Frame::kDouble);
  }
};

class Director final {
 public:
  Director() { std::cout << "Constructing Director\n"; }
  void SetBuilder(std::shared_ptr<Builder> builder) { builder_ = builder; }
  void BuildDefaultShape() {}
  void BuildOnlyFormedShape() { builder_->Form(); }
  void BuildOnlyColoredShape() { builder_->Paint(); }
  void BuildFullShape() {
    builder_->Form();
    builder_->Paint();
    builder_->Frame();
  }

 private:
  std::shared_ptr<Builder> builder_;
};

void ClientCode(std::shared_ptr<Director> director,
                std::shared_ptr<Builder> builder) {
  director->SetBuilder(builder);
  std::cout << "Client tells director to build default shape\n";
  director->BuildDefaultShape();
  builder->GetFigure()->draw();
  std::cout << "Client tells director to build only formed shape\n";
  director->BuildOnlyFormedShape();
  builder->GetFigure()->draw();
  std::cout << "Client tells director to build only colored shape\n";
  director->BuildOnlyColoredShape();
  builder->GetFigure()->draw();
  std::cout << "Client tells director to build full shape\n";
  director->BuildFullShape();
  builder->GetFigure()->draw();
}

}  // namespace

void run() {
  std::cout << "\n=== Builder ===\n\n";
  auto director = std::make_shared<Director>();
  std::cout << "Client uses green framed triangle builder\n";
  ClientCode(director, std::make_shared<GreenFramedTriangleBuilder>());
  std::cout << "Client uses red double framed square builder\n";
  ClientCode(director, std::make_shared<RedDoubleFramedSquareBuilder>());
  std::cout << '\n';
}

}  // namespace builder
