#include "stdafx.h"
#include "Node.h"


Node::Node() : x(0), y(0), z(0), size(0), r(0), g(0), b(0), a(0) {};

Node::Node(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a)
	: x(_x), y(_y), z(_z), size(_size), r(_r), g(_g), b(_b), a(_a) { }


Node::~Node() { }

void Node::setSize(float _size) {
	size = _size;
}

float Node::getSize() {
	return size;
}

void Node::setPositionX(float _x) { x = _x;  }
float Node::getPositionX() { return x; }

void Node::setPositionY(float _y) { y = _y; }
float Node::getPositionY() { return y; }

void Node::setPositionZ(float _z) { z = _z; }
float Node::getPositionZ() { return z; }

void Node::setColor(Color& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
};

Color& Node::getColor() {
	Color color = { r, g, b, a };
	return color;
}

