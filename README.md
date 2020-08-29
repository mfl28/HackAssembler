# HackAssembler

[![Build Status](https://dev.azure.com/mfl28/HackAssembler/_apis/build/status/mfl28.HackAssembler?branchName=master)](https://dev.azure.com/mfl28/HackAssembler/_build/latest?definitionId=3&branchName=master)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/mfl28/HackAssembler.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/mfl28/HackAssembler/context:cpp)

| OS      | Build & Test Pipeline Status                                                                                                                                                                                                                   |
| ------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| Linux   | [![Build Status](https://dev.azure.com/mfl28/HackAssembler/_apis/build/status/mfl28.HackAssembler?branchName=master&stageName=Test&jobName=Linux)](https://dev.azure.com/mfl28/HackAssembler/_build/latest?definitionId=3&branchName=master)   |
| MacOS   | [![Build Status](https://dev.azure.com/mfl28/HackAssembler/_apis/build/status/mfl28.HackAssembler?branchName=master&stageName=Test&jobName=MacOS)](https://dev.azure.com/mfl28/HackAssembler/_build/latest?definitionId=3&branchName=master)   |
| Windows | [![Build Status](https://dev.azure.com/mfl28/HackAssembler/_apis/build/status/mfl28.HackAssembler?branchName=master&stageName=Test&jobName=Windows)](https://dev.azure.com/mfl28/HackAssembler/_build/latest?definitionId=3&branchName=master) |

This is a C++-implementation of an assembler for the Hack assembly-language as defined in the nand2tetris-course [project 6](https://www.nand2tetris.org/project06). The program gets a single `.asm`-file containing Hack assembly-language code as argument, translates it into binary code and outputs the result into a `.hack`-file.

## Building the program

_Note_: To build this program, a compiler that supports C++17 and `std::filesystem` is required (e.g. gcc version ≥ 8).

```bash
git clone https://github.com/mfl28/HackAssembler.git
cd HackAssembler
cmake -B build    # Use option "-D BUILD_TESTING=OFF" if you do not want to build the unit-tests.
cmake --build build   
```

## Running the program

After you built the program, do the following from within the `build`-directory:

#### Linux

```bash
./HackAssembler path/to/filename.asm
```

#### Windows

```bash
cd Debug    # Or "cd Release" if you built using Release-configuration.
.\HackAssembler.exe path\to\filename.asm
```

## Running the tests

If you built the program including the unit-tests, then these can be run from within the `build`-directory by doing the following:

#### Linux

```bash
ctest -V
```

#### Windows

```bash
ctest -C Debug -V    # Or "ctest -C Release -V" if you built using Release-configuration.
```

## References

-   [nand2tetris-course](https://www.nand2tetris.org)
-   [Google Test](https://github.com/google/googletest)
