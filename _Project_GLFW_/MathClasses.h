#pragma once
#include "WindowComponent.h"
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <cmath>
#include <type_traits>



constexpr double PI = 3.14159265358979323846;
constexpr float ToRadians = PI / 180;
const int Width = 2560;
const int Height = 1440;


template<typename T>
concept Numeric = std::is_arithmetic_v<T>;
template<typename T>
concept Floating = std::is_floating_point_v<T>;

template<Numeric T>
class Vector2F
{
	T m_X;
	T m_Y;

public:
	Vector2F(T x, T y) :m_X(x), m_Y(y) {}
	Vector2F() = default;

	Vector2F& operator=(const Vector2F<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		m_X = other.get_X();
		m_Y = other.get_Y();
		return *this;
	}
	Vector2F(const Vector2F<T>& other)
	{
		m_X = other.get_X();
		m_Y = other.get_Y();
	}
	T get_X() const
	{
		return m_X;
	}
	T get_Y() const
	{
		return m_Y;
	}
	void set_X(T x)
	{
		this->m_X = x;
	}
	void set_Y(T y)
	{
		this->m_Y = y;
	}

	std::string ToString() const
	{
		return "(" + std::to_string(m_X) + "," + std::to_string(m_Y) + ")" + "\n";
	}

	//returning the length of the vector or in another words hypotenus of the triangle 
	T LengthVector2f() const
	{
		return sqrt(m_X * m_X + m_Y * m_Y);
	}
	// overloading dot product for my vector2f c++ feature:)
	T Dotproduct(const Vector2F& r)
	{
		return m_X * r.get_X() + m_Y * r.get_Y();
	}
	// returning vector it self after normalization(or making it equal to 1)
	Vector2F Normalization()
	{
		T length = LengthVector2f();
		if (std::abs(length) <= 1e-6)
		{
			std::cerr << "division by 0\n";
			return Vector2F<T>(0, 0);
		}
		return Vector2F<T>(m_X / length, m_Y / length);
	}
	static Vector2F<double> CursorPos()
	{
		double xpos = 0.0, ypos = 0.0;
		glfwGetCursorPos(Window::m_mywindow, &xpos, &ypos);
		return Vector2F<double>(xpos, ypos);

	}
	// functions for basic operations with vectors 
	//this is to add another vector 2f 
	Vector2F operator+(const Vector2F& num)const
	{
		return Vector2F(m_X + num.get_X(), m_Y + num.get_Y());
	}
	Vector2F& operator+=(const Vector2F& num)
	{
		m_X += num.get_X();
		m_Y += num.get_Y();
		return *this;
	}
	Vector2F operator-(const Vector2F& num)const
	{
		return Vector2F(m_X - num.get_X(), m_Y - num.get_Y());
	}
	Vector2F& operator-=(const Vector2F& num)
	{
		m_X -= num.get_X();
		m_Y -= num.get_Y();
		return *this;
	}
	Vector2F operator*(const Vector2F& num)const
	{
		return Vector2F(m_X * num.get_X(), m_Y * num.get_Y());
	}
	Vector2F& operator*=(const Vector2F& num)
	{
		m_X *= num.get_X();
		m_Y *= num.get_Y();
		return *this;
	}
	Vector2F operator/(const Vector2F& num)const
	{
		T x = m_X, y = m_Y;
		if (num.get_X() != static_cast<T>(0))
		{
			x = m_X / num.get_X();
		}
		if (num.get_Y() != static_cast<T>(0))
		{
			y = m_Y / num.get_Y();
		}

		return Vector2F(x, y);
	}
	Vector2F& operator/=(const Vector2F& num)
	{

		if (num.get_X() != static_cast<T>(0))
		{
			m_X /= num.get_X();

		}
		if (num.get_Y() != static_cast<T>(0))
		{
			m_Y /= num.get_Y();
		}
		return *this;
	}
	Vector2F operator+(const T& num)const
	{
		return Vector2F(m_X + num, m_Y + num);
	}
	Vector2F& operator+=(const T& num)
	{
		m_X += num;
		m_Y += num;
		return *this;
	}
	Vector2F operator-(const T& num)const
	{
		return Vector2F(m_X - num, m_Y - num);
	}
	Vector2F& operator-=(const T& num)
	{
		m_X -= num;
		m_Y -= num;
		return *this;
	}
	Vector2F operator*(const T& num)const
	{
		return Vector2F(m_X * num, m_Y * num);
	}
	Vector2F& operator*=(const T& num)
	{
		m_X *= num;
		m_Y *= num;
		return *this;
	}
	Vector2F operator/(const T& num)const
	{
		if (std::abs(num) <= 1e-6)
		{
			return Vector2F(m_X / 1, m_Y / 1);
		}

		return Vector2F(m_X / num, m_Y / num);
	}
	Vector2F& operator/=(const T& num)
	{
		if (std::abs(num) <= 1e-6)
		{
			return *this;
		}
		m_X /= num;
		m_Y /= num;
		return *this;
	}


