#include "interpreter.h"
#include <sstream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <cmath>
#include <stdexcept>

enum class TokenType {
    Number,
    String,
    Identifier,
    Operator,
    Keyword,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    explicit Lexer(std::istream& input) : input(input) {}

    Token getNextToken() {
        while (std::isspace(peek())) {
            advance();
        }

        if (std::isdigit(peek())) {
            return number();
        }

        if (std::isalpha(peek()) || peek() == '_') {
            return identifier();
        }

        if (peek() == '"') {
            return string();
        }

        if (peek() == '\0') {
            return {TokenType::EndOfFile, ""};
        }

        return op();
    }

private:
    std::istream& input;
    char currentChar = ' ';

    char peek() {
        if (input.peek() == EOF) {
            return '\0';
        }
        return input.peek();
    }

    void advance() {
        input.get(currentChar);
    }

    Token number() {
        std::string value;
        while (std::isdigit(peek()) || peek() == '.') {
            value += peek();
            advance();
        }
        return {TokenType::Number, value};
    }

    Token identifier() {
        std::string value;
        while (std::isalnum(peek()) || peek() == '_') {
            value += peek();
            advance();
        }
        return {TokenType::Identifier, value};
    }

    Token string() {
        std::string value;
        advance(); // skip opening quote
        while (peek() != '"') {
            value += peek();
            advance();
        }
        advance(); // skip closing quote
        return {TokenType::String, value};
    }

    Token op() {
        std::string value(1, peek());
        advance();
        return {TokenType::Operator, value};
    }
};

class Interpreter {
public:
    bool interpret(std::istream& input, std::ostream& output) {
        Lexer lexer(input);
        Token token = lexer.getNextToken();
        while (token.type != TokenType::EndOfFile) {
            if (token.type == TokenType::Identifier) {
                if (token.value == "print") {
                    token = lexer.getNextToken();
                    if (token.type == TokenType::Identifier) {
                        output << variables[token.value];
                    } else if (token.type == TokenType::Number) {
                        output << token.value;
                    } else if (token.type == TokenType::String) {
                        output << token.value;
                    }
                } else {
                    std::string varName = token.value;
                    token = lexer.getNextToken();
                    if (token.type == TokenType::Operator && token.value == "=") {
                        token = lexer.getNextToken();
                        if (token.type == TokenType::Number) {
                            variables[varName] = token.value;
                        } else if (token.type == TokenType::String) {
                            variables[varName] = token.value;
                        }
                    }
                }
            }
            token = lexer.getNextToken();
        }
        return true;
    }

private:
    std::unordered_map<std::string, std::string> variables;
};

bool interpret(std::istream& input, std::ostream& output) {
    Interpreter interpreter;
    return interpreter.interpret(input, output);
}
