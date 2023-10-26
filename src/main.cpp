#include <iostream>
#include <string>
#include <string_view>
#include <optional>
#include <memory>
#include <fstream>

#include "maddy/parser.h"

constexpr char HTML_STYLE[] = R"(
<link rel="stylesheet" href="./highlight/styles/monokai.css"/>
<script src="./highlight/highlight.min.js"></script>
<script>hljs.highlightAll();</script>
)";

std::ifstream read_file(std::string_view path)
{
    std::ifstream ifs(path.data());
    return ifs;
}

void write_file(std::string_view path, std::string_view content)
{
    std::ofstream ofs(path.data(),
    std::ios::out |   // output file stream
    std::ios::app |   // can append to a existing file
    std::ios::ate);  // set file cursor at the end
    ofs << content.data();
    ofs.close();
}

int main()
{
    auto file_content = read_file("./example.md");

    // config is optional
    std::shared_ptr<maddy::ParserConfig> config = std::make_shared<maddy::ParserConfig>();
    // config->isEmphasizedParserEnabled = false; // default true - this flag is deprecated
    // config->isHTMLWrappedInParagraph = false; // default true - this flag is deprecated
    config->enabledParsers &= ~maddy::types::EMPHASIZED_PARSER; // equivalent to !isEmphasizedParserEnabled
    config->enabledParsers |= maddy::types::HTML_PARSER; // equivalent to !isHTMLWrappedInParagraph

    std::shared_ptr<maddy::Parser> parser = std::make_shared<maddy::Parser>(config);
    std::string html = HTML_STYLE + parser->Parse(file_content);
    std::cout << "html: " << html << std::endl;

    write_file("./out.html", html);

    return 0;
}