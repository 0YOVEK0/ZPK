#pragma once


const float PI = 3.14159265358979323846f;
const float E = 2.71828182845904523536f;

/*
  * @brief Calculates the absolute value
  * @param num Value for which the absolute value is calculated
  */
inline float
MUabs(float num) {
    if (num < 0) {
        return num * -1;
    }
    return num;
}

/*
  * @brief Calculates the square root (approximation) using the Newton method
  * @param num Value for which the square root is calculated
  */
inline float
sqrtNewthon(int num) {
    float errMargin = 0.0001; //Allowed error margin
    float estimate = 1.0; // Initial estimate
    // Continues calculating until the estimate is close to the square root of the number
    while (MUabs((estimate * estimate) - num) >= errMargin) {
        float quotient = num / estimate; // Quotient of the number and the current estimate
        float prom = (quotient + estimate) / 2.0; // Calculation for the estimate value
        estimate = prom;
    }
    return estimate;
}

/*
  * @brief Calculates the square root using the Newton-Raphson method
  * @param num Value for which the square root is calculated
  */
inline float
MUsqrt(float value) {
    // Negative values are not allowed
    if (value < 0) {
        return 0;
    }
    float x = value;
    float y = 1.0f;
    float epsilon = 0.00001f;
    while (x - y > epsilon) {
        x = (x + y) / 2.0f;
        y = value / x;
    }
    return x;
}

/**
   * Calculates the sine of an angle in radians using the Taylor series
   * @param angle Angle in radians.
   */
inline float
MUsin(float angle) {
    float result = 0.0f;
    float term = angle;
    float angle_squared = angle * angle;
    int n = 1;
    while (term > 0.000001 || term < -0.000001) {
        result += term;
        term *= -angle_squared / ((2 * n) * (2 * n + 1));
        ++n;
    }
    return result;
}

/**
   * Calculates the cosine of an angle in radians using the Taylor series
   * @param angle Angle in radians.
   */
inline float
MUcos(float angle) {
    float result = 1.0f;
    float term = 1.0f;
    float angle_squared = angle * angle;
    int n = 1;
    while (term > 1e-6f || term < -1e-6f) {
        term *= -angle_squared / ((2 * n - 1) * (2 * n));
        result += term;
        ++n;
    }
    return result;
}

/**
   * Calculates the tangent of an angle in radians, ensuring no division
   * by zero using a ternary operator (condition ? value_true : value_false)
   * @param angle Angle in radians.
   */
inline float
MUtan(float angle) {
    float tSin = MUsin(angle);
    float tCos = MUcos(angle);
    return tCos != 0.0f ? tSin / tCos : 0.0f;
}
