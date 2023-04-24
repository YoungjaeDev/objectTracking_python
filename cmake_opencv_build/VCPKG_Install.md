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

# opencv -DWITH_GTK=ON

The problem is vcpkg passes in the build option -DWITH_GTK=OFF when building OpenCV. The open issue: https://github.com/microsoft/vcpkg/issues/12621

The workaround is the following:

    edit the file vcpkg/ports/opencv4/portfile.cmake
    find the line that says -DWITH_GTK=OFF and change it to say -DWITH_GTK=ON
    run ./vcpkg remove opencv4
    run sudo apt-get install libgtk2.0-dev pkg-config
    reinstall OpenCV with ./vcpkg install opencv4 or whichever vcpkg command you used