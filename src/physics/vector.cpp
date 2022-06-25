#include "vector.hpp"

#include <cmath>

#include "../util.hpp"

Vector::Vector(double x, double y) : x(x), y(y) {
	round();
}

Vector::~Vector() {}

/* Private */

void Vector::round() {
	if (fabs(x) < 0.001) x = 0;
	if (fabs(y) < 0.001) y = 0;
}

/* Public Static */

Vector Vector::make_cart(double x, double y) {
	return Vector(x, y);
}

Vector Vector::make_polar(double r, double th) {
	return Vector(r * cos(th), r * sin(th));
}

Vector *Vector::new_cart(double x, double y) {
	return new Vector(x, y);
}

Vector *Vector::new_polar(double r, double th) {
	return new Vector(r * cos(th), r * sin(th));
}

/* Public */

double Vector::get_x() {
	return x;
}

double Vector::get_y() {
	return y;
}

double Vector::get_r() {
	return sqrt(x * x + y * y);
}

double Vector::get_th() {
	if (x == 0) {
		if (y == 0) return 0;
		if (y > 0) return M_PI / 2;
		if (y < 0) return 3 * M_PI / 2;
	}
	if (y == 0) {
		if (x > 0) return 0;
		if (x < 0) return M_PI;
	}
	return wrap_angle(atan(y / x));
}

void Vector::set_cart(double x, double y) {
	this->x = x;
	this->y = y;
	round();
}

void Vector::set_polar(double r, double th) {
	this->x = r * cos(th);
	this->y = r * sin(th);
	round();
}

void Vector::apply_to(Vector &vec, double mult) {
	vec.x += this->x * mult;
	vec.y += this->y * mult;
}
