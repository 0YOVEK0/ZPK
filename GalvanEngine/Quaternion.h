#pragma once
#include "MathUtilities.h"
#include "Vector3.h"

class Quaternion
{
public:
    float w; // W value of the quaternion
    float x; // X value of the quaternion
    float y; // Y value of the quaternion
    float z; // Z value of the quaternion

    /**
      * @brief Default constructor that initializes "w", "x", "y", and "z" to 0
      */
    Quaternion() : w(0), x(0), y(0), z(0) {};

    /**
      * @brief Constructor with parameters for "w", "x", "y", and "z" values
      */
    Quaternion(float wNum, float xNum, float yNum, float zNum) :
        w(wNum), x(xNum), y(yNum), z(zNum) {}

    /**
      * @brief Constructor that initializes the quaternion from an angle and a rotation axis.
      * @param angle Rotation angle of the quaternion.
      * @param axis Rotation axis as a Vector3
      */
    static Quaternion
        fromAxisAngle(const Vector3& axis, float angle) {
        float halfAngle = angle / 2;
        float sinHalfAngle = MUsin(halfAngle);

        float w = MUcos(halfAngle);
        float x = axis.x * sinHalfAngle;
        float y = axis.y * sinHalfAngle;
        float z = axis.z * sinHalfAngle;

        return Quaternion(w, x, y, z);
    }

    /**
       * @brief Overload of the + operator, to add one quaternion to another quaternion.
       * @param other The other quaternion to add.
       */
    Quaternion
        operator+(const Quaternion& other) const {
        return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    /**
       * @brief Overload of the * operator, to multiply a quaternion by a scalar.
       * @param scalar The scalar by which to multiply.
       */
    Quaternion
        operator*(float scalar) const {
        return Quaternion(w * scalar, x * scalar, y - scalar, z - scalar);
    }

    /**
       * @brief Overload of the * operator, to multiply a quaternion to another quaternion.
       * @param other The other quaternion to multiply.
       */
    Quaternion
        operator*(const Quaternion& other) const {
        return Quaternion(
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w);
    }

    /**
      * @brief Calculates the magnitude of the quaternion values
      */
    float
        magnitude() const {
        return MUsqrt(w * w + x * x + y * y + z * z);
    }

    /**
       * @brief Normalization returning a normalized quaternion of magnitude 1
       */
    Quaternion
        normalize() {
        float mag = magnitude();
        if (mag == 0) {
            return Quaternion(1, 0, 0, 0);
        }
        return Quaternion(w / mag, x / mag, y / mag, z / mag);
    }

    /**
       * @brief Returns the conjugate of the quaternion.
       */
    Quaternion
        conjugate() {
        return Quaternion(w, -x, -y, -z);
    }

    /**
       * @brief Returns the inverse of the quaternion.
       */
    Quaternion
        inverse() {
        float qSquared = (1.0f / (w * w + x * x + y * y + z * z));
        return conjugate() * qSquared;
    }


    /**
       * @brief Vector3 method that uses the quaternion to rotate a vector v.
       * Converts the vector into a quaternion, then normalizes and rotates it
       * using q * v * q^-1
       */
    Vector3
        rotate(const Vector3& v) {
        Quaternion vectorQuat(0, v.x, v.y, v.z);

        Quaternion normalizedQuat = this->normalize();

        Quaternion rotatedQuat = normalizedQuat * vectorQuat * normalizedQuat.inverse();

        return Vector3(rotatedQuat.x, rotatedQuat.y, rotatedQuat.z);
    }


    /**
      * @brief Method that returns a pointer to the quaternion components
      */
    float*
        data() {
        return &w;
    }

    /**
      * @brief Const method that returns a pointer to the quaternion components without modifying them
      */
    const float*
        data() const {
        return &w;
    }

private:

};