/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Author: Juseung Yang
Assignment : Math vec2
Course : CS170
Term : 2022 Spring
Creation date: 3/21/2022
-----------------------------------------------------------------*/

namespace math
{
    constexpr vec2& vec2::operator+=(const vec2& v) noexcept
    {

        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    [[nodiscard]] constexpr vec2 operator+(const vec2& v1, const vec2& v2) noexcept
    {
        vec2 result = v1;
        result += v2;
        return result;
    }

    constexpr vec2& vec2::operator-=(const vec2& v) noexcept
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    [[nodiscard]] constexpr vec2 operator-(const vec2& v1, const vec2& v2) noexcept
    {
        vec2 result = v1;
        result -= v2;
        return result;
    }

    [[nodiscard]] constexpr vec2 operator-(const vec2& v) noexcept
    {
        return vec2(-v.x, -v.y);
    }

    constexpr vec2& vec2::operator*=(const double value) noexcept
    {
        this->x *= value;
        this->y *= value;
        return *this;
    }

    [[nodiscard]] constexpr vec2 operator*(const vec2& v, double value) noexcept
    {
        return vec2(v.x * value, v.y * value);
    }

    [[nodiscard]] constexpr vec2 operator*(double value, const vec2& v) noexcept
    {
        return vec2(v.x * value, v.y * value);
    }

    constexpr vec2& vec2::operator/=(const double value) noexcept
    {
        this->x /= value;
        this->y /= value;
        return *this;
    }

    [[nodiscard]] constexpr vec2 operator/(const vec2& v, double value) noexcept
    {
        return vec2(v.x / value, v.y / value);
    }

    //check if two vectors are equal --> if(v == v2) {...} if(v != v2){...}
        //should use std::numeric_limits<double>::epsilon() for the double version
    [[nodiscard]] constexpr bool operator==(const vec2& v1, const vec2& v2) noexcept
    {
        if (is_equal(v1.x, v2.x) == true && is_equal(v1.y, v2.y) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    [[nodiscard]] constexpr bool operator!=(const vec2& v1, const vec2& v2) noexcept
    {
        if (is_equal(v1.x, v2.x) != true && is_equal(v1.y, v2.y) != true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    [[nodiscard]] constexpr double vec2::LengthSquared() noexcept
    {
        return (x * x) + (y * y);
    }

    [[nodiscard]] inline vec2 vec2::Normalize() noexcept
    {
        vec2 result;
        result.x = x / std::sqrt(LengthSquared());
        result.y = y / std::sqrt(LengthSquared());
        return result;
    }

    //ivector

    constexpr ivec2& ivec2::operator+=(const ivec2& v) noexcept
    {
        this->x += v.x;
        this->x += v.y;
        return *this;
    }

    [[nodiscard]] constexpr ivec2 operator+(const ivec2& v1, const ivec2& v2) noexcept
    {
        ivec2 result = v1;
        result += v2;
        return result;
    }

    constexpr ivec2& ivec2::operator-=(const ivec2& v) noexcept
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    [[nodiscard]] constexpr ivec2 operator-(const ivec2& v1, const ivec2& v2) noexcept
    {
        ivec2 result = v1;
        result -= v2;
        return result;
    }

    [[nodiscard]] constexpr ivec2 operator-(const ivec2& v) noexcept
    {
        return ivec2(-v.x, -v.y);
    }

    constexpr ivec2& ivec2::operator*=(const int value) noexcept
    {
        this->x *= value;
        this->x *= value;
        return *this;
    }

    [[nodiscard]] constexpr ivec2 operator*(const ivec2& v, int value) noexcept
    {
        return ivec2(v.x * value, v.y * value);
    }

    [[nodiscard]] constexpr ivec2 operator*(int value, const ivec2& v) noexcept
    {
        return ivec2(v.x * value, v.y * value);
    }

    [[nodiscard]] constexpr vec2 operator*(double value, const ivec2& v) noexcept
    {
        vec2 result = static_cast<vec2>(v);
        result.x *= value;
        result.y *= value;
        return result;
    }

    [[nodiscard]] constexpr vec2 operator*(const ivec2& v, double value) noexcept
    {
        vec2 result = static_cast<vec2>(v);
        result.x *= value;
        result.y *= value;
        return result;
    }

    constexpr ivec2& ivec2::operator/=(const int value) noexcept
    {
        this->x /= value;
        this->y /= value;
        return *this;
    }

    [[nodiscard]] constexpr ivec2 operator/(const ivec2& v, int value) noexcept
    {
        ivec2 result(v.x / value, v.y / value);
        return result;
    }

    [[nodiscard]] constexpr vec2 operator/(const ivec2& v, double value) noexcept
    {
        vec2 result = static_cast<vec2>(v);
        result.x /= value;
        result.y /= value;
        return result;
    }

    [[nodiscard]] constexpr bool operator==(const ivec2& v1, const ivec2& v2) noexcept
    {
        if (is_equal(v1.x, v2.x) == true && is_equal(v1.y, v2.y) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    [[nodiscard]] constexpr bool operator!=(const ivec2& v1, const ivec2& v2) noexcept
    {
        if (is_equal(v1.x, v2.x) != true && is_equal(v1.y, v2.y) != true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    [[nodiscard]] constexpr ivec2::operator math::vec2() const noexcept
    {
        return math::vec2{ static_cast<double>(x), static_cast<double>(y) };
    }
}