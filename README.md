## ppl-matlab

Parma Polyhedra Library bindings for use in MATLAB and Simulink

Only some minimal polyhedra features are included, and the API tries to match that of MPT3

---

### How to build Pharma Polyhedra Library binaries

This repository includes static library binaries of ppl 1.2 and gmp 6.3 compiled on GCC 8.1 for Windows x64. You need those if you want to call C++ functions through 'coder.ceval' on MATLAB scripts or MATLAB fn blocks that use them.

#### Prerequisites

- Parma Polyhedra Library source https://www.bugseng.com/content/ppl-download
- GMP source https://gmplib.org/
- MSYS2 https://winstall.app/apps/MSYS2.MSYS2
- MATLAB supported C compiler https://la.mathworks.com/support/requirements/supported-compilers.html

#### 1. Set-up directories

- Extract all compressed files to easy to access directories and create a new one for the library binaries.
```bash
# Source code
C:\sources\gmp-6.3.0
C:\sources\ppl-1.2
# C compiler
C:\matlab\mingw81
# Output
C:\output
```

#### 2. Prepare MSYS2 shell for compilation

- Launch MSYS2-MINGW64 and install `m4` and `make`

    ``pacman -S m4 make``

- Navigate to the directory where the C compiler is and add `bin` to PATH

    ```bash
    cd /c/matlab/mingw81/bin
    export PATH=$PATH:$(pwd)
    # Check that PATH has been modified correctly
    echo $PATH
    ```

#### 3. Compile GMP and PPL

- Navigate to the GMP sources and compile

    ```bash
    cd /c/sources/gmp-6.3.0
    ./configure --enable-cxx --prefix=/c/output
    make
    make install
    ```

- Navigate to the PPL sources and compile

    ```bash
    cd /c/sources/ppl-1.2
    ./configure --enable-shared=no --with-gmp=/c/output --prefix=/c/output
    make
    make install
    ```

- If everything went correctly header files and compiled binaries can be found in `C:\output\include` and `C:\output\lib` respectively.