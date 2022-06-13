/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformMatrix.h
Project: CS230
Author: Juseung Yang
Creation date: 4/14/2022
-----------------------------------------------------------------*/
#pragma once
#include "Vec2.h"

namespace math {
    class TransformMatrix {
    public:
        TransformMatrix();

        const double* operator[](int index) const { return matrix[index]; }
        TransformMatrix operator * (TransformMatrix rhs) const;
        TransformMatrix& operator *= (TransformMatrix rhs);
        void Reset();

        vec2 operator * (vec2 rhs) const;


    protected:
        double matrix[3][3];
    };

    class TranslateMatrix : public TransformMatrix 
    {
    public:
        TranslateMatrix(ivec2 translate);
        TranslateMatrix(vec2 translate);
    };

    class RotateMatrix : public TransformMatrix 
    {
    public:
        RotateMatrix(double radians);
    };

    class ScaleMatrix : public TransformMatrix 
    {
    public:
        ScaleMatrix(vec2 scale);
    };
}
