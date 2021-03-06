#pragma once
class Vertex
{
public:

	Vertex();
	Vertex(float x, float y, float z);
	Vertex(const Vertex& other);

	//Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float y);
	float GetW() const;
	void SetW(const float w);

	//Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;


	void Dehomogenzied();

private:
	float _x;
	float _y;
	float _z;
	float _w;
};

