# HackAssembler [![Build Status](https://travis-ci.org/mfl28/HackAssembler.svg?branch=master)](https://travis-ci.org/mfl28/HackAssembler)
This is an implementation of an assembler for the Hack-assembly-language as defined in the nand2tetris-course [project 6](https://www.nand2tetris.org/project06) .

## Building the program
```bash
git clone https://github.com/mfl28/HackAssembler.git
cd HackAssembler
mkdir build
cmake -S . -B build    # Or "cmake -D BUILD_TESTS=ON -S . -B build" if you want to also build the unit-tests.
cmake --build build    # Add "--config Release" to select Release-configuration.
```
## Running the program
After you built the program, then from the project root do:
```bash
git clone https://github.com/mfl28/HackAssembler.git
cd build/Debug    # Or "cd build/Release if you chose to build in Release-mode.
./HackAssembler path/to/file-to-assemble/filename.asm
```
## Running the tests
If you built the program including the unit-tests (i.e. using `-D BUILD_TESTS=ON`), then these can be run from the project root by doing the following:
```bash
cd build
ctest -C Debug -V    # Or "ctest -C Release -V" if you chose to build in Release-mode.
```
## References
- [nand2tetris-course](https://www.nand2tetris.org)
- [Google Test](https://github.com/google/googletest)
