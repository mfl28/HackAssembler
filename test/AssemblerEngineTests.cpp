#include "AssemblerEngine.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

using std::vector;
using std::string;
using std::istream;
using std::ostream;
using std::ifstream;
using std::istreambuf_iterator;
using std::stringstream;
namespace fs = std::filesystem;

extern string testFilesPath;

namespace {
    const vector<string> TEST_FILE_NAMES{
        "Add.asm",
        "Max.asm",
        "MaxL.asm",
        "Pong.asm",
        "PongL.asm",
        "Rect.asm",
        "RectL.asm"
    };

    class AssemblerEngineTest : public testing::TestWithParam<string> {};

    /**
     * \brief A parametrized test, that gets an input-file <filename>.asm as a parameter, opens the file
     * using the testFilePath-string as stem-directory and assembles the commands in the file into
     * binary code. The produced output is then compared with the binary code in the reference-file
     * <filename>_Ref.hack which is expected to exist in the directory denoted by testFilePath. 
     * All reference files have been assembled using the provided HackAssembler.bat from nand2tetris.org.  
     */
    TEST_P(AssemblerEngineTest, AssemblyOutputMatchesReferenceOutput) {
        const fs::path inputPath{testFilesPath + GetParam()};

        ASSERT_TRUE(fs::exists(inputPath)) << "The test-file " << inputPath << " does not exist.";

        fs::path referenceOutputFilePath{inputPath};
        referenceOutputFilePath.replace_filename(inputPath.stem().string() + "_Ref.hack");

        ASSERT_TRUE(fs::exists(referenceOutputFilePath)) << "The required reference-file " << referenceOutputFilePath.filename() 
            << " does not exist in the test-file directory " << inputPath.parent_path();

        ifstream referenceOutputStream{referenceOutputFilePath};
        const string referenceOutput{istreambuf_iterator<char>{referenceOutputStream}, istreambuf_iterator<char>{}};

        stringstream outputStream;
        ifstream inputStream{inputPath};

        HackAssembler::AssemblerEngine engine{inputStream, outputStream};
        engine.execute();

        ASSERT_EQ(referenceOutput, outputStream.str());
    }

    INSTANTIATE_TEST_CASE_P(AssemblerEngineTestInstance, AssemblerEngineTest, ::testing::ValuesIn(TEST_FILE_NAMES),
		[] (const ::testing::TestParamInfo<string>& info) { return info.param.substr(0, info.param.find('.')); });
}