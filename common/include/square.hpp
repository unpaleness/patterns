#pragma once

class Square {
 public:
  virtual ~Square() {}
  virtual void draw() const = 0;
};

class RedSquare : public Square {
 public:
  RedSquare();
  virtual void draw() const override final;
};

class GreenSquare : public Square {
 public:
  GreenSquare();
  virtual void draw() const override final;
};
