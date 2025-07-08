#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <optional>


std::string filepath;

enum class ksTokenType {
    semicolon,
    open_parentheses,
    closed_parentheses,
    identifier,
    equals,
    plus,
    minus,
    open_curly,
    closed_curly,
    open_bracket,
    closed_bracket,
    assigment,
    ks_return,
    ks_if,
    ks_else,
    elif,
    int_literal,
    star,
    slash,
    ks_and,
    ks_or,
    ks_not,
    ks_xor,
    attribute_unoptimized,
    attribute_unsafe,
    attribute_no_return,
    attribute_end,
    function,
    int_type,
};

struct ksToken {
    ksTokenType type;
    int line;
    std::optional < std::string > value {};
};

class Tokenizer {
public:
    explicit Tokenizer(std::string src): m_src(std::move(src)) {}

    bool loadSource(const std::string &filename, std::vector<std::string> &output) {
        filepath = filename;

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "ksc: \033[31merror:\033[0m cannot open file '" << filename << "'\n";
            return false;
        }

        

        std::string line;
        while (std::getline(file, line)) {
            output.push_back(line);
        }

        return true;
    }

    inline std::string tokenToString(const ksToken &token) {
        std::ostringstream oss;

        switch (token.type) {
            case ksTokenType::semicolon:
                oss << ";";
                break;
            case ksTokenType::open_parentheses:
                oss << "(";
                break;
            case ksTokenType::closed_parentheses:
                oss << ")";
                break;
            case ksTokenType::identifier:
                oss << "identifier";
                break;
            case ksTokenType::equals:
                oss << "==";
                break;
            case ksTokenType::plus:
                oss << "+";
                break;
            case ksTokenType::minus:
                oss << "-";
                break;
            case ksTokenType::open_curly:
                oss << "{";
                break;
            case ksTokenType::closed_curly:
                oss << "}";
                break;
            case ksTokenType::open_bracket:
                oss << "[";
                break;
            case ksTokenType::closed_bracket:
                oss << "]";
                break;
            case ksTokenType::assigment:
                oss << "=";
                break;
            case ksTokenType::ks_return:
                oss << "return";
                break;
            case ksTokenType::ks_if:
                oss << "if";
                break;
            case ksTokenType::ks_else:
                oss << "else";
                break;
            case ksTokenType::elif:
                oss << "elif";
                break;
            case ksTokenType::int_literal:
                oss << "int literal";
                break;
            case ksTokenType::star:
                oss << "*";
                break;
            case ksTokenType::slash:
                oss << "/";
                break;
            case ksTokenType::ks_and:
                oss << "and";
                break;
            case ksTokenType::ks_or:
                oss << "or";
                break;
            case ksTokenType::ks_not:
                oss << "not";
                break;
            case ksTokenType::ks_xor:
                oss << "xor";
                break;
            case ksTokenType::attribute_unoptimized:
                oss << "#[unoptimized]";
                break;
            case ksTokenType::attribute_unsafe:
                oss << "#[unsafe]";
                break;
            case ksTokenType::attribute_no_return:
                oss << "#[no_return]";
                break;
            case ksTokenType::function:
                oss << "function";
                break;
            case ksTokenType::int_type:
                oss << "int";
                break;
            default:
                return "unknown";
        }

        return oss.str();
    }

    std::vector<ksToken> tokenize() {
        std::vector<ksToken> tokens;
        std::string buffer;

        int line = 1;
        while (peek().has_value()) {

            if (std::isalpha(peek().value())) {   
                                                                                    // if the next char is an alphabetical char, start an identifier                     
                buffer.push_back(consume());                                        // or a keyword
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buffer.push_back(consume());
                } if (buffer == "return") {
                    tokens.push_back({ ksTokenType::ks_return, line });
                    buffer.clear();
                } else if (buffer == "if") {
                    tokens.push_back({ ksTokenType::ks_if, line });
                    buffer.clear();
                } else if (buffer == "elif") {
                    tokens.push_back({ ksTokenType::elif, line });
                    buffer.clear();
                } else if (buffer == "else") {
                    tokens.push_back({ ksTokenType::ks_else, line });
                    buffer.clear();
                } else if (buffer == "and") {
                    tokens.push_back({ ksTokenType::ks_and, line});
                    buffer.clear();
                } else if (buffer == "or") {
                    tokens.push_back({ ksTokenType::ks_or, line});
                    buffer.clear();
                } else if (buffer == "not") {
                    tokens.push_back({ ksTokenType::ks_not, line});
                    buffer.clear();
                } else if (buffer == "xor") {
                    tokens.push_back({ ksTokenType::ks_xor, line});
                    buffer.clear();
                } else if (buffer == "function") {
                    tokens.push_back({ ksTokenType::function, line});
                    buffer.clear();
                } else if (buffer == "int") {
                    tokens.push_back({ ksTokenType::int_type, line });
                    buffer.clear();
                } else {
                    tokens.push_back({ ksTokenType::identifier, line, buffer });
                    buffer.clear();
                }

            } else if (std::isdigit(peek().value())) {                             // if the next char is a number, assume its a int literal,
                buffer.push_back(consume());                                       // collect the digits into a buffer and push int_literal token.
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buffer.push_back(consume());
                }
                tokens.push_back({ ksTokenType::int_literal, line, buffer });
                buffer.clear();
                
            } else if (peek().value() == '#' && peek(1).has_value() && peek(1).value() == '[') {
                                                                                   // if 2 chars contain "#[", assume its an attribute
                consume();
                consume();

                std::string attribute;

                while (peek().has_value() && peek().value() != ']') {
                    attribute.push_back(consume());
                }

                if (!peek().has_value() || consume() != ']') {
                    std::cerr << "\033[1mIn file " << filepath << " " << line << "\033[0m\n";
                    std::cerr << "      \033[31merror:\033[0m expected ']' after an attribute\n";
                    exit(1);
                }

                if (attribute == "unoptimized") {
                    tokens.push_back({ ksTokenType::attribute_unoptimized, line});
                } else if (attribute == "unsafe") {
                    tokens.push_back({ ksTokenType::attribute_unsafe, line});
                } else if (attribute == "no_return") {
                    tokens.push_back({ ksTokenType::attribute_no_return, line});
                } else {
                    std::cerr << "\033[1mIn file " << filepath << " " << line << "\033[0m\n";
                    std::cerr << "      \033[31merror:\033[0m unknown attribute '" << attribute << "'\n";
                    exit(1);
                }

            } else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '/') {
                                                                                   // if this char and next char have "/" then treat it as a comment
                consume();                                                         // and just ignore it
                consume();
                while (peek().has_value() && peek().value() != '\n') {
                    consume();
                }
            } else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '*') {
                consume();                                                         // if 2 chars contain "/*" ignore everything else until next 2 chars
                consume();                                                         // contain "*/"
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
            } else if (peek().value() == '(') {
                consume();
                tokens.push_back({ ksTokenType::open_parentheses, line });
            }
            else if (peek().value() == ')') {
                consume();
                tokens.push_back({ ksTokenType::closed_parentheses, line });
            }
            else if (peek().value() == ';') {
                consume();
                tokens.push_back({ ksTokenType::semicolon, line });
            }
            else if (peek().value() == '=') {
                consume();
                tokens.push_back({ ksTokenType::assigment, line });
            }
            else if (peek().value() == '=' && peek(1).has_value() && peek(1).value() == '=') {
                consume();
                tokens.push_back({ ksTokenType::equals, line });
            }
            else if (peek().value() == '+') {
                consume();
                tokens.push_back({ ksTokenType::plus, line });
            }
            else if (peek().value() == '*') {
                consume();
                tokens.push_back({ ksTokenType::star, line });
            }
            else if (peek().value() == '-') {
                consume();
                tokens.push_back({ ksTokenType::minus, line });
            }
            else if (peek().value() == '/') {
                consume();
                tokens.push_back({ ksTokenType::slash, line });
            }
            else if (peek().value() == '{') {
                consume();
                tokens.push_back({ ksTokenType::open_curly, line });
            }
            else if (peek().value() == '}') {
                consume();
                tokens.push_back({ ksTokenType::closed_curly, line });
            }
            else if (peek().value() == '\n') {
                consume();
                line++;
            }
            else if (std::isspace(peek().value())) {                               // ignore the spaces
                consume();
            }
            else {
                std::cerr << "\033[1mIn file " << filepath << " " << line << "\033[0m\n";
                std::cerr << "      \033[31merror:\033[0m invalid token '" 
                << peek().value() << "'\n";
                exit(1);
            }

            
        }
        return tokens;
    }

private:
    [[nodiscard]] std::optional<char> peek(const size_t offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }
        return m_src.at(m_index + offset);
    }

    char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index = 0;
};