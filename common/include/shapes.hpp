#pragma once

namespace shapes {

enum class Shape { kNone, kSquare, kTriangle };
enum class Color { kDefault, kRed, kGreen };
enum class Frame { kNone, kSingle, kDouble };

class Figure {
public:
    Figure();
    void SetShape(Shape shape);
    void SetColor(Color color);
    void SetFrame(Frame frame);
    void draw() const;

private:
    Shape shape_{Shape::kNone};
    Color color_{Color::kDefault};
    Frame frame_{Frame::kNone};
};

class Square : protected Figure {
public:
    using Figure::draw;

    Square();
};

class RedSquare : public Square {
public:
    RedSquare();
};

class GreenSquare : public Square {
public:
    GreenSquare();
};

class Triangle : protected Figure {
public:
    using Figure::draw;

    Triangle();
};

class RedTriangle : public Triangle {
public:
    RedTriangle();
};

class GreenTriangle : public Triangle {
public:
    GreenTriangle();
};

}  // namespace shapes
