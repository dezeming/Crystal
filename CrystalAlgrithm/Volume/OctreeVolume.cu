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

#include "OctreeVolume.h"

namespace CrystalAlgrithm {

OctreeVolume::OctreeVolume() {

    MinBoundResolution = 6;

}

OctreeVolume::~OctreeVolume() {



}

void OctreeVolume::calculateHierachy() {

    unsigned int nodesCount = 0;
    unsigned int finalBoundResolution;
    std::vector<unsigned int> nodesCountEachHierachy;
    for (unsigned int p = MinBoundResolution; ;p *= 2) {

        unsigned int xBoundCount = volumeInfo.resolution.x / p;
        if (volumeInfo.resolution.x % p >= p / 2) xBoundCount++;
        unsigned int yBoundCount = volumeInfo.resolution.y / p;
        if (volumeInfo.resolution.y % p >= p / 2) yBoundCount++;
        unsigned int zBoundCount = volumeInfo.resolution.z / p;
        if (volumeInfo.resolution.z % p >= p / 2) zBoundCount++;

        unsigned int boundsCount = xBoundCount * yBoundCount * zBoundCount;
        nodesCount += boundsCount;

        nodesCountEachHierachy.push_back(boundsCount);

        if (boundsCount == 1) {
            finalBoundResolution = p;
            break;
        }
    }

    volumeInfo.resolution;



}







}