	Vector2F Rotate(const T& angle)
	{
		T rad = angle * ToRadians;
		T sin = std::sin(rad);
		T cos = std::cos(rad);

		return Vector2F(cos * m_X - sin * m_Y, sin * m_X + cos * m_Y);
	}
};
template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Vector2F<T>& v)
{
	os << v.ToString();
	return os;
}
template<Numeric T>
class Vector3F
{
	T m_X;
	T m_Y;
	T m_Z;
public:
	Vector3F(T x, T y, T z) :m_X(x), m_Y(y), m_Z(z) {}
	Vector3F() = default;
	Vector3F& operator=(const Vector3F<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		m_X = other.getX3D();
		m_Y = other.getY3D();
		m_Z = other.getX3D();
		return *this;
	}
	Vector3F(const Vector3F<T>& other)
	{
		m_X = other.getX3D();
		m_Y = other.getY3D();
		m_Z = other.getZ3D();
	}
	T getX3D()const
	{
		return m_X;
	}
	T getY3D()const
	{
		return m_Y;
	}
	T getZ3D()const
	{
		return m_Z;
	}
	void setX3D(T x)
	{
		this->m_X = x;
	}
	void setY3D(T y)
	{
		this->m_Y = y;
	}
	void setZ3D(T z)
	{
		this->m_Z = z;
	}
public:

	T LengthVector3f()
	{
		return  sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
	}
	Vector3F CrossProduct(const Vector3F& Vec) const
	{
		return Vector3F(m_Y * Vec.m_Z - m_Z * Vec.m_Y, m_Z * Vec.m_X - m_X * Vec.m_Z, m_X * Vec.m_Y - m_Y * Vec.m_X);
	}

	Vector3F Normalize3d()
	{
		T length = LengthVector3f();
		if (std::abs(length) <= 1e-6)
		{
			std::cerr << m_X << "," << m_Y << "," << m_Z << ":this was vector which length was 0\n";
			std::cerr << "this is the error cause by division by 0" << "\n";
			return Vector3F<T>(0, 0, 0);			
		}
		return Vector3F<T>(m_X / length, m_Y / length, m_Z / length);
	}

	T Dotproduct(const Vector3F& r)
	{
		return m_X * r.getX3D() + m_Y * r.getY3D() + m_Z * r.getZ3D();
	}

	Vector3F operator+(const Vector3F& other)const
	{
		return Vector3F(m_X + other.getX3D(), m_Y + other.getY3D(), m_Z + other.getZ3D());
	}
	Vector3F& operator+=(const Vector3F& other)
	{
		m_X += other.getX3D();
		m_Y += other.getY3D();
		m_Z += other.getZ3D();
		return *this;
	}
	Vector3F operator-(const Vector3F& other)const
	{
		return Vector3F(m_X - other.getX3D(), m_Y - other.getY3D(), m_Z - other.getZ3D());
	}
	Vector3F& operator-=(const Vector3F& other)
	{
		m_X -= other.getX3D();
		m_Y -= other.getY3D();
		m_Z -= other.getZ3D();
		return *this;
	}
	Vector3F operator*(const Vector3F& other) const
	{
		return Vector3F(m_X * other.getX3D(), m_Y * other.getY3D(), m_Z * other.getZ3D());
	}
	Vector3F& operator*=(const Vector3F& other)
	{
		m_X *= other.getX3D();
		m_Y *= other.getY3D();
		m_Z *= other.getZ3D();
		return *this;
	}
	Vector3F operator/(const Vector3F& other) const
	{
		T x = m_X, y = m_Y, z = m_Z;

		if (std::abs(other.getX3D()) >= 1e-6)
		{
			x = m_X / other.getX3D();
		}

		if (std::abs(other.getY3D()) >= 1e-6)
		{
			y = m_Y / other.getY3D();
		}
		if (std::abs(other.getZ3D()) >= 1e-6)
		{
			z = m_Z / other.getZ3D();
		}

		return Vector3F(x, y, z);
	}
	Vector3F& operator/=(const Vector3F& other)
	{
		if (std::abs(other.getX3D()) >= 1e-6)
		{
			m_X /= other.getX3D();
		}

		if (std::abs(other.getY3D()) >= 1e-6)
		{
			m_Y /= other.getY3D();
		}
		if (std::abs(other.getZ3D()) >= 1e-6)
		{
			m_Z /= other.getZ3D();
		}


		return *this;
	}
	Vector3F operator+(const T& other) const
	{
		return Vector3F(m_X + other, m_Y + other, m_Z + other);
	}
	Vector3F& operator+=(const T& other)
	{
		m_X += other;
		m_Y += other;
		m_Z += other;
		return *this;
	}
	Vector3F operator-(const T& other)const
	{
		return Vector3F(m_X - other, m_Y - other, m_Z - other);
	}
	Vector3F& operator-=(const T& other)
	{
		m_X -= other;
		m_Y -= other;
		m_Z -= other;
		return *this;
	}
	Vector3F operator*(const T& other)const
	{
		return Vector3F(m_X * other, m_Y * other, m_Z * other);
	}
	Vector3F& operator*=(const T& other)
	{
		m_X -= other;
		m_Y -= other;
		m_Z -= other;
		return *this;
	}

