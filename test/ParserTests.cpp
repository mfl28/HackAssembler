#include "Parser.h"
#include "HackAssembler.h"
#include <gtest/gtest.h>
#include <sstream>

using std::ofstream;
using std::ios;
using std::stringstream;

using HackAssembler::Parser;

TEST(ParserSymbolLessTest, HasMoreCommands) {
    stringstream s("@123 \n  \n //... \n D=M \n     //...");
    Parser parser(s);

    ASSERT_TRUE(parser.hasMoreCommands());
    
	parser.advance();
	ASSERT_TRUE(parser.hasMoreCommands());
    
    parser.advance();
    ASSERT_FALSE(parser.hasMoreCommands());
}

TEST(ParserSymbolLessTest, CommandsCorrectlyParsed) {
    stringstream s("@123 \n D=M \n @2 \n 0;JMP");
    Parser parser(s);

    parser.advance();
    ASSERT_EQ(parser.commandType(), Parser::CommandType::A);
    ASSERT_EQ(parser.symbol(), "123");

    parser.advance();
    ASSERT_EQ(parser.commandType(), Parser::CommandType::C);
    ASSERT_EQ(parser.dest(), "D");
    ASSERT_EQ(parser.comp(), "M");
    ASSERT_EQ(parser.jump(), "null");

    parser.advance();
    ASSERT_EQ(parser.commandType(), Parser::CommandType::A);
    ASSERT_EQ(parser.symbol(), "2");

    parser.advance();
    ASSERT_EQ(parser.commandType(), Parser::CommandType::C);
    ASSERT_EQ(parser.dest(), "null");
    ASSERT_EQ(parser.comp(), "0");
    ASSERT_EQ(parser.jump(), "JMP");

    ASSERT_FALSE(parser.hasMoreCommands());
}

TEST(ParserSymbolTest, HasMoreCommands) {
    stringstream s("@test \n  \n //... \n D=M \n (END)   //...");
    Parser parser(s);

    ASSERT_TRUE(parser.hasMoreCommands());

    parser.advance();
    ASSERT_TRUE(parser.hasMoreCommands());

    parser.advance();
    ASSERT_TRUE(parser.hasMoreCommands());

    parser.advance();
    ASSERT_FALSE(parser.hasMoreCommands());
}

TEST(ParserSymbolTest, CommandsCorrectlyParsed) {
    stringstream s("(START) \n @testvalue \n D=M \n @START \n D;JGT");
    Parser parser(s);

    parser.advance();
    ASSERT_EQ(parser.commandType(), Parser::CommandType::L);
    ASSERT_EQ(parser.symbol(), "START");

    parser.advance();
    ASSERT_EQ(parser.commandType(), Parser::CommandType::A);
    ASSERT_EQ(parser.symbol(), "testvalue");

    parser.advance();
    ASSERT_EQ(parser.commandType(), Parser::CommandType::C);
    ASSERT_EQ(parser.dest(), "D");
    ASSERT_EQ(parser.comp(), "M");
    ASSERT_EQ(parser.jump(), "null");

    parser.advance();
    ASSERT_EQ(parser.commandType(), Parser::CommandType::A);
    ASSERT_EQ(parser.symbol(), "START");

    parser.advance();
    ASSERT_EQ(parser.dest(), "null");
    ASSERT_EQ(parser.comp(), "D");
    ASSERT_EQ(parser.jump(), "JGT");

    ASSERT_FALSE(parser.hasMoreCommands());
}