#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <optional>

enum class ksTokenType {
    semicolon,
    open_parentheses,
    closed_parentheses,
    identifier,
    let,
    equals,
    plus,
    minus,
    open_curly,
    closed_curly,
    open_bracket,
    closed_bracket,
    assigment,
    ks_return,
};

enum class ksTokenAttribute {
    unoptimized,
    unsafe,
    no_return,
};

enum class ksPreProcessor {
    use,

};

struct ksToken {
    ksTokenType type;
    int line;
    std::optional < std::string > value {};
};

class Tokenizer {
public:
    bool loadSource(const std::string & filename, std::vector < std::string > & output) {
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

    inline std::string tokenToString(const ksToken & token) {
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
            case ksTokenType::let:
                oss << "let";
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