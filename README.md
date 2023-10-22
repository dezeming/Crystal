# <img src="Resources/Images/logo.png" width="150" >

> <font size=5>Crystal - A `modern`, `fashionable`, `high-quality` 3D visualization tool for medical images</font>

<img src="Resources/Images/cVRT1.png" width="390" >

> <font size=5> The rendering results above were generated by my another project - a 'real-time', 'realistic' volume rendering engine. Realistic rendering will be a very important part of this project. </font>

---
# <img src="Resources/Images/crystal.png" width="40" > Build this project

## Computer configuration

|  Device   |  Minimum configuration | Recommended settings ((equal to or greater than)) |
|  ----  | ----  | ----  |
| System  | Windows 10 | Windows 10/11 |
| CPU RAM | 16GB | 32GB |
| GPU  | Nvidia RTX 2060 | Nvidia RTX 4070 |
| GPU VRAM | - | - |

|  Software   |  Minimum version | Recommended settings ((equal to or greater than)) |
|  ----  | ----  | ----  |
| Visual Studio | 2019 | 2019 |
| OpenGL | version 4.3 | - |

## Dependent third-party libraries

### <img src="Resources/Images/logo-qt.png" width="50" >

> **Qt** version (equal to or greater than) 6.0   
> https://www.qt.io/product


### <img src="Resources/Images/logo-cuda.png" width="90" >

> **Nvidia Cuda** version (equal to or greater than) 11.0   
> https://developer.nvidia.com/cuda-toolkit


### <img src="Resources/Images/logo-optix.png" width="90" >

> **Nvidia Optix** version (equal to or greater than) 11.0   
> https://developer.nvidia.com/rtx/ray-tracing/optix


### <img src="Resources/Images/logo-openexr.png" width="130" >

> **OpenEXR**
> https://openexr.com/en/latest/



## Corresponding CMake path that needs to be modified (in CMakeLists.txt)

> **Qt directory**
> - set(Qt6_DIR "D:/DevTools/Qt6/6.2.4/msvc2019_64/" CACHE PATH "qt5 cmake dir") 

> **Optix directory**
> - set(Optix_DIR "D:/DevTools/VTK8-Install")   

> **OpenEXR directory**
> - set(OpenEXR_DIR "D:/DevTools/VTK8-Install")

---
# <img src="Resources/Images/crystal.png" width="40" > Supported Features

## 3D medical images Cinematic rendering

> Utilize advanced visualization techniques to process medical image data, and apply physically-based rendering techniques to achieve realistic rendering effects.

## Advanced Visualization Tools

> Implement multiple visualization processing algorithms and enable interactive operation of said algorithms.

## Support for multiple light sources

> Provide support for multiple light sources, including point light, surface light, directional light, and high dynamic range environment mapping, to illuminate medical 3D data.

## Real time denoising

> Provide real-time denoising capabilities for realistic rendering, with the intention of achieving high-quality rendering results in interaction.