	Vector3F operator/(const T& other)const
	{
		T x = m_X, y = m_Y, z = m_Z;

		if (std::abs(other) >= 1e-6)
		{
			x = m_X / other;
			y = m_Y / other;
			z = m_Z / other;
		}

		return Vector3F(x, y, z);

	}
	Vector3F& operator/=(const T& other)
	{
		if (std::abs(other) >= 1e-6)
		{
			m_X /= other;
			m_Y /= other;
			m_Z /= other;
		}

		return *this;
	}

	Vector3F  Crossproduct(Vector3F vector)
	{
		T X_x = m_Y * vector.getZ3D() - m_Z * vector.getY3D();
		T Y_y = m_Z * vector.getX3D() - m_X * vector.getZ3D();
		T Z_z = m_X * vector.getY3D() - m_Y * vector.getX3D();


		return Vector3F(X_x, Y_y, Z_z);
	}

	std::string to_String()const
	{
		return "(" + std::to_string(m_X) + "," + std::to_string(m_Y) + "," + std::to_string(m_Z) + ")" + "\n";
	}

};
template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Vector3F<T>& v)
{
	os << v.to_String();
	return os;
}
//TODO object's rotation by axis
template<Numeric T>
class Quatornion
{
	T m_x;
	T m_y;
	T m_z;
	T m_w;
public:
	//functions
	Quatornion(T x, T y, T z, T w) :m_x(x), m_y(y), m_z(z), m_w(w) {}
	Quatornion() = default;
	//todo  *  operators and alos << operator
	Quatornion operator*(const Quatornion& other)
	{
		T w_ = m_w * other.getW() - m_x * other.getX() - m_y * other.getY() - m_z * other.getZ();
		T x_ = m_x * other.getW() + m_w * other.getX() + m_y * other.getZ() - m_z * other.getY();
		T y_ = m_y * other.getW() + m_w * other.getY() + m_z * other.getX() - m_x * other.getZ();
		T z_ = m_z * other.getW() + m_w * other.getZ() + m_x * other.getY() - m_y * other.getX();

		return  Quatornion(x_, y_, z_, w_);
	}
	Quatornion operator*(const Vector3F<T>& other)
	{
		T w_ = -m_x * other.getX3D() - m_y * other.getY3D() - m_z * other.getZ3D();
		T x_ = m_w * other.getX3D() + m_y * other.getZ3D() - m_z * other.getY3D();
		T y_ = m_w * other.getY3D() + m_z * other.getX3D() - m_x * other.getZ3D();
		T z_ = m_w * other.getZ3D() + m_x * other.getY3D() - m_y * other.getX3D();

		return  Quatornion(x_, y_, z_, w_);
	}


public:
	T QuatornionLength()
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	}
	Quatornion Normalization()
	{
		T length = QuatornionLength();

		if (length == 0.0f) {
			return Quatornion<float>(0, 0, 0, 0);
		}
		m_x /= length;
		m_y /= length;
		m_z /= length;
		m_w /= length;

		return *this;
	}
	Quatornion Conjugate()
	{
		return  Quatornion(-m_x, -m_y, -m_z, m_w);
	}
	//r should be (1,1,0)normalized for vertical spinning need to be fixed ..
	Quatornion Rotation(double& alpha, Vector3F<float>& r)
	{
		r.Normalize3d();
		double rad = alpha * PI / 180.0;
		Quatornion Q1(0, 1, 0, 0);
		Quatornion Q2(cos(rad / 2), r.getX3D() * sin(rad / 2), r.getY3D() * sin(rad / 2), r.getZ3D() * sin(rad / 2));
		Quatornion Q3 = Q2 * Q1 * Q2;

		return Q3;

	}
