/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Author: Juseung Yang
Assignment : Math vec2
Course : CS170
Term : 2022 Spring
Creation date: 3/21/2022
-----------------------------------------------------------------*/
#pragma once
#include <cmath>
#include <limits>

namespace math
{
    [[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }

    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

    struct vec2
    {
        double x = 0;
        double y = 0;

        [[nodiscard]] constexpr vec2() noexcept = default;

        [[nodiscard]] constexpr explicit vec2(double value) noexcept
            : x(value), y(value)
        {
        }

        [[nodiscard]] constexpr vec2(double x_value, double y_value) noexcept
            : x(x_value), y(y_value)
        {
        }

        constexpr vec2& operator+=(const vec2& v) noexcept;

        constexpr vec2& operator-=(const vec2& v) noexcept;

        constexpr vec2& operator*=(const double value) noexcept;

        constexpr vec2& operator/=(const double value) noexcept;

        [[nodiscard]] constexpr double LengthSquared() noexcept;

        [[nodiscard]] inline vec2 Normalize() noexcept;

    };

    [[nodiscard]] constexpr vec2 operator+(const vec2& v1, const vec2& v2) noexcept;

    [[nodiscard]] constexpr vec2 operator-(const vec2& v1, const vec2& v2) noexcept;

    [[nodiscard]] constexpr vec2 operator-(const vec2& v) noexcept;

    [[nodiscard]] constexpr vec2 operator*(const vec2& v, double value) noexcept;

    [[nodiscard]] constexpr vec2 operator*(double value, const vec2& v) noexcept;

    [[nodiscard]] constexpr vec2 operator/(const vec2& v, double value) noexcept;

    [[nodiscard]] constexpr bool operator==(const vec2& v1, const vec2& v2) noexcept;

    [[nodiscard]] constexpr bool operator!= (const vec2& v1, const vec2& v2) noexcept;

    struct ivec2
    {

        int x = 0;
        int y = 0;

        [[nodiscard]] constexpr ivec2() noexcept = default;

        [[nodiscard]] constexpr explicit ivec2(int value) noexcept
            : x(value), y(value)
        {}

        [[nodiscard]] constexpr ivec2(int x_value, int y_value) noexcept
            : x(x_value), y(y_value)
        {}

        constexpr ivec2& operator+=(const ivec2& v) noexcept;

        constexpr ivec2& operator-=(const ivec2& v) noexcept;

        constexpr ivec2& operator*=(const int value) noexcept;

        constexpr ivec2& operator/=(const int value) noexcept;

        [[nodiscard]] constexpr operator vec2() const noexcept;

        explicit constexpr operator vec2() { return vec2{ static_cast<double>(x),static_cast<double>(y) }; }
    };

    [[nodiscard]] constexpr ivec2 operator+(const ivec2& v1, const ivec2& v2) noexcept;

    [[nodiscard]] constexpr ivec2 operator-(const ivec2& v1, const ivec2& v2) noexcept;

    [[nodiscard]] constexpr ivec2 operator-(const ivec2& v) noexcept;

    [[nodiscard]] constexpr ivec2 operator*(int value, const ivec2& v) noexcept;

    [[nodiscard]] constexpr ivec2 operator*(const ivec2& v, int value) noexcept;

    [[nodiscard]] constexpr vec2 operator*(double value, const ivec2& v) noexcept;

    [[nodiscard]] constexpr vec2 operator*(const ivec2& v, double value) noexcept;

    [[nodiscard]] constexpr ivec2 operator/(const ivec2& v, int value) noexcept;

    [[nodiscard]] constexpr vec2 operator/(const ivec2& v, double value) noexcept;

    [[nodiscard]] constexpr bool operator==(const ivec2& v1, const ivec2& v2) noexcept;

    [[nodiscard]] constexpr bool operator!=(const ivec2& v1, const ivec2& v2) noexcept;
}

#include "Vec2.inl"