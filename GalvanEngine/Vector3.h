#pragma once
#include "MathUtilities.h"

class Vector3
{
public:
    float x; // X value of the vector
    float y; // Y value of the vector
    float z; // Z value of the vector

    /**
      * @brief Default constructor that initializes "x", "y", and "z" to 0
      */
    Vector3() : x(0), y(0), z(0) {};

    /**
      * @brief Constructor with parameters for "x", "y", and "z" values
      */
    Vector3(float xNum, float yNum, float zNum) : x(xNum), y(yNum), z(zNum) {}

    /**
      * @brief Default destructor
      */
    ~Vector3() = default;

    /**
       * @brief Overload of the + operator, to add one vector to another vector.
       * @param other The other vector to add.
       */
    Vector3
        operator+(const Vector3& other) const {
        float new_xNum = x + other.x;
        float new_yNum = y + other.y;
        float new_zNum = z + other.z;
        return Vector3(new_xNum, new_yNum, new_zNum);
    }

    /**
       * @brief Overload of the - operator, to subtract one vector from another vector.
       * Optimized by doing operations directly in the return statement.
       * @param other The other vector to subtract.
       */
    Vector3
        operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    /**
       * @brief Overload of the * operator, to multiply a vector by a scalar.
       * @param scalar The scalar by which to multiply.
       */
    Vector3
        operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    /**
      * @brief Calculates the magnitude of the vector values
      */
    float
        magnitude() {
        return MUsqrt(x * x + y * y + z * z);
    }

    /**
       * @brief Normalizes the vector, returning a vector with the same direction
       */
    Vector3
        normalize() {
        float mag = magnitude();
        // If the magnitude is 0, a vector with coordinates (0,0,0) is returned
        if (mag == 0) {
            return Vector3(0, 0, 0);
        }
        return Vector3(x / mag, y / mag, z / mag);
    }

    /**
      * @brief Method that returns a pointer to the vector components
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