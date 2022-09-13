set vcpkgPath=vcpkg
set vcpkgScriptPath=%vcpkgPath%/scripts/buildsystems/vcpkg.cmake

mkdir BUILD
cd BUILD
cmake ../Src "-DCMAKE_TOOLCHAIN_FILE=../%vcpkgScriptPath%"
cmake --build .

pause