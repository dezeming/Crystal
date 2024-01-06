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


#include "Texture.h"

namespace CrystalAlgrithm {

// ConstantFloatTexture
ConstantFloatTexture::ConstantFloatTexture(float v) {
    val = v;
}
ConstantFloatTexture:: ~ConstantFloatTexture() {

}


// ConstantRGBATexture
ConstantRGBATexture::ConstantRGBATexture(float4 v) {
    val = v;
}
ConstantRGBATexture::~ConstantRGBATexture() {

}


// MapFloatTexture
MapFloatTexture::MapFloatTexture() {

}
MapFloatTexture::~MapFloatTexture() {

}


// MapRGBATexture
MapRGBATexture::MapRGBATexture() {

}
MapRGBATexture::~MapRGBATexture() {


}


// TextureManager
TextureManager::TextureManager() {

}
TextureManager::~TextureManager() {

}


}
