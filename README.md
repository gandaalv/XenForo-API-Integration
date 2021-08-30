# XenForo-API-Integration
C++ XenForo API wrapper

# Dependeny libraries used
>* [zlib](https://github.com/madler/zlib)
>* [curl](https://github.com/curl/curl)
>* [cpr](https://github.com/whoshuu/cpr)

# Platform Toolset and Configuration
>* Windows SDK Version: 10.0.20348.0
>* Platform Toolset: Visual Studio 2022 (v143)
>* C++ Language Standart: std:c++latest

If you encounter any compiling issues related to the dependency libraries and the platform toolset / windows sdk version, build them yourself by following the steps below.

# Building the dependencies yourself
> Installing vcpkg
```shell
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.sh
vcpkg integrate install
```
> Building dependencies
```shell
vcpkg install zlib:windows-x86-static
vcpkg install zlib:windows-x64-static
vcpkg install curl:windows-x86-static
vcpkg install curl:windows-x64-static
vcpkg install cpr:windows-x86-static
vcpkg install cpr:windows-x64-static
```
Copy your build dependencies afterwards from your vcpkg\packages folder and replace the old dependencies in your **$(SolutionDir)**\dependencies folder.


# Credits
Decided to rework my [previous](https://github.com/gandaalv/CPP-XenForo-Loader) C++ XenForo API project after i got inspired by [patrickcjk's](https://github.com/patrickcjk) [Xenforo-API-Integration-for-C-Sharp](https://github.com/patrickcjk/Xenforo-API-Integration-for-C-Sharp).

# License
[MIT License](https://github.com/gandaalv/XenForo-API-Integration/blob/main/LICENSE)
