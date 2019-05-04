# HackAssembler [![Build Status](https://travis-ci.org/mfl28/HackAssembler.svg?branch=master)](https://travis-ci.org/mfl28/HackAssembler)
This is a C++-implementation of an assembler for the Hack-assembly-language as defined in the nand2tetris-course [project 6](https://www.nand2tetris.org/project06) .

## Building the program
_Note_: To build this program, a compiler that suppports C++17 and `std::filesystem` is required (e.g. gcc version &geq; 8).

```bash
git clone https://github.com/mfl28/HackAssembler.git
cd HackAssembler
mkdir build
cd build
cmake ..    # Use "cmake -D BUILD_TESTS=ON .." if you want to also build the unit-tests.
cmake --build .   
```
## Running the program
After you built the program, do the following from within the `build`-directory:
#### Linux
```bash
./HackAssembler path/to/file-to-assemble/filename.asm
```
#### Windows
```bash
cd Debug    # Or "cd Release" if you built using Release-configuration.
.\HackAssembler.exe path\to\file-to-assemble\filename.asm
```
## Running the tests
If you built the program including the unit-tests (i.e. using `-D BUILD_TESTS=ON`), then these can be run from within the `build`-directory by doing the following:
#### Linux
```bash
ctest -V
```
#### Windows
```bash
ctest -C Debug -V    # Or "ctest -C Release -V" if you built using Release-configuration.
```
## References
- [nand2tetris-course](https://www.nand2tetris.org)
- [Google Test](https://github.com/google/googletest)
