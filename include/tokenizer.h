#pragma once

#include <iostream>
#include <optional>
#include <variant>
#include <vector>

typedef enum {
    ks_while,
    ks_for,
    ks_void,
    ks_break,
    ks_and,
    ks_or,
    ks_xor,
    ks_not,
    ks_if,
    ks_else,
    ks_continue,
    ks_test,
    ks_case,
    ks_default,
    ks_short,
    ks_long,
    ks_unsigned,
    ks_int,
    ks_char,
    ks_sizeof,
    ks_return,
    ks_enum,
    ks_struct,
    ks_typedef,
    ks_module,
    ks_extern,
    ks_float,
    ks_double,
    ks_signed,
    ks_const,
    ks_static,
    ks_function,
    ks_arrow,
    ks_open_paren,
    ks_closed_paren,
    ks_semi,
    ks_open_bracket,
    ks_closed_bracket,
    ks_open_curly,
    ks_closed_curly,
    ks_open_arrow,
    ks_closed_arrow,
    ks_hashtag,
    ks_dot,
    ks_int_lit,
    ks_char_lit,

} TokenType;

typedef struct {
    TokenType                 Token_t;
    
    std::optional
    <std::variant<int, char, float, unsigned int>> Value {};

} Token;

class Tokenizer {
    public:
        explicit Tokenizer(std::string src) : m_src(std::move(src)) {}

        std::vector<Token> Tokenize() {
            
            std::vector<Token> Tokens;
            std::string        Buffer;

            while (peek().has_value()) {

                // Keywords
                if (std::isalpha(peek().value())) {
                    Buffer.push_back(consume());

                    if (Buffer == "while") {
                        Tokens.push_back( { ks_while } );
                    }
                    else if (Buffer == "for") {
                        Tokens.push_back( { ks_for } );
                    }
                    else if (Buffer == "void") {
                        Tokens.push_back( { ks_void } );
                    }
                    else if (Buffer == "break") {
                        Tokens.push_back( { ks_break } );
                    }
                    else if (Buffer == "and") {
                        Tokens.push_back( { ks_and } );
                    }
                    else if (Buffer == "or") {
                        Tokens.push_back( { ks_or } );
                    }
                    else if (Buffer == "xor") {
                        Tokens.push_back( { ks_xor } );
                    }
                    else if (Buffer == "not") {
                        Tokens.push_back( { ks_not } );
                    }
                    else if (Buffer == "if") {
                        Tokens.push_back( { ks_if } );
                    }
                    else if (Buffer == "else") {
                        Tokens.push_back( { ks_else } );
                    }
                    else if (Buffer == "continue") {
                        Tokens.push_back( { ks_continue } );
                    }
                    else if (Buffer == "test") {
                        Tokens.push_back( { ks_test } );
                    }
                    else if (Buffer == "case") {
                        Tokens.push_back( { ks_case } );
                    }
                    else if (Buffer == "default") {
                        Tokens.push_back( { ks_default } );
                    }
                    else if (Buffer == "short") {
                        Tokens.push_back( { ks_short } );
                    }
                    else if (Buffer == "long") {
                        Tokens.push_back( { ks_long } );
                    }
                    else if (Buffer == "unsigned") {
                        Tokens.push_back( { ks_unsigned } );
                    }
                    else if (Buffer == "int") {
                        Tokens.push_back( { ks_int } );
                    }
                    else if (Buffer == "char") {
                        Tokens.push_back( { ks_char } );
                    }
                    else if (Buffer == "sizeof") {
                        Tokens.push_back( { ks_sizeof } );
                    }
                    else if (Buffer == "return") {
                        Tokens.push_back( { ks_return } );
                    }
                    else if (Buffer == "enum") {
                        Tokens.push_back( { ks_enum } );
                    }
                    else if (Buffer == "struct") {
                        Tokens.push_back( { ks_struct } );
                    }
                    else if (Buffer == "typedef") {
                        Tokens.push_back( { ks_typedef } );
                    }
                    else if (Buffer == "module") {
                        Tokens.push_back( { ks_module } );
                    }
                    else if (Buffer == "external") {
                        Tokens.push_back( { ks_extern } );
                    }
                    else if (Buffer == "float") {
                        Tokens.push_back( { ks_float } );
                    }
                    else if (Buffer == "double") {
                        Tokens.push_back( { ks_double } );
                    }
                    else if (Buffer == "signed") {
                        Tokens.push_back( { ks_signed } );
                    }
                    else if (Buffer == "constant") {
                        Tokens.push_back( { ks_const } );
                    }
                    else if (Buffer == "static") {
                        Tokens.push_back( { ks_static } );
                    }
                    else if (Buffer == "function") {
                        Tokens.push_back( { ks_function } );
                    }
                    else {
                        consume();
                        Tokens.push_back( { ks_char_lit } );
                    }
                }

                // Return arrows
                else if (peek().value() == '-' && peek(1).value() == '>') {
                    consume();
                    consume();
                    Tokens.push_back( { ks_arrow } );
                }

                // Comments
                else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '/') {
                    consume();
                    consume();
                    while (peek().has_value() && peek().value() != '\n') {
                        consume();
                    }
                }

                // Multiline comments
                else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '*') {
                    consume();
                    consume();
                    while (peek().has_value()) {
                        if (peek().value() == '*' && peek(1).has_value() && peek(1).value() == '/') {
                            break;
                        }
                        consume();
                    }
                    if (peek().has_value()) {
                        consume();
                    }
                    if (peek().has_value()) {
                        consume();
                    }
                }

                // Symbols
                else if (peek().value() == '(') {
                    consume();
                    Tokens.push_back( { ks_open_paren } );
                }
                else if (peek().value() == ')') {
                    consume();
                    Tokens.push_back( { ks_closed_paren } );
                }
                else if (peek().value() == ';') {
                    consume();
                    Tokens.push_back( { ks_semi } );
                }
                else if (peek().value() == '[') {
                    consume();
                    Tokens.push_back( { ks_open_bracket } );
                }
                else if (peek().value() == ']') {
                    consume();
                    Tokens.push_back( { ks_closed_bracket } );
                }
                else if (peek().value() == '{') {
                    consume();
                    Tokens.push_back( { ks_open_curly } );
                }
                else if (peek().value() == '}') {
                    consume();
                    Tokens.push_back( { ks_closed_curly } );
                }
                else if (peek().value() == '<') {
                    consume();
                    Tokens.push_back( { ks_open_arrow } );
                }
                else if (peek().value() == '>') {
                    consume();
                    Tokens.push_back( { ks_closed_arrow } );
                }
                else if (peek().value() == '#') {
                    consume();
                    Tokens.push_back( { ks_hashtag } );
                }
                else if (peek().value() == '.') {
                    consume();
                    Tokens.push_back( { ks_dot } );
                }

                if (std::isdigit(peek().value())) {
                    consume();
                    Tokens.push_back( { ks_int_lit } );
                }
            }
        }
    private:
        [[nodiscard]] std::optional<char> peek(const size_t offset = 0) const {
            if (m_index + offset >= m_src.length()) {
                return {};
            }
            return m_src.at(m_index + offset);
        }

        char consume() {
            return m_src.at(m_index++);
        }

    const std::string m_src;
    size_t m_index = 0;
};