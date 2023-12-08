#ifndef BLOCK_HPP
#define BLOCK_HPP

class block {
protected:
	float _x;
	float _y;
	float _size;
	
public:
	block(float x, float y, float size);
	void setX(float x);
	void setY(float y);
	void addX(float dx);
	void addY(float dy);
	float getX() const;
	float getY() const;
	float getCenterX() const;
	float getCenterY() const;
	float getSize() const;
};

#endif