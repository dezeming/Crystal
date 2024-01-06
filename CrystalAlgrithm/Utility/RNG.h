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

// This code comes from pbrt v3
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef __Algrithm_RNG_h__
#define __Algrithm_RNG_h__

#include <string>
#include <iostream>
#include <vector>

#include "Common.hpp"
#include "Cuda_Common.cuh"

namespace CrystalAlgrithm {

// Random Number Declarations
#define PCG32_DEFAULT_STATE 0x853c49e6748fea9bULL
#define PCG32_DEFAULT_STREAM 0xda3e39cb94b95bdbULL
#define PCG32_MULT 0x5851f42d4c957f2dULL

inline uint64_t MixBits(uint64_t v) {
    v ^= (v >> 31);
    v *= 0x7fb5d329728ea185;
    v ^= (v >> 27);
    v *= 0x81dadef4bc2dd44d;
    v ^= (v >> 33);
    return v;
}

// RNG Definition
class RNG {
public:
    // RNG Public Methods
    HOST_AND_DEVICE
        RNG() : state(PCG32_DEFAULT_STATE), inc(PCG32_DEFAULT_STREAM) {}
    HOST_AND_DEVICE
        RNG(uint64_t seqIndex, uint64_t offset) { SetSequence(seqIndex, offset); }
    HOST_AND_DEVICE
        RNG(uint64_t seqIndex) { SetSequence(seqIndex); }

    HOST_AND_DEVICE
        void SetSequence(uint64_t sequenceIndex, uint64_t offset);
    HOST_AND_DEVICE
        void SetSequence(uint64_t sequenceIndex) {
        SetSequence(sequenceIndex, MixBits(sequenceIndex));
    }

    template <typename T>
    HOST_AND_DEVICE T Uniform();

    template <typename T>
    HOST_AND_DEVICE typename std::enable_if_t<std::is_integral_v<T>, T> Uniform(T b) {
        T threshold = (~b + 1u) % b;
        while (true) {
            T r = Uniform<T>();
            if (r >= threshold)
                return r % b;
        }
    }

    HOST_AND_DEVICE
        void Advance(int64_t idelta);
    HOST_AND_DEVICE
        int64_t operator-(const RNG& other) const;

private:
    // RNG Private Members
    uint64_t state, inc;
};

// RNG Inline Method Definitions
template <typename T>
inline T RNG::Uniform() {
    return T::unimplemented;
}

template <>
inline uint32_t RNG::Uniform<uint32_t>();

template <>
inline uint32_t RNG::Uniform<uint32_t>() {
    uint64_t oldstate = state;
    state = oldstate * PCG32_MULT + inc;
    uint32_t xorshifted = (uint32_t)(((oldstate >> 18u) ^ oldstate) >> 27u);
    uint32_t rot = (uint32_t)(oldstate >> 59u);
    return (xorshifted >> rot) | (xorshifted << ((~rot + 1u) & 31));
}

template <>
inline uint64_t RNG::Uniform<uint64_t>() {
    uint64_t v0 = Uniform<uint32_t>(), v1 = Uniform<uint32_t>();
    return (v0 << 32) | v1;
}

template <>
inline int32_t RNG::Uniform<int32_t>() {
    // https://stackoverflow.com/a/13208789
    uint32_t v = Uniform<uint32_t>();
    if (v <= (uint32_t)std::numeric_limits<int32_t>::max())
        return int32_t(v);
    DCHECK_GE(v, (uint32_t)std::numeric_limits<int32_t>::min());
    return int32_t(v - std::numeric_limits<int32_t>::min()) +
        std::numeric_limits<int32_t>::min();
}

template <>
inline int64_t RNG::Uniform<int64_t>() {
    // https://stackoverflow.com/a/13208789
    uint64_t v = Uniform<uint64_t>();
    if (v <= (uint64_t)std::numeric_limits<int64_t>::max())
        // Safe to type convert directly.
        return int64_t(v);
    DCHECK_GE(v, (uint64_t)std::numeric_limits<int64_t>::min());
    return int64_t(v - std::numeric_limits<int64_t>::min()) +
        std::numeric_limits<int64_t>::min();
}

inline void RNG::SetSequence(uint64_t sequenceIndex, uint64_t seed) {
    state = 0u;
    inc = (sequenceIndex << 1u) | 1u;
    Uniform<uint32_t>();
    state += seed;
    Uniform<uint32_t>();
}

template <>
inline float RNG::Uniform<float>() {
    return std::min<float>(OneMinusEpsilon, Uniform<uint32_t>() * 0x1p-32f);
}

template <>
inline double RNG::Uniform<double>() {
    return std::min<double>(OneMinusEpsilon, Uniform<uint64_t>() * 0x1p-64);
}

inline void RNG::Advance(int64_t idelta) {
    uint64_t curMult = PCG32_MULT, curPlus = inc, accMult = 1u;
    uint64_t accPlus = 0u, delta = (uint64_t)idelta;
    while (delta > 0) {
        if (delta & 1) {
            accMult *= curMult;
            accPlus = accPlus * curMult + curPlus;
        }
        curPlus = (curMult + 1) * curPlus;
        curMult *= curMult;
        delta /= 2;
    }
    state = accMult * state + accPlus;
}

HOST_AND_DEVICE
    inline int64_t RNG::operator-(const RNG& other) const {
    CHECK_EQ(inc, other.inc);
    uint64_t curMult = PCG32_MULT, curPlus = inc, curState = other.state;
    uint64_t theBit = 1u, distance = 0u;
    while (state != curState) {
        if ((state & theBit) != (curState & theBit)) {
            curState = curState * curMult + curPlus;
            distance |= theBit;
        }
        CHECK_EQ(state & theBit, curState & theBit);
        theBit <<= 1;
        curPlus = (curMult + 1ULL) * curPlus;
        curMult *= curMult;
    }
    return (int64_t)distance;
}









}


#endif



