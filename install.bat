git clone https://github.com/Microsoft/vcpkg.git

cd vcpkg

call bootstrap-vcpkg.bat

vcpkg install freeglut
vcpkg --triplet x64-windows install freeglut

vcpkg install glew
vcpkg --triplet x64-windows install glew


vcpkg install glm
vcpkg --triplet x64-windows install glm