public:
	// getters and setters
	T getX()const { return this->m_x; }
	T getY()const { return this->m_y; }
	T getZ()const { return this->m_z; }
	T getW()const { return this->m_w; }
	void setX(T& x) { this->m_x = x; }
	void setY(T& y) { this->m_y = y; }
	void setZ(T& z) { this->m_z = z; }
	void setW(T& w) { this->m_w = w; }
};

template<Numeric T>
class Matrix
{
	int m_M;
	int m_N;
	std::vector<std::vector<T>> m_matrix;
public:
	//standart tools/operators
	Matrix() = default;
	Matrix(int m, int n, const T& initial) :m_M(m), m_N(n)
	{

		if (m <= 0 || n <= 0)
		{
			throw std::invalid_argument("Matrix dimensions cant be negative/0");

		}
		m_matrix.resize(m);
		for (int i = 0; i < m_matrix.size(); i++)
		{
			m_matrix[i].resize(n, initial);
		}


	}
	// copy constructor
	Matrix(const Matrix& other)
	{
		m_matrix = other.m_matrix;
		m_M = other.m_M;
		m_N = other.m_N;
	}
	//assignment operator
	Matrix& operator=(const Matrix<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		int newrow = other.m_M;
		int newcol = other.m_N;

		m_matrix.resize(newrow);
		for (int i = 0; i < m_matrix.size(); i++)
		{
			m_matrix[i].resize(newcol);
		}
		for (int i = 0; i < newrow; i++) {
			for (int j = 0; j < newcol; j++) {
				m_matrix[i][j] = other.m_matrix[i][j];
			}
		}
		m_M = newrow;
		m_N = newcol;

		return *this;
	}
	const T& operator()(const int& row, const int& col) const
	{
		return this->m_matrix[row][col];
	}

