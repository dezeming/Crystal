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



/*
	pbrt source code is Copyright(c) 1998-2016
						Matt Pharr, Greg Humphreys, and Wenzel Jakob.

	This file is part of pbrt.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are
	met:

	- Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.

	- Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
	IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
	TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
	PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */


#ifndef __Algrithm_bvhTree_h__
#define __Algrithm_bvhTree_h__

#include "CrystalAlgrithm/Utility/Common.hpp"

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include <string>
#include <iostream>
#include <vector>

#include "Primitive.h"

namespace CrystalAlgrithm {


// BVHPrimitiveInfo include the information for bounding box
// input two vector:
// std::vector<BVHPrimitiveInfo> primitiveInfo(primitives.size());
// std::vector<std::shared_ptr<Primitive>> primitives;
// 
// output is BVH Tree, as well as the sorted array
// primitives will be sorted in the program, and orderedPrims can be obtained
// std::vector<std::shared_ptr<Primitive>> &orderedPrims



struct EXPORT_DLL BucketInfo {
	int count = 0;
	Bounds3f bounds;
};

// tree-shape bvh
struct EXPORT_DLL BVHNode {
	BVHNode() {
		children[0] = children[1] = nullptr;
	}
	~BVHNode() {
		if(children[0]) {
			delete children[0];
			children[0] = nullptr;
		}
		if (children[1]) {
			delete children[1];
			children[1] = nullptr;
		}
	}

	BVHNode* children[2];
	int splitAxis, firstPrimOffset, nPrimitives;
	Bounds3f bound;
	// Initialize as leaf node
	void InitLeaf(int first, int n, const Bounds3f& b) {
		firstPrimOffset = first;
		nPrimitives = n;
		bound = b;
		children[0] = children[1] = nullptr;
	}
	// Initialize as an internal node
	void InitInterior(int axis, BVHNode* c0, BVHNode* c1) {
		children[0] = c0;
		children[1] = c1;
		bound = Union(c0->bound, c1->bound);
		splitAxis = axis;
		nPrimitives = 0;
	}
};

// array-shape bvh
struct EXPORT_DLL LinearBVHNode {
	Bounds3f bounds;
	union {
		int primitivesOffset;   // leaf
		int secondChildOffset;  // interior
	};
	unsigned int nPrimitives;
	unsigned int axis;
};


struct EXPORT_DLL BVHPrimitiveInfo {
	BVHPrimitiveInfo() {}
	BVHPrimitiveInfo(size_t primitiveNumber, const Bounds3f& bounds)
		: primitiveNumber(primitiveNumber),
		bound(bounds),
		centroid(.5f * bounds.pMin + .5f * bounds.pMax) {}
	size_t primitiveNumber;
	Bounds3f bound;
	Point3f centroid;
};


// BVH

class EXPORT_DLL BVHTree {
public:
	unsigned int nodeNum;
	unsigned int primitiveNum;

	LinearBVHNode* nodes;
	Primitive* p_out;

	const int maxPrimsInNode = 2;

	BVHTree() {
		nodes = nullptr;
		p_out = nullptr;
	}

	void releaseAll() {
		if (p_out)
			delete[] p_out; 
		p_out = nullptr;

		if (nodes)
			delete[] nodes; 
		nodes = nullptr;
	}

