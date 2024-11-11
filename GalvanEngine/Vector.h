#pragma once
#include "Prerequisites.h"

class
    Vector2 {
public:
    /*Constructor*/

    //Construtctor
    Vector2(float x1 = 0, float y1 = 0) : x(x1), y(y1) {}
    ~Vector2() = default;


    /*Sobrecarga de Operadores*/
    Vector2
        operator+(const Vector2& other) {
        Vector2 resultado;
        resultado.x = x + other.x;
        resultado.y = y + other.y;
        return resultado;
    };

    Vector2
        operator-(const Vector2& other) {
        Vector2 resultado;
        resultado.x = x - other.x;
        resultado.y = y - other.y;
        return resultado;
    };

    Vector2
        operator*(const float& escalar) {
        return Vector2(x * escalar, y * escalar);
    }

    /*Metodos de operacion*/

    float
        magnitud() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    /*Metodos de operacion*/

    Vector2
        normalize(float& magnitud) {
        Vector2 resultado;
        if (magnitud == 0) {
            return Vector2(0, 0);
        }
        else {
            resultado.x / magnitud;
            resultado.y / magnitud;
            return resultado;
        }

    }

    float*
        data() {
        return &x, & y;
    }

    const float*
        data() const {
        return &x, & y;
    }

    //Variables
    float x;
    float y;
};
