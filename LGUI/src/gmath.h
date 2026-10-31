#pragma once
#include <cmath>

namespace GMath {
    //struct GVec2i;
    
    struct GVec2f { 
        float x = 0;
        float y = 0;

        GVec2f operator+(const GVec2f& vec) const {
            return GVec2f {
                x + vec.x,
                y + vec.y
            };
        }

        GVec2f operator-(const GVec2f& vec) const {
            return GVec2f {
                x - vec.x,
                y - vec.y
            };
        }

        GVec2f operator*(const float& scalar) const {
            return GVec2f {
                x * scalar,
                y * scalar
            };
        }

        GVec2f operator*(const GVec2f& scalar) const {
            return GVec2f {
                x * scalar.x,
                y * scalar.y
            };
        }

        GVec2f operator/(const float& scalar) const {
            return GVec2f {
                x / scalar,
                y / scalar
            };
        }

        GVec2f operator/(const GVec2f& scalar) const {
            return GVec2f {
                x / scalar.x,
                y / scalar.y
            };
        }
    };

    //cp++ hates this one specificly
    /*
    struct GVec2i { 
        int x = 0;
        int y = 0;

        GVec2f asFloat() {
            return GVec2f {x, y};
        }

        GVec2i operator+(const GVec2i& other) const {
            return GVec2i {
                x + other.x,
                y + other.y
            };
        }

        GVec2i operator-(const GVec2i& other) const {
            return GVec2i {
                x - other.x,
                y - other.y
            };
        }
    };
    */

    struct GMatrix2x2f {
        float a = 1; float b = 1;
        float c = 1; float d = 1;

        GVec2f transform(GVec2f vec) {
            return GVec2f { vec.x * a + vec.y * b , vec.x * c + vec.y * d };
        }
    };

    //graphics ahh
    struct UDim2 {
        GVec2f scale {0, 0}; //int
        GVec2f offset  {0, 0};
    };

    struct Color4 {
        int r;
        int g;
        int b;
        int a;
        
        RAYLIB_H::Color asRL() {
            return RAYLIB_H::Color {
                static_cast<unsigned char>(r),
                static_cast<unsigned char>(g),
                static_cast<unsigned char>(b),
                static_cast<unsigned char>(a)
            };
        };
    };
}