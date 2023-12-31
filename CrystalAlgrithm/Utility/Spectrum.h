/*
    Copyright (C) <2023>  <Dezeming>  <feimos@mail.ustc.edu.cn>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or any
    later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Github site: <https://github.com/dezeming/Crystal>
*/

#ifndef __algrithm_Spectrum_h__
#define __algrithm_Spectrum_h__

#include "CrystalAlgrithm/Utility/cuda_Common.cuh"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <string>

namespace CrystalAlgrithm {

HOST_AND_DEVICE inline void XYZToRGB(const float xyz[3], float rgb[3]) {
    rgb[0] = 3.240479f * xyz[0] - 1.537150f * xyz[1] - 0.498535f * xyz[2];
    rgb[1] = -0.969256f * xyz[0] + 1.875991f * xyz[1] + 0.041556f * xyz[2];
    rgb[2] = 0.055648f * xyz[0] - 0.204043f * xyz[1] + 1.057311f * xyz[2];
}

HOST_AND_DEVICE inline void RGBToXYZ(const float rgb[3], float xyz[3]) {
    xyz[0] = 0.412453f * rgb[0] + 0.357580f * rgb[1] + 0.180423f * rgb[2];
    xyz[1] = 0.212671f * rgb[0] + 0.715160f * rgb[1] + 0.072169f * rgb[2];
    xyz[2] = 0.019334f * rgb[0] + 0.119193f * rgb[1] + 0.950227f * rgb[2];
}


class Spectrum3 {
public:
    // CoefficientSpectrum Public Methods
    HOST_AND_DEVICE Spectrum3() {
        for (int i = 0; i < 3; ++i) c[i] = 0.0f;
    }

    HOST_AND_DEVICE Spectrum3(float v) {
        for (int i = 0; i < 3; ++i) c[i] = v;
    }

    HOST_AND_DEVICE Spectrum3& operator+=(const Spectrum3& s2) {
        for (int i = 0; i < 3; ++i) c[i] += s2.c[i];
        return *this;
    }
    HOST_AND_DEVICE Spectrum3 operator+(const Spectrum3& s2) const {
        Spectrum3 ret = *this;
        for (int i = 0; i < 3; ++i) ret.c[i] += s2.c[i];
        return ret;
    }
    HOST_AND_DEVICE Spectrum3 operator-(const Spectrum3& s2) const {
        Spectrum3 ret = *this;
        for (int i = 0; i < 3; ++i) ret.c[i] -= s2.c[i];
        return ret;
    }
    HOST_AND_DEVICE Spectrum3 operator/(const Spectrum3& s2) const {
        Spectrum3 ret = *this;
        for (int i = 0; i < 3; ++i) {
            ret.c[i] /= s2.c[i];
        }
        return ret;
    }
    HOST_AND_DEVICE Spectrum3 operator*(const Spectrum3& sp) const {
        Spectrum3 ret = *this;
        for (int i = 0; i < 3; ++i) ret.c[i] *= sp.c[i];
        return ret;
    }
    HOST_AND_DEVICE Spectrum3& operator*=(const Spectrum3& sp) {
        for (int i = 0; i < 3; ++i) c[i] *= sp.c[i];
        return *this;
    }
    HOST_AND_DEVICE Spectrum3 operator*(float a) const {
        Spectrum3 ret = *this;
        for (int i = 0; i < 3; ++i) ret.c[i] *= a;
        return ret;
    }
    HOST_AND_DEVICE Spectrum3& operator*=(float a) {
        for (int i = 0; i < 3; ++i) c[i] *= a;
        return *this;
    }

    HOST_AND_DEVICE Spectrum3 operator/(float a) const {
        Spectrum3 ret = *this;
        for (int i = 0; i < 3; ++i) ret.c[i] /= a;
        return ret;
    }
    HOST_AND_DEVICE Spectrum3& operator/=(float a) {
        for (int i = 0; i < 3; ++i) c[i] /= a;
        return *this;
    }
    HOST_AND_DEVICE bool operator==(const Spectrum3& sp) const {
        for (int i = 0; i < 3; ++i)
            if (c[i] != sp.c[i]) return false;
        return true;
    }
    HOST_AND_DEVICE bool operator!=(const Spectrum3& sp) const {
        return !(*this == sp);
    }
    HOST_AND_DEVICE bool IsBlack() const {
        for (int i = 0; i < 3; ++i)
            if (c[i] != 0.) return false;
        return true;
    }
    HOST_AND_DEVICE Spectrum3 Sqrt(const Spectrum3& s) {
        Spectrum3 ret;
        for (int i = 0; i < 3; ++i) ret.c[i] = sqrt(s.c[i]);
        return ret;
    }
    HOST_AND_DEVICE Spectrum3 operator-() const {
        Spectrum3 ret;
        for (int i = 0; i < 3; ++i) ret.c[i] = -c[i];
        return ret;
    }

    HOST_AND_DEVICE Spectrum3 Pow(const Spectrum3& s, float e) {
        Spectrum3 ret;
        for (int i = 0; i < 3; ++i) ret.c[i] = pow(s.c[i], e);
        return ret;
    }

    HOST_AND_DEVICE Spectrum3 Exp(const Spectrum3& s) {
        Spectrum3 ret;
        for (int i = 0; i < 3; ++i) ret.c[i] = exp(s.c[i]);
        return ret;
    }

    HOST std::string ToString() const {
        std::string str = "[ ";
        for (int i = 0; i < 3; ++i) {
            str += std::to_string(c[i]);
            if (i + 1 < 3) str += ", ";
        }
        str += " ]";
        return str;
    }
    HOST_AND_DEVICE Spectrum3 Clamp(float low = 0.0f, float high = 1.0f) const {
        Spectrum3 ret;
        for (int i = 0; i < 3; ++i)
            ret.c[i] = CrystalAlgrithm::Clamp(c[i], low, high);
        return ret;
    }
    HOST_AND_DEVICE float MaxComponentValue() const {
        float m = c[0];
        for (int i = 1; i < 3; ++i)
            m = std::max(m, c[i]);
        return m;
    }
    HOST_AND_DEVICE bool HasNaNs() const {
        for (int i = 0; i < 3; ++i)
            if (CrystalAlgrithm::isNaN(c[i])) return true;
        return false;
    }
    HOST_AND_DEVICE float& operator[](int i) {
        return c[i];
    }
    HOST_AND_DEVICE float operator[](int i) const {
        return c[i];
    }

    // Spectrum3 Public Data
    static const int nSamples = 3;

protected:
    // Spectrum3 Protected Data
    float c[nSamples];
};

class Spectrum4 {
public:
    // CoefficientSpectrum Public Methods
    HOST_AND_DEVICE Spectrum4(float v = 0.f) {
        for (int i = 0; i < 4; ++i) c[i] = v;
    }

    HOST_AND_DEVICE Spectrum4& operator+=(const Spectrum4& s2) {
        for (int i = 0; i < 4; ++i) c[i] += s2.c[i];
        return *this;
    }
    HOST_AND_DEVICE Spectrum4 operator+(const Spectrum4& s2) const {
        Spectrum4 ret = *this;
        for (int i = 0; i < 4; ++i) ret.c[i] += s2.c[i];
        return ret;
    }
    HOST_AND_DEVICE Spectrum4 operator-(const Spectrum4& s2) const {
        Spectrum4 ret = *this;
        for (int i = 0; i < 4; ++i) ret.c[i] -= s2.c[i];
        return ret;
    }
    HOST_AND_DEVICE Spectrum4 operator/(const Spectrum4& s2) const {
        Spectrum4 ret = *this;
        for (int i = 0; i < 4; ++i) {
            ret.c[i] /= s2.c[i];
        }
        return ret;
    }
    HOST_AND_DEVICE Spectrum4 operator*(const Spectrum4& sp) const {
        Spectrum4 ret = *this;
        for (int i = 0; i < 4; ++i) ret.c[i] *= sp.c[i];
        return ret;
    }
    HOST_AND_DEVICE Spectrum4& operator*=(const Spectrum4& sp) {
        for (int i = 0; i < 4; ++i) c[i] *= sp.c[i];
        return *this;
    }
    HOST_AND_DEVICE Spectrum4 operator*(float a) const {
        Spectrum4 ret = *this;
        for (int i = 0; i < 4; ++i) ret.c[i] *= a;
        return ret;
    }
    HOST_AND_DEVICE Spectrum4& operator*=(float a) {
        for (int i = 0; i < 4; ++i) c[i] *= a;
        return *this;
    }

    HOST_AND_DEVICE Spectrum4 operator/(float a) const {
        Spectrum4 ret = *this;
        for (int i = 0; i < 4; ++i) ret.c[i] /= a;
        return ret;
    }
    HOST_AND_DEVICE Spectrum4& operator/=(float a) {
        for (int i = 0; i < 4; ++i) c[i] /= a;
        return *this;
    }
    HOST_AND_DEVICE bool operator==(const Spectrum4& sp) const {
        for (int i = 0; i < 4; ++i)
            if (c[i] != sp.c[i]) return false;
        return true;
    }
    HOST_AND_DEVICE bool operator!=(const Spectrum4& sp) const {
        return !(*this == sp);
    }
    HOST_AND_DEVICE bool IsBlack() const {
        for (int i = 0; i < 4; ++i)
            if (c[i] != 0.) return false;
        return true;
    }

    HOST_AND_DEVICE Spectrum4 Sqrt(const Spectrum4& s) {
        Spectrum4 ret;
        for (int i = 0; i < 4; ++i) ret.c[i] = sqrt(s.c[i]);
        return ret;
    }

    HOST_AND_DEVICE Spectrum4 operator-() const {
        Spectrum4 ret;
        for (int i = 0; i < 4; ++i) ret.c[i] = -c[i];
        return ret;
    }

    HOST_AND_DEVICE Spectrum4 Pow(const Spectrum4& s, float e) {
        Spectrum4 ret;
        for (int i = 0; i < 4; ++i) ret.c[i] = pow(s.c[i], e);
        return ret;
    }

    HOST_AND_DEVICE Spectrum4 Exp(const Spectrum4& s) {
        Spectrum4 ret;
        for (int i = 0; i < 4; ++i) ret.c[i] = exp(s.c[i]);
        return ret;
    }

    HOST_AND_DEVICE std::string ToString() const {
        std::string str = "[ ";
        for (int i = 0; i < 4; ++i) {
            str += std::to_string(c[i]);
            if (i + 1 < 4) str += ", ";
        }
        str += " ]";
        return str;
    }
    HOST_AND_DEVICE Spectrum4 Clamp(float low = 0.0f, float high = 1.0f) const {
        Spectrum4 ret;
        for (int i = 0; i < 4; ++i)
            ret.c[i] = CrystalAlgrithm::Clamp(c[i], low, high);
        return ret;
    }
    HOST_AND_DEVICE float MaxComponentValue() const {
        float m = c[0];
        for (int i = 1; i < 4; ++i)
            m = std::max(m, c[i]);
        return m;
    }
    HOST_AND_DEVICE bool HasNaNs() const {
        for (int i = 0; i < 4; ++i)
            if (std::isnan(c[i])) return true;
        return false;
    }
    HOST_AND_DEVICE float& operator[](int i) {
        return c[i];
    }
    HOST_AND_DEVICE float operator[](int i) const {
        return c[i];
    }

    // Spectrum4 Public Data
    static const int nSamples = 4;

protected:
    // Spectrum4 Protected Data
    float c[nSamples];
};








}








#endif



