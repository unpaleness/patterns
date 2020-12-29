#include "pattern.hpp"

#include <iostream>
#include <memory>

#include <shapes.hpp>

namespace builder {

namespace {

class Builder {
 public:
  Builder() { Reset(); }
  virtual ~Builder(){};
  virtual void Form() const = 0;
  virtual void Paint() const = 0;
  virtual void Frame() const = 0;
  void Reset() { figure_ = std::make_unique<shapes::Figure>(); }
  std::unique_ptr<shapes::Figure> GetFigure() {
    auto finished_figure_ptr = std::move(figure_);
    Reset();
    return finished_figure_ptr;
  }

 protected:
  std::unique_ptr<shapes::Figure> figure_;
};

class GreenFramedTriangleBuilder final : public Builder {
 public:
  GreenFramedTriangleBuilder() : Builder() {
    std::wcout << "Constructing GreenFramedTriangleBuilder\n";
  }
  virtual void Form() const override final {
    figure_->SetShape(shapes::Shape::kTriangle);
  }
  virtual void Paint() const override final {
    figure_->SetColor(shapes::Color::kGreen);
  }
  virtual void Frame() const override final {
    figure_->SetFrame(shapes::Frame::kSingle);
  }
};

class RedDoubleFramedSquareBuilder final : public Builder {
 public:
  RedDoubleFramedSquareBuilder() : Builder() {
    std::wcout << "Constructing RedDoubleFramedSquareBuilder\n";
  }
  virtual void Form() const override final {
    figure_->SetShape(shapes::Shape::kSquare);
  }
  virtual void Paint() const override final {
    figure_->SetColor(shapes::Color::kRed);
  }
  virtual void Frame() const override final {
    figure_->SetFrame(shapes::Frame::kDouble);
  }
};

class Director final {
 public:
  Director() { std::wcout << "Constructing Director\n"; }
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
  std::wcout << "Client tells director to build default shape\n";
  director->BuildDefaultShape();
  builder->GetFigure()->draw();
  std::wcout << "Client tells director to build only formed shape\n";
  director->BuildOnlyFormedShape();
  builder->GetFigure()->draw();
  std::wcout << "Client tells director to build only colored shape\n";
  director->BuildOnlyColoredShape();
  builder->GetFigure()->draw();
  std::wcout << "Client tells director to build full shape\n";
  director->BuildFullShape();
  builder->GetFigure()->draw();
}

}  // namespace

void run() {
  std::wcout << "\n=== Builder ===\n\n";
  auto director = std::make_shared<Director>();
  std::wcout << "Client uses green framed triangle builder\n";
  ClientCode(director, std::make_shared<GreenFramedTriangleBuilder>());
  std::wcout << "Client uses red double framed square builder\n";
  ClientCode(director, std::make_shared<RedDoubleFramedSquareBuilder>());
  std::wcout << '\n';
}

}  // namespace builder
