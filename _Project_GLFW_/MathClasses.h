#pragma once
#include "WindowComponent.h"
#include "InputSystem.h"
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <cmath>
#include <type_traits>






const double PI = 3.14159265358979323846;
const int Width = 1920;
const int Height = 1080;


template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
class Vector2F
{
    T X;
    T Y;

public:
    Vector2F(T x, T y) :X(x), Y(y) {}
    Vector2F() = default;

    Vector2F& operator=(const Vector2F<T>& other)
    {
        if (this == &other) 
        {
            return *this;
        }
        X = other.get_X();
        Y = other.get_Y();
        return *this;
    }
    Vector2F(const Vector2F<T>& other)
    {
        X = other.get_X();
        Y = other.get_Y();
    }
    T get_X() const
    {
        return X;
    }
    T get_Y() const
    {
        return Y;
    }
    void set_X(T x)
    {
        this->X = x;
    }
    void set_Y(T y)
    {
        this->Y = y;
    }

    std::string ToString() const
    {
        return "(" + std::to_string(X) + "," + std::to_string(Y)  + ")" + "\n";
    }

    //returning the length of the vector or in another words hypotenus of the triangle 
    T Length_Vector2f()
    {
        return sqrt(X * X + Y * Y);
    }
    // overloading dot product for my vector2f c++ feature:)
    T dotproduct(const Vector2F& r)
    {
        return X * r.get_X() + Y * r.get_Y();
    }
    // returning vector it self after normalization(or making it equal to 1)
    Vector2F normalization()
    {
        T length = Length_Vector2f();

        X /= length;
        Y /= length;

        return *this;
    }
    static Vector2F<double> cursorPos() {

        double xpos, ypos;
        glfwGetCursorPos(Window::mywindow, &xpos, &ypos);
        return Vector2F<double>(xpos, ypos);

    }
    // functions for basic operations with vectors 
    //this is to add another vector 2f 
    Vector2F operator+(const Vector2F& other)const
    {
        return Vector2F(X + other.get_X(), Y + other.get_Y());
    }
    Vector2F operator+=(const Vector2F& other)
    {
        return Vector2F(X += other.get_X(), Y += other.get_Y());
    }
    Vector2F operator-(const Vector2F& other)const
    {
        return Vector2F(X - other.get_X(), Y - other.get_Y());
    }
    Vector2F operator-=(const Vector2F& other)
    {
        return Vector2F(X -= other.get_X(), Y -= other.get_Y());
    }
    Vector2F operator*(const Vector2F& other)const
    {
        return Vector2F(X * other.get_X(), Y * other.get_Y());
    }
    Vector2F operator/(const Vector2F& other)const
    {
        return Vector2F(X / other.get_X(), Y / other.get_Y());
    }
    Vector2F operator/=(const Vector2F& other)
    {
        return Vector2F(X /= other.get_X(), Y /= other.get_Y());
    }
    Vector2F operator*=(const Vector2F& other)
    {
        return Vector2F(X *= other.get_X(), Y *= other.get_Y());
    }
    Vector2F operator+(const T& num)const
    {
        return Vector2F(X + num, Y + num);
    }
    Vector2F operator-(const T& num)const
    {
        return Vector2F(X - num, Y - num);
    }
    Vector2F operator*(const T& num)const
    {
        return Vector2F(X * num, Y * num);
    }
    Vector2F operator/(const T& num)const
    {
        return Vector2F(X / num, Y / num);
    }

    Vector2F Rotate(const T& angle) 
    {
        T rad = angle * (3.14159265358 / 180);
        T sin = std::sin(rad);
        T cos = std::cos(rad);

        return Vector2F(cos * X - sin * Y, sin * X + cos * Y);
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
    T x;
    T y;
    T z;
public:
    Vector3F(T X, T Y, T Z):x(X),y(Y),z(Z){}
    Vector3F() = default;
    Vector3F& operator=(const Vector3F<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }
        x = other.getX3D();
        y = other.getY3D();
        z = other.getX3D();
        return *this;
    }
    Vector3F(const Vector3F<T>& other)
    {
        x = other.getX3D();
        y = other.getY3D();
        z = other.getZ3D();
    }
    T getX3D()const 
    {
        return x;
    }
    T getY3D()const 
    {
        return y;
    }
    T getZ3D()const 
    {
        return z;
    }
    void setX3D(T x) 
    {
        this->x = x;
    }
    void setY3D(T y) 
    {
        this->y = y;
    }
    void setZ3D(T z) 
    {
        this->z = z;
    }
public:
    
    T Length_Vector3f() 
    {
        return  sqrt(x * x + y * y + z * z);
    }
    Vector3F CrossProduct(const Vector3F& Vec) const 
    {
        return Vector3F( y * Vec.z - z * Vec.y, z * Vec.x - x * Vec.z, x * Vec.y - y * Vec.x);
    }
    Vector3F& normalize3d() 
    {
        T length = Length_Vector3f();

        x /= length;
        y /= length;
        z /= length;


        return *this;
    }
    
    T dotproduct(const Vector3F& r) 
    {
        return x * r.getX3D() + y * r.getY3D() + z * r.getZ3D();
    }
   
    Vector3F operator+(const Vector3F& other)const
    {
        return Vector3F(x + other.getX3D(), y + other.getY3D(), z + other.getZ3D());
    }
    Vector3F operator+=(const Vector3F& other)
    {
        return Vector3F(x += other.getX3D(), y += other.getY3D(), z += other.getZ3D());
    }
    Vector3F operator-(const Vector3F& other)const
    {
        return Vector3F(x - other.getX3D(), y - other.getY3D(), z - other.getZ3D());
    }
    Vector3F operator-=(const Vector3F& other)
    {
        return Vector3F(x -= other.getX3D(), y -= other.getY3D(), z -= other.getZ3D());
    }
    Vector3F operator*(const Vector3F& other) const
    {
        return Vector3F(x * other.getX3D(), y * other.getY3D(), z * other.getZ3D());
    }
    Vector3F operator*=(const Vector3F& other)
    {
        return Vector3F(x *= other.getX3D(), y *= other.getY3D(), z *= other.getZ3D());
    }
    Vector3F operator/(const Vector3F& other) const
    {
        return Vector3F(x / other.getX3D(), y / other.getY3D(), z / other.getZ3D());
    }
    Vector3F operator/=(const Vector3F& other)
    {
        return Vector3F(x /= other.getX3D(), y /= other.getY3D(), z /= other.getZ3D());
    }
    Vector3F operator+(const T& other) const
    {
        return Vector3F(x + other, y + other, z + other);
    }
    Vector3F operator-(const T& other)const
    {
        return Vector3F(x - other, y - other, z - other);
    }
    Vector3F operator*(const T& other)const
    {
        return Vector3F(x * other, y * other, z * other);
    }
    Vector3F operator/(const T& other)const
    {
        return Vector3F(x / other, y / other, z / other);
    }

    Vector3F  crossproduct(Vector3F vector) 
    {
        T X_x = y * vector.getZ3D() - z * vector.getY3D();
        T Y_y = z * vector.getX3D() - x * vector.getZ3D();
        T Z_z = x * vector.getY3D() - y * vector.getX3D();


        return Vector3F(X_x, Y_y, Z_z);
    }

    std::string to_String()const 
    {
        return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")"+"\n";
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
    T x;
    T y;
    T z;
    T w;
public:
    //functions
    Quatornion(T x, T y, T z, T w) :x(x), y(y), z(z), w(w) {}
    Quatornion() = default;
    //todo  *  operators and alos << operator
    Quatornion operator*(const Quatornion& other)
    {
        T w_ = w * other.get_w() - x * other.get_x() - y * other.get_y() - z * other.get_z();
        T x_ = x * other.get_w() + w * other.get_x() + y * other.get_z() - z * other.get_y();
        T y_ = y * other.get_w() + w * other.get_y() + z * other.get_x() - x * other.get_z();
        T z_ = z * other.get_w() + w * other.get_z() + x * other.get_y() - y * other.get_x();

        return  Quatornion(x_, y_, z_, w_);
    }
    Quatornion operator*(const Vector3F<T>& other)
    {
        T w_ = -x * other.getX3D() - y * other.getY3D() - z * other.getZ3D();
        T x_ = w * other.getX3D() + y * other.getZ3D() - z * other.getY3D();
        T y_ = w * other.getY3D() + z * other.getX3D() - x * other.getZ3D();
        T z_ = w * other.getZ3D() + x * other.getY3D() - y * other.getX3D();

        return  Quaternion(x_, y_, z_, w_);
    }


public:
    T quatornion_Length()
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }
    Quatornion normalization()
    {
        T length = quatornion_Length();
        x /= length;
        y /= length;
        z /= length;
        w /= length;

        return *this;
    }
    Quatornion conjugate()
    {
        return  Quatornion(-x, -y, -z, w);
    }
    //r should be (1,1,0)normalized for vertical spinning 
    Quatornion Rotation(double& alpha, Vector3F<int>& r)
    {
        r.normalize3d();
        double rad = alpha * PI / 180.0;
        Quatornion Q1(0, 1, 0, 0);
        Quatornion Q2(cos(rad / 2), r.getX3D() * sin(rad / 2), r.getY3D() * sin(rad / 2), r.getZ3D() * sin(rad / 2));
        Quatornion Q3 = Q2 * Q1 * Q2;

        return Q3;

    }
public:
    // getters and setters
    T get_x()const { return this->x; }
    T get_y()const { return this->y; }
    T get_z()const { return this->z; }
    T get_w()const { return this->w; }
    void set_x(T& x) { this->x = x; }
    void set_y(T& y) { this->y = y; }
    void set_z(T& z) { this->z = z; }
    void set_w(T& w) { this->w = w; }
};

template<Numeric T>
class Matrix  
{
    int M;
    int N; 
    std::vector<std::vector<T>> matrix;
public:
    //standart tools/operators
    Matrix() = default;
    Matrix(int m , int n  , const T& initial ):M(m), N(n)
    {
        
        if (m <= 0 || n <= 0) 
        {
            throw std::invalid_argument("Matrix dimensions cant be negative/0");
            
        }
        matrix.resize(m);
        for (int i = 0; i < matrix.size(); i++) 
        {
            matrix[i].resize(n, initial);
        }
        

    }
    // copy constructor
    Matrix(const Matrix& other) 
    {
        matrix = other.matrix;
        M = other.M;
        N = other.N;
    }
    //assignment operator
    Matrix& operator=( const Matrix<T>& other) 
    {
        if (this == &other)
        {
            return *this;
        }
        int newrow = other.M;
        int newcol = other.N;

        matrix.resize(newrow);
        for (int i = 0; i < matrix.size(); i++) 
        {
            matrix[i].resize(newcol);
        }
        for (int i = 0; i < newrow; i++) {
            for (int j = 0; j < newcol; j++) {
                matrix[i][j] = other.matrix[i][j];
            }
        }
        M = newrow;
        N = newcol;

        return *this;
    }
    const T& operator()(const int& row, const int& col) const
    {
        return this->matrix[row][col];
    }
   
    T& operator()(const int& row, const int& col) 
    {
        return this->matrix[row][col];
    }
  
public:
    //mathmatical operations
    Matrix<T> operator*(const Matrix<T>& other) 
    {
        if (this->N != other.M) {
           throw std::invalid_argument("Matrix dimensions do not match for multiplication");
        }
        int rows = other.M;
        int cols = other.N;
        Matrix result(rows, cols, 0.0);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int k = 0; k < rows; k++) {
                    result(i, j) += (*this)(i,k) * other(k, j);
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
        Matrix result(M, N, 0.0);

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                result(i, j) = this->matrix[i][j] * other;
            }
        }

        return result;
    }
    //for 3d rotation by object's axis
    Matrix& ConvertQuatornian(Matrix<float>& model, const Quatornion<float>& q)
    {
        
        float xx = q.get_x() * q.get_x(), yy = q.get_y() * q.get_y(), zz = q.get_z() * q.get_z();
        float xy = q.get_x() * q.get_y(), xz = q.get_x() * q.get_z(), yz = q.get_y() * q.get_z();
        float wx = q.get_w() * q.get_x(), wy = q.get_w() * q.get_y(), wz = q.get_w() * q.get_z();
        //first row
        model.setElement(0, 0, 1 - 2*(yy + zz));
        model.setElement(0, 1, 2*(xy - wz));
        model.setElement(0, 2, 2*(xz + wy));
        model.setElement(0, 3, 0);
        //second row
        model.setElement(1, 0, 2*(xy + wz));
        model.setElement(1, 1, 1 - 2*(xx + zz));
        model.setElement(1, 2, 2*(yz - wx));
        model.setElement(1, 3, 0);
        //third row
        model.setElement(2, 0, 2*(xz - wy));
        model.setElement(2, 1, 2*(yz + wx));
        model.setElement(2, 2, 1 - 2*(xx + yy));
        model.setElement(2, 3, 0);
        //forth row
        model.setElement(3, 0, 0);
        model.setElement(3, 1, 0);
        model.setElement(3, 2, 0);
        model.setElement(3, 3, 1);

        return model;
    }
    Matrix& initidentity(int M)
    {

        if (this->get_row() != M || this->get_cols() != M) 
        {
            throw std::invalid_argument("parameter must be same as the column/row of the matrix");
        }
        for (int i = 0; i < this->get_row(); i++) 
        {
            for (int j = 0; j < this->get_cols(); j++)
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
    //ROLL Rotation
    Matrix& RollRotation(double alpha)
    {
        if (this->get_row() != 4 || this->get_cols() != 4)
        {
            throw std::invalid_argument("Invalid argument: value for dimenstions row/cols must be 4x4!!!.");

        }
        double rad = alpha * PI / 180.0;

        this->setElement(0, 0, cos(rad));  this->setElement(0, 1,-sin(rad));  this->setElement(0, 2, 0);  this->setElement(0, 3, 0);
        this->setElement(1, 0, sin(rad));  this->setElement(1, 1, cos(rad));  this->setElement(1, 2, 0);  this->setElement(1, 3, 0);
        this->setElement(2, 0, 0);         this->setElement(2, 1, 0);         this->setElement(2, 2, 1);  this->setElement(2, 3, 0);
        this->setElement(3, 0, 0);         this->setElement(3, 1, 0);         this->setElement(3, 2, 0);  this->setElement(3, 3, 1);



        return *this;

    }
    //PITCH Rotation
    Matrix& PitchRotation(double alpha) {
        // Ensure matrix is 4x4
        if (this->get_row() != 4 || this->get_cols() != 4) {
            throw std::invalid_argument("Invalid argument: Matrix dimensions must be 4x4.");
        }

        // Convert degrees to radians
        double rad = alpha * PI / 180.0;

       
        this->setElement(0, 0, 1);  this->setElement(0, 1, 0);          this->setElement(0, 2, 0);          this->setElement(0, 3, 0);
        this->setElement(1, 0, 0);  this->setElement(1, 1, cos(rad));   this->setElement(1, 2, sin(rad));   this->setElement(1, 3, 0);
        this->setElement(2, 0, 0);  this->setElement(2, 1,-sin(rad));   this->setElement(2, 2, cos(rad));   this->setElement(2, 3, 0);
        this->setElement(3, 0, 0);  this->setElement(3, 1, 0);          this->setElement(3, 2, 0);          this->setElement(3, 3, 1);

        // Return reference to the current matrix
        return *this;
    }
    //YAW Rotation
    Matrix& YawRotation(double alpha)
     {
         if (this->get_row() != 4 || this->get_cols() != 4)
         {
             throw std::invalid_argument("Invalid argument: value for dimenstions row/cols must be 4x4!!!.");

         }
         double rad = alpha * PI / 180.0;

         this->setElement(0, 0, cos(rad));  this->setElement(0, 1, 0);  this->setElement(0, 2,sin(rad));  this->setElement(0, 3, 0);     
         this->setElement(1, 0, 0);         this->setElement(1, 1, 1);  this->setElement(1, 2, 0);         this->setElement(1, 3, 0);
         this->setElement(2, 0, -sin(rad));  this->setElement(2, 1, 0);  this->setElement(2, 2, cos(rad));  this->setElement(2, 3, 0);
         this->setElement(3, 0, 0);         this->setElement(3, 1, 0);  this->setElement(3, 2, 0 );        this->setElement(3, 3, 1);
         
         

         return *this;

     }

    
    //Translate matrix function 
    Matrix& Translate(Matrix<float>& model, Vector3F<float>& Vec) 
    {
        //sets up identity matrix 
        model.initidentity(4);
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
            std::cerr <<"Rotate function gives::" << ex.what() << std::endl;
        }
       

    }
    
    // Scale matrix function
    Matrix& Scale(Matrix<float>& model, Vector3F<float>& Vec)
    {
        //sets up identity matrix 
        model.initidentity(4);
        //first row
        model.setElement(0, 0, Vec.getX3D());
        //second row
        model.setElement(1, 1, Vec.getY3D());
        //third row
        model.setElement(2, 2, Vec.getZ3D());
       

        return model;

    }
    //look at function 
    Matrix& LookOfCamera(Vector3F<float>& CameraP, Vector3F<float>& CameraT, Vector3F<float>& CameraU) 
    {  
       //forward vector
       Vector3F<float> forward = (CameraT - CameraP).normalize3d();
       //right vector
       Vector3F<float> right = CameraU.CrossProduct(forward).normalize3d();
       //true_up vector
       Vector3F<float> true_up= forward.CrossProduct(right);
      

       
       //first row
       this->setElement(0, 0, right.getX3D());
       this->setElement(0, 1, right.getY3D());
       this->setElement(0, 2, right.getZ3D());
       this->setElement(0, 3, -right.dotproduct(CameraP));
       //second row
       this->setElement(1, 0, true_up.getX3D());
       this->setElement(1, 1, true_up.getY3D());
       this->setElement(1, 2, true_up.getZ3D());
       this->setElement(1, 3, -true_up.dotproduct(CameraP));
       //third row 
       this->setElement(2, 0, -forward.getX3D());
       this->setElement(2, 1, -forward.getY3D());
       this->setElement(2, 2, -forward.getZ3D());
       this->setElement(2, 3, forward.dotproduct(CameraP));
       //forth row
       this->setElement(3, 0, 0);
       this->setElement(3, 1, 0);
       this->setElement(3, 2, 0);
       this->setElement(3, 3, 1);

       return *this;
    }
    //perspective function
    Matrix& Projection(double& fov, float& aspectRatio, float& nearplane, float& farplane)
    {
        //first row
        this->setElement(0, 0, 1 / aspectRatio * tan(fov / 2));
        this->setElement(0, 1, 0);
        this->setElement(0, 2, 0);
        this->setElement(0, 3, 0);
        //second row
        this->setElement(1, 0, 0);
        this->setElement(1, 1, 1/tan(fov/2));
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
        return matrix;
    }
    void setMatrix(std::vector<std::vector<T>> mat) 
    {
        this->matrix = mat;
    }
    void setElement(int x, int y, const T& value) 
    {
        matrix[x][y] = value;
    }
    int get_row()const { return this->M; }
    int get_cols()const { return this->N; }
    
    template<Numeric T>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& M);
    
};
template<Numeric T> 
std::ostream& operator<<(std::ostream& os, const Matrix<T>& M) 
{
    for (int i = 0; i < M.get_row(); i++)
    {
        for (int j = 0; j < M.get_cols(); j++)
        {
            os << M(i, j);
            // Only print a comma if it's not the last element in the row
            if (j < M.get_cols() - 1)
            {
                os << ", ";
            }
        }
        os << std::endl;

    }
    return os;

}