	T& operator()(const int& row, const int& col)
	{
		return this->m_matrix[row][col];
	}

public:
	//mathmatical operations
	Matrix<T> operator*(const Matrix<T>& other)
	{
		if (this->m_N != other.m_M) {
			throw std::invalid_argument("Matrix dimensions do not match for multiplication");
		}
		int rows = other.m_M;
		int cols = other.m_N;
		Matrix result(rows, cols, 0.0);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				for (int k = 0; k < rows; k++) {
					result(i, j) += (*this)(i, k) * other(k, j);
				}
			}
		}

		return result;
	}
	Matrix operator*=(const Matrix& other)
	{
		Matrix result = (*this) * other;
		(*this) = result;
		return *this;

	}
	Matrix operator*(const T& other)
	{
		Matrix result(m_M, m_N, 0.0);

		for (int i = 0; i < m_M; i++) {
			for (int j = 0; j < m_N; j++) {
				result(i, j) = this->m_matrix[i][j] * other;
			}
		}

		return result;
	}
	//for 3d rotation by object's axis
	Matrix& ConvertQuatornian(Matrix<float>& model, const Quatornion<float>& q)
	{

		float xx = q.getX() * q.getX(), yy = q.getY() * q.getY(), zz = q.getZ() * q.getZ();
		float xy = q.getX() * q.getY(), xz = q.getX() * q.getZ(), yz = q.getY() * q.getZ();
		float wx = q.getW() * q.getX(), wy = q.getW() * q.getY(), wz = q.getW() * q.getZ();
		//first row
		model.setElement(0, 0, 1 - 2 * (yy + zz));
		model.setElement(0, 1, 2 * (xy - wz));
		model.setElement(0, 2, 2 * (xz + wy));
		model.setElement(0, 3, 0);
		//second row
		model.setElement(1, 0, 2 * (xy + wz));
		model.setElement(1, 1, 1 - 2 * (xx + zz));
		model.setElement(1, 2, 2 * (yz - wx));
		model.setElement(1, 3, 0);
		//third row
		model.setElement(2, 0, 2 * (xz - wy));
		model.setElement(2, 1, 2 * (yz + wx));
		model.setElement(2, 2, 1 - 2 * (xx + yy));
		model.setElement(2, 3, 0);
		//forth row
		model.setElement(3, 0, 0);
		model.setElement(3, 1, 0);
		model.setElement(3, 2, 0);
		model.setElement(3, 3, 1);

		return model;
	}
	Matrix& Initidentity(int M)
	{

		if (this->getRow() != M || this->getCols() != M)
		{
			throw std::invalid_argument("parameter must be same as the column/row of the matrix");
		}
		for (int i = 0; i < this->getRow(); i++)
		{
			for (int j = 0; j < this->getCols(); j++)
			{
				if (i == j)
				{
					this->setElement(i, j, 1);
				}
				else {
					this->setElement(i, j, 0);
				}
			}
		}
		return *this;
	}
	//todo view,projection, uniformmatrixes functions
	// ---------------------------------------------------------
	// Rotations in 3d space 
	//ROLL Rotation x
	Matrix& RollRotation(double alpha)
	{
		if (this->getRow() != 4 || this->getCols() != 4)
		{
			throw std::invalid_argument("Invalid argument: value for dimenstions row/cols must be 4x4!!!.");

		}
		double rad = alpha * PI / 180.0;

		this->setElement(0, 0, cos(rad));  this->setElement(0, 1, -sin(rad));  this->setElement(0, 2, 0);  this->setElement(0, 3, 0);
		this->setElement(1, 0, sin(rad));  this->setElement(1, 1, cos(rad));  this->setElement(1, 2, 0);  this->setElement(1, 3, 0);
		this->setElement(2, 0, 0);         this->setElement(2, 1, 0);         this->setElement(2, 2, 1);  this->setElement(2, 3, 0);
		this->setElement(3, 0, 0);         this->setElement(3, 1, 0);         this->setElement(3, 2, 0);  this->setElement(3, 3, 1);



		return *this;

	}
	//PITCH Rotation y
	Matrix& PitchRotation(double alpha) {
		// Ensure matrix is 4x4
		if (this->getRow() != 4 || this->getCols() != 4) {
			throw std::invalid_argument("Invalid argument: Matrix dimensions must be 4x4.");
		}

		// Convert degrees to radians
		double rad = alpha * PI / 180.0;


		this->setElement(0, 0, 1);  this->setElement(0, 1, 0);          this->setElement(0, 2, 0);          this->setElement(0, 3, 0);
		this->setElement(1, 0, 0);  this->setElement(1, 1, cos(rad));   this->setElement(1, 2, sin(rad));   this->setElement(1, 3, 0);
		this->setElement(2, 0, 0);  this->setElement(2, 1, -sin(rad));   this->setElement(2, 2, cos(rad));   this->setElement(2, 3, 0);
		this->setElement(3, 0, 0);  this->setElement(3, 1, 0);          this->setElement(3, 2, 0);          this->setElement(3, 3, 1);

		// Return reference to the current matrix
		return *this;
	}
	//YAW Rotation y
	Matrix& YawRotation(double alpha)
	{
		if (this->getRow() != 4 || this->getCols() != 4)
		{
			throw std::invalid_argument("Invalid argument: value for dimenstions row/cols must be 4x4!!!.");

		}
		double rad = alpha * PI / 180.0;

		this->setElement(0, 0, cos(rad));  this->setElement(0, 1, 0);  this->setElement(0, 2, sin(rad));  this->setElement(0, 3, 0);
		this->setElement(1, 0, 0);         this->setElement(1, 1, 1);  this->setElement(1, 2, 0);         this->setElement(1, 3, 0);
		this->setElement(2, 0, -sin(rad));  this->setElement(2, 1, 0);  this->setElement(2, 2, cos(rad));  this->setElement(2, 3, 0);
		this->setElement(3, 0, 0);         this->setElement(3, 1, 0);  this->setElement(3, 2, 0);        this->setElement(3, 3, 1);



		return *this;

	}


	//Translate matrix function 
	Matrix& Translate(Matrix<float>& model, Vector3F<float>& Vec)
	{
		//sets up identity matrix 
		model.Initidentity(4);
		//first  row
		model.setElement(0, 3, Vec.getX3D());
		//second row
		model.setElement(1, 3, Vec.getY3D());
		//third row
		model.setElement(2, 3, Vec.getZ3D());


		return model;

	}


	//Rotate Matrix functin
	Matrix<float>& Rotate(Matrix<float>& model, double& radians, Vector3F<float>& Vec)
	{
		try {
			Matrix<float> MYAW(4, 4, 1.0f);
			MYAW = YawRotation(radians);
			Matrix<float> MPITCH(4, 4, 1.0f);
			MPITCH = PitchRotation(radians);
			Matrix<float> MROLL(4, 4, 1.0f);
			MROLL = RollRotation(radians);



			model = MYAW * MPITCH * MROLL;


			return model;
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Rotate function gives::" << ex.what() << std::endl;
		}


	}

	// Scale matrix function
	Matrix& Scale(Matrix<float>& model, Vector3F<float>& Vec)
	{
		//sets up identity matrix 
		model.Initidentity(4);
		//first row
		model.setElement(0, 0, Vec.getX3D());
		//second row
		model.setElement(1, 1, Vec.getY3D());
		//third row
		model.setElement(2, 2, Vec.getZ3D());


		return model;

	}
	//look at function 
	Matrix& LookOfCamera(const Vector3F<float>& CameraP, const Vector3F<float>& CameraT, const Vector3F<float>& CameraU)
	{

		//forward vector
		Vector3F<float> forward = (CameraT - CameraP).Normalize3d();
		
		//right vectorforward
		Vector3F<float>right = CameraU.CrossProduct(forward).Normalize3d();
		//true_up vector
		Vector3F<float> true_up = forward.CrossProduct(right);

		

		//first row
		this->setElement(0, 0, right.getX3D());
		this->setElement(0, 1, right.getY3D());
		this->setElement(0, 2, right.getZ3D());
		this->setElement(0, 3, -right.Dotproduct(CameraP));
		//second row
		this->setElement(1, 0, true_up.getX3D());
		this->setElement(1, 1, true_up.getY3D());
		this->setElement(1, 2, true_up.getZ3D());
		this->setElement(1, 3, -true_up.Dotproduct(CameraP));
		//third row 
		this->setElement(2, 0, -forward.getX3D());
		this->setElement(2, 1, -forward.getY3D());
		this->setElement(2, 2, -forward.getZ3D());
		this->setElement(2, 3, forward.Dotproduct(CameraP));
		//forth row
		this->setElement(3, 0, 0);
		this->setElement(3, 1, 0);
		this->setElement(3, 2, 0);
		this->setElement(3, 3, 1);




		return *this;
	}
	//perspective function
	Matrix& Projection(const double& fov, const float& aspectRatio, const float& nearplane, const float& farplane)
	{
		//first row
		this->setElement(0, 0, 1.0f / (aspectRatio * tan(fov / 2)));
		this->setElement(0, 1, 0);
		this->setElement(0, 2, 0);
		this->setElement(0, 3, 0);
		//second row
		this->setElement(1, 0, 0);
		this->setElement(1, 1, 1 / tan(fov / 2));
		this->setElement(1, 2, 0);
		this->setElement(1, 3, 0);
		//third row
		this->setElement(2, 0, 0);
		this->setElement(2, 1, 0);
		this->setElement(2, 2, -(farplane + nearplane) / (farplane - nearplane));
		this->setElement(2, 3, -(2 * farplane * nearplane) / (farplane - nearplane));
		//forth row
		this->setElement(3, 0, 0);
		this->setElement(3, 1, 0);
		this->setElement(3, 2, -1);
		this->setElement(3, 3, 0);

		return *this;
	}
public:
	//encapsulation tools
	std::vector<std::vector<T>> getMatrix()
	{
		return m_matrix;
	}
	void setMatrix(std::vector<std::vector<T>> mat)
	{
		this->m_matrix = mat;
	}
	void setElement(int x, int y, const T& value)
	{
		m_matrix[x][y] = value;
	}
	int getRow()const { return this->m_M; }
	int getCols()const { return this->m_N; }

	template<Numeric T>
	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& M);

};
template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& M)
{
	for (int i = 0; i < M.getRow(); i++)
	{
		for (int j = 0; j < M.getCols(); j++)
		{
			os << M(i, j);
			// Only print a comma if it's not the last element in the row
			if (j < M.getCols() - 1)
			{
				os << ", ";
			}
		}
		os << std::endl;

	}
	return os;

}