	bool BVHBuildTree(std::vector<std::shared_ptr<Primitive>> p) {
		std::vector<std::shared_ptr<Primitive>> primitives = std::move(p);
		if (primitives.empty()) return false;

		// Initialize primitives
		std::vector<BVHPrimitiveInfo> primitiveInfo(primitives.size());
		for (size_t i = 0; i < primitives.size(); ++i)
			primitiveInfo[i] = { i, primitives[i]->WorldBound() };

		// Build BVH tree
		int totalNodes = 0;
		std::vector<std::shared_ptr<Primitive>> orderedPrims;
		orderedPrims.reserve(primitives.size());

		BVHNode* root;
		root = recursiveBuild(primitiveInfo, 0, primitives.size(),
			&totalNodes, primitives, orderedPrims);
		primitives.swap(orderedPrims);
		primitiveInfo.resize(0);

		// Compute representation of depth-first traversal of BVH tree
		nodeNum = totalNodes;
		nodes = new LinearBVHNode[totalNodes];
		int offset = 0;
		flattenBVHTree(root, &offset);

		primitiveNum = primitives.size();
		if (!p_out) p_out = new Primitive[primitiveNum];

		for (unsigned int i = 0; i < primitiveNum; i++) {
			p_out[i].typeIndex = primitives[i]->typeIndex;
			p_out[i].numIndex = primitives[i]->numIndex;
		}
	}
	BVHNode* recursiveBuild(std::vector<BVHPrimitiveInfo>& primitiveInfo,
		int start, int end, int* totalNodes,
		std::vector<std::shared_ptr<Primitive>>& primitives,
		std::vector<std::shared_ptr<Primitive>>& orderedPrims) {

		BVHNode* node = new BVHNode;
		(*totalNodes)++;
		Bounds3f bounds;
		for (int i = start; i < end; ++i)
			bounds = Union(bounds, primitiveInfo[i].bound);
		int nPrimitives = end - start;
		if (nPrimitives <= maxPrimsInNode) {
			int firstPrimOffset = orderedPrims.size();
			for (int i = start; i < end; ++i) {
				int primNum = primitiveInfo[i].primitiveNumber;
				orderedPrims.push_back(primitives[primNum]);
			}
			node->InitLeaf(firstPrimOffset, nPrimitives, bounds);
			return node;
		}
		else {
			Bounds3f centroidBounds;
			for (int i = start; i < end; ++i)
				centroidBounds = Union(centroidBounds, primitiveInfo[i].centroid);
			int dim = centroidBounds.MaximumExtent();

			int mid = (start + end) / 2;
			if (centroidBounds.pMax[dim] == centroidBounds.pMin[dim]) {
				int firstPrimOffset = orderedPrims.size();
				for (int i = start; i < end; ++i) {
					int primNum = primitiveInfo[i].primitiveNumber;
					orderedPrims.push_back(primitives[primNum]);
				}
				node->InitLeaf(firstPrimOffset, nPrimitives, bounds);
				return node;
			}
			else {
				{
					mid = (start + end) / 2;
					std::nth_element(&primitiveInfo[start], &primitiveInfo[mid],
						&primitiveInfo[end - 1] + 1,
						[dim](const BVHPrimitiveInfo& a, const BVHPrimitiveInfo& b) {
							return a.centroid[dim] < b.centroid[dim];
						});
				}
				node->InitInterior(dim,
					recursiveBuild(primitiveInfo, start, mid,
						totalNodes, primitives, orderedPrims),
					recursiveBuild(primitiveInfo, mid, end,
						totalNodes, primitives, orderedPrims));
			}
		}
	}
	int flattenBVHTree(BVHNode* node, int* offset) {
		LinearBVHNode* linearNode = &nodes[*offset];
		linearNode->bounds = node->bound;
		int myOffset = (*offset)++;
		if (node->nPrimitives > 0) {
			linearNode->primitivesOffset = node->firstPrimOffset;
			linearNode->nPrimitives = node->nPrimitives;
		}
		else {
			// Create interior flattened BVH node
			linearNode->axis = node->splitAxis;
			linearNode->nPrimitives = 0;
			flattenBVHTree(node->children[0], offset);
			linearNode->secondChildOffset = flattenBVHTree(node->children[1], offset);
		}
		return myOffset;
	}

};

HOST_AND_DEVICE inline bool IntersectBVH(CameraRay ray, LinearBVHNode* nodes, Primitive* primitives) {
	if (!nodes) return false;
	bool hit = false;

	Vector3f invDir = Vector3f(1.0 / ray.direction.x, 1.0 / ray.direction.y, 1.0 / ray.direction.z);
	int dirIsNeg[3]; dirIsNeg[0] = (invDir.x < 0.0); dirIsNeg[1] = (invDir.y < 0.0); dirIsNeg[2] = (invDir.z < 0.0);

	// Follow ray through BVH nodes to find primitive intersections
	int toVisitOffset = 0, currentNodeIndex = 0;
	int nodesToVisit[64];

	Triangle tri;
	while (true) {
		LinearBVHNode node = nodes[currentNodeIndex];
		Bounds3f bound; bound.pMin = node.bounds.pMin; bound.pMax = node.bounds.pMax;
		if (bound.IntersectP(ray, invDir, dirIsNeg)) {
			if (node.nPrimitives > 0) {
				for (unsigned int i = 0; i < node.nPrimitives; ++i) {
					unsigned int offset = (node.secondChildOffset + i);
					primitives[node.primitivesOffset + i];

					// update ray.tmax if the ray intersect the primitive
					/*
					float dis_t = hitTriangle(tri_t, ray);
					if (dis_t > 0 && dis_t < ray.hitMin) {
						ray.hitMin = dis_t;
						tri = tri_t;
						hit = true;
					}*/
				}
				if (toVisitOffset == 0) break;
				currentNodeIndex = nodesToVisit[--toVisitOffset];
			}
			else {
				// put BVH node into _nodesToVisit_ stack, advance to near
				if ((bool)(dirIsNeg[node.axis])) {
					nodesToVisit[toVisitOffset++] = currentNodeIndex + 1;
					currentNodeIndex = node.secondChildOffset;
				}
				else {
					nodesToVisit[toVisitOffset++] = node.secondChildOffset;
					currentNodeIndex = currentNodeIndex + 1;
				}
			}
		}
		else {
			if (toVisitOffset == 0) break;
			currentNodeIndex = nodesToVisit[--toVisitOffset];
		}
	}
	return hit;
}





}

#endif





