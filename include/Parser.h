#pragma once
#include <istream>
#include <string>
#include <regex>

namespace HackAssembler {
    class Parser {
    public:
        /**
         * \brief Contains the different command-types:
         * A (address-command): "@Xxx", where Xxx is either a symbol or a decimal number
         * C (compute-command): "dest=comp;jump", where dest=destination, comp=computation, 
         *                      jump=jump-instruction (either dest or jump may be empty)
         * L (label-(pseudo)-command): "(Xxx)", where Xxx is the label's name
         */
        enum class CommandType { A, C, L };

        /**
         * \brief Creates a new parser for a provided input-stream and gets ready to parse the 
         * first command (if one exists).
         * \param inputStream The stream to be parsed
         */
        explicit Parser(std::istream& inputStream) : inputStream_{inputStream} { updateNextCommand(); }

        /** 
         * \brief Checks if there exists another command in input-stream.
         * \return True if another command exists, otherwise false.
         */
        bool hasMoreCommands() const noexcept { return !nextCommand_.empty(); }

        /**
         * \brief Sets the current command to the next command encountered
         * in the input-stream. Must only be called if hasMoreCommands() 
         * returns true.
         */
        void advance();

        /**
         * \brief Resets the parser to the beginning of the input-stream.
         * Switches on syntax-checking. 
         */
        void reset();

        /**
         * \brief Gets the type of the current command.
         * \return A-, C-, or L-command-type
         */
        CommandType commandType() const;

        /**
         * \brief Gets the symbol or decimal Xxx of the current command @Xxx or (Xxx).
         * Must only be called when the current command-type is A or L
         * \return symbol or decimal as a string
         */
        std::string symbol() const;

        /**
         * \brief Gets the destination-part of a command with type C, so this function must only
         * be called if the current command is a C-command.
         * \return one of 8 possible dest-mnemonics defined in the Hack assembly language
         */
        std::string dest() const;

        /**
         * \brief Gets the computation-part of a command with type C, so this function must only
         * be called if the current command is a C-command.
         * \return one of 28 possible comp-mnemonics defined in the Hack assembly language
         */
        std::string comp() const;

        /**
         * \brief Gets the jump-instruction-part of a command with type C, so this function must only
         * be called if the current command is a C-command.
         * \return one of 8 possible jump-mnemonics defined in the Hack assembly language
         */
        std::string jump() const;

        /**
         * \brief Switches syntax-checking on or off. If switched on, the parser will throw
         * an exception if a syntactic error is encountered while parsing the input-stream.
         * Syntax-checking is turned on by default after construction.
         * \param value True or false
         */
        void setSyntaxChecking(bool value) { syntaxChecking_ = value; }

        /**
         * \brief Checks if syntax-checking is currently switched on.
         * \return True if syntax-checking is on, false otherwise.
         */
        bool isSyntaxChecking() const { return syntaxChecking_; }

    private:
        std::istream& inputStream_;
        std::string currentCommand_;
        std::string nextCommand_;
        size_t currentLineNr_{};
        bool syntaxChecking_{true};

        void updateNextCommand();
    };
}

