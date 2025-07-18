#include <string>

bool isDigit(const std::string& input) {
    if (input.empty()) return false;

    for (size_t i = 0; i < input.size(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(input[i]))) return false;
    }

    return true;
}