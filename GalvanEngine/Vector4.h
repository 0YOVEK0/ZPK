#pragma once
#include "MathUtilities.h"

class Vector4
{
public:
    float x; // X value of the vector
    float y; // Y value of the vector
    float z; // Z value of the vector
    float w; // W value of the vector

    /**
      * @brief  Default constructor that initializes "x", "y", "z", and "w" to 0
      */
    Vector4() : x(0), y(0), z(0), w(0) {};

    /**
      * @brief Constructor with parameters for "x", "y", "z", and "w" values
      */
    Vector4(float xNum, float yNum, float zNum, float wNum) :
        x(xNum), y(yNum), z(zNum), w(wNum) {}

    /**
      * @brief Default destructor
      */
    ~Vector4() = default;

    /**
       * @brief Overload of the + operator, to add one vector to another vector.
       * @param other The other vector to add.
       */
    Vector4
        operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    /**
       * @brief Overload of the - operator, to subtract one vector from another vector.
       * @param other The other vector to subtract.
       */
    Vector4
        operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w + other.w);
    }

    /**
       * @brief Overload of the * operator, to multiply a vector by a scalar.
       * @param scalar The scalar by which to multiply.
       */
    Vector4
        operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    /**
      * @brief Calculates the magnitude of the vector values
      */
    float
        magnitude() {
        return MUsqrt(x * x + y * y + z * z + w * w);
    }

    /**
       * @brief Normalizes the vector, returning a vector with the same direction
       */
    Vector4
        normalize() {
        float mag = magnitude();
        if (mag == 0) {
            return Vector4(0, 0, 0, 0);
        }
        return Vector4(x / mag, y / mag, z / mag, w / mag);
    }

    /**
      * @brief Method that returns a pointer to the vector components
      */
    float*
        data() {
        return &x;
    }

    /**
      * @brief Const method that returns a pointer to the vector components without modifying them
      */
    const float*
        data() const {
        return &x;
    }

private:

};
