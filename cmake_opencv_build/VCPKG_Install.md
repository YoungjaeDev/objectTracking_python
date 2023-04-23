# How to install VCPKG

Official Link: <https://vcpkg.io/en/index.html>

```cmd
mkdir -p external && cd external
git clone https://github.com/Microsoft/vcpkg.git --depth 1
# .\vcpkg\bootstrap-vcpkg.bat # windows
./vcpkg/bootstrap-vcpkg.sh # Unix
export PATH=$PATH:${PWD}/vcpkg
vcpkg
```
