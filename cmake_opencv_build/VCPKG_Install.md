# How to install VCPKG

Official Link: <https://vcpkg.io/en/index.html>

```cmd
mkdir -p external && cd external
git clone https://github.com/Microsoft/vcpkg.git
# .\vcpkg\bootstrap-vcpkg.bat # windows
./vcpkg/bootstrap-vcpkg.sh # Unix
echo "export PATH=$PATH:${PWD}/vcpkg" >> ~/.bashrc
. ~/.bashrc
vcpkg
```
