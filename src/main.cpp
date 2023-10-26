#include <iostream>
#include <string>
#include <string_view>
#include <optional>
#include <memory>
#include <fstream>

#include "maddy/parser.h"

std::string read_file(std::string_view file_path)
{
    std::ifstream ifs(file_path.data());
    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    return content;
}

int main()
{
    auto file_content = read_file("./example.md");

    std::cout << "read content: " << file_content << std::endl;
    return 0;
}