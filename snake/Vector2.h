#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

struct Vector2 {
	int x, y;
	Vector2() :
		x(0),
		y(0)
	{}

	Vector2(int x, int y) :
		x(x),
		y(y)
	{}

	double getLength() {
		return sqrt(pow(this->x, 2) + pow(this->y, 2));
	}

	bool operator==(Vector2& other) {
		return (this->x == other.x && this->y == other.y);
	}

	bool operator==(const Vector2& other) {
		return (this->x == other.x && this->y == other.y);
	}

	bool operator!=(const Vector2& other) {
		return (this->x != other.x || this->y != other.y);
	}

	bool operator!=(Vector2& other) {
		return (this->x != other.x || this->y != other.y);
	}


	Vector2 operator+(Vector2& other) {
		return Vector2(this->x + other.x, this->y + other.y);
	}

	Vector2 operator+(const Vector2& other) {
		return Vector2(this->x + other.x, this->y + other.y);
	}

	void operator+=(Vector2& other) {
		this->x += other.x;
		this->y += other.y;
	}

	Vector2 operator-(Vector2& other) {
		return Vector2(this->x - other.x, this->y - other.y);
	}

	void operator-=(Vector2& other) {
		this->x -= other.x;
		this->y -= other.y;
	}

	/*Vector2 operator*(Vector2& other) {
	return Vector2();
	}*/

	Vector2 operator*(const float& k) {
		return Vector2((int)std::ceil(this->x * k), (int)std::ceil(this->y * k));
	}

	Vector2 operator/(int k) {
		return Vector2(this->x / k, this->y / k);
	}

};


#endif // !VECTOR2_H