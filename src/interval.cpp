#include <armadillo>

#include "interval.hpp"

interval::interval() 
    : min(arma::datum::inf), max(-arma::datum::inf) {}

interval::interval(double min, double max)
    : min(min), max(max) {}

double interval::size() const {
    return max - min;
}

bool interval::contains(double x) const {
    return min <= x && x <= max;
}

bool interval::surrounds(double x) const {
    return min < x && x < max;
}

const interval interval::empty = interval(arma::datum::inf, -arma::datum::inf);
const interval interval::universe = interval(-arma::datum::inf, arma::datum::inf);
