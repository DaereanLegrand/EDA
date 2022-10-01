// Copyright

#ifndef SOURCE_RECTANGLE_HPP_
#define SOURCE_RECTANGLE_HPP_

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <stdexcept>

class Interval {
 public:
  Interval();
  explicit Interval(float begin, float end);

  Interval& operator=(const Interval& lhs);

  float& begin();
  float begin() const;

  float& end();
  float end() const;

  float get_range();

 private:
  // TODO(Roger): Replace with std::array
  float range[2];
};

/** Interval class implementation details*/

Interval::Interval() {}

Interval::Interval(float begin, float end) {
  if (end < begin) {
    throw std::invalid_argument("Begin must be lower or equal than end.");
  }
  range[0] = begin;
  range[1] = end;
}

Interval& Interval::operator=(const Interval& lhs) {
  range[0] = lhs.range[0];
  range[1] = lhs.range[1];
  return *this;
}

float& Interval::begin() { return range[0]; }
float Interval::begin() const { return range[0]; }

float& Interval::end() { return range[1]; }
float Interval::end() const { return range[1]; }

float Interval::get_range() { return end() - begin(); }

bool overlaps(const Interval& one, const Interval& lhs) {
  if (lhs.begin() < one.end() && one.begin() < lhs.end()) {
    return true;
  }
  if (one.begin() < lhs.end() && lhs.begin() < one.end()) {
    return true;
  }
  return false;
}

float get_enlargement(const Interval& rhs, const Interval& lhs) {
  float total_enlargement = 0.f;
  if (rhs.end() < lhs.end()) {
    total_enlargement += lhs.end() - rhs.end();
  }
  if (lhs.begin() < rhs.begin()) {
    total_enlargement += rhs.begin() - lhs.begin();
  }
  return total_enlargement;
}

template <size_t N>
class Rectangle {
 public:
  typedef Interval* iterator;
  typedef const Interval* const_iterator;

  Interval& operator[](size_t index);
  Interval operator[](size_t index) const;

  Rectangle& operator=(const Rectangle& rectangle);

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  float get_area();

  void reset();

  void adjust(const Rectangle& rectangle);

 private:
  Interval bounds[N];
};

/** Rectangle class implementation details*/
template <size_t N>
Interval& Rectangle<N>::operator[](size_t index) {
  return bounds[index];
}

template <size_t N>
Interval Rectangle<N>::operator[](size_t index) const {
  return bounds[index];
}

template <size_t N>
Rectangle<N>& Rectangle<N>::operator=(const Rectangle<N>& rhs) {
  std::copy(rhs.begin(), rhs.end(), begin());
  return *this;
}

template <size_t N>
typename Rectangle<N>::iterator Rectangle<N>::begin() {
  return bounds;
}

template <size_t N>
typename Rectangle<N>::iterator Rectangle<N>::end() {
  return bounds + N;
}

template <size_t N>
typename Rectangle<N>::const_iterator Rectangle<N>::begin() const {
  return bounds;
}

template <size_t N>
typename Rectangle<N>::const_iterator Rectangle<N>::end() const {
  return bounds + N;
}

template <size_t N>
void Rectangle<N>::reset() {
  for (Interval& interval : *this) {
    interval.begin() = LONG_MAX;
    interval.end() = LONG_MIN;
  }
}

template <size_t N>
float Rectangle<N>::get_area() {
  float area = 1.f;
  for (Interval& interval : *this) {
    area *= interval.get_range();
  }
  return area;
}

template <size_t N>
void Rectangle<N>::adjust(const Rectangle& rectangle) {
  for (size_t index = 0; index < N; ++index) {
    (*this)[index].begin() =
        std::min(rectangle[index].begin(), (*this)[index].begin());
    (*this)[index].end() =
        std::max(rectangle[index].end(), (*this)[index].end());
  }
}

template <size_t N>
bool overlaps(const Rectangle<N>& rhs, const Rectangle<N>& lhs) {
  for (size_t index = 0; index < N; ++index) {
    if (!overlaps(rhs[index], lhs[index])) {
      return false;
    }
  }
  return true;
}

#endif  // SOURCE_RECTANGLE_HPP_
