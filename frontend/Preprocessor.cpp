#include "Preprocessor.hpp"


void Preprocessor::string_replace(std::string& input, const std::string& src, const std::string& dst) {
    size_t pos = input.find(src);
    while(pos != std::string::npos) {
        input.replace(pos, src.size(), dst);
        pos = input.find(src, pos);
    }
}


std::vector<std::string> Preprocessor::split_and_delete_comments(const std::string& s) {
    std::vector<std::string> result;
    std::stringstream input(s);
    std::string item;

    while (getline (input, item, ' ')) {
        if (item.empty() || item[0] == '\t') { continue; }         // unused space
        if (item[0] == '#') { return result; }                     // comment start
        result.push_back(item);
    }
    return result;
}


void Preprocessor::delete_commas(std::vector<std::string>& line) {
    for (std::string& word: line) { string_replace(word, ",", ""); }
}


void Preprocessor::replace_eqv(std::string& str) {
    for(auto& pair : eqv) {
        string_replace(str, pair.first, pair.second);
    }
}

void Preprocessor::close_resources() {
    out.close();
    in.close();
}


void Preprocessor::preprocess() {
    in.open(file);
    out.open("_in.parse"); 
    int counter = 0;  // counter for lines in _in.parse
    if (in.is_open()) {
        std::string current_line;
        while (getline(in, current_line)) { 
            if (current_line.empty() || current_line[0] == '#') {
                continue;
            }
            std::vector<std::string> buf = split_and_delete_comments(current_line);
            if (buf.empty()) { continue; }
            std::string first = buf.front();
            if (macros.find(first) != macros.end()) {
                delete_commas(buf);
                buf.erase(buf.begin());
                if (macros[first].params.size() != buf.size()) {
                    close_resources();
                    throw PreprocessorException("invalid args amount for macro: " + first);
                }
                for (std::string line: macros[first].macros_lines) {
                    for (size_t i = 0; i < macros[first].params.size(); i++) {
                        string_replace(line, macros[first].params[i], buf[i]);
                    }
                    counter++;
                    replace_eqv(line);
                    out << line << std::endl; 
                }
                continue;
            }
            if (first.at(0) == '.') {
                if (first == ".macro") {
                    Macros m_data;
                    std::string name = buf[1];
                    delete_commas(buf);
                    buf.erase(buf.begin(), buf.begin() + 2);                      // delete .macro and macro_name
                    m_data.params = buf;                                          // many parameters
                    while (getline(in, current_line)) {
                      std::vector<std::string> in_buf = split_and_delete_comments(current_line);  // delete comments
                      if (in_buf.empty()) { continue; }
                      if (in_buf.front() == ".end_macro") { break; }
                      m_data.macros_lines.push_back(StringUtils::concat(" ", in_buf)); 
                    }
                    macros[name] = m_data;
                } else if (first == ".eqv") {
                    if (buf.size() == 3) {
                        eqv[buf[1]] = buf[2];    // name : string to replace
                    } else {
                        close_resources();
                        throw PreprocessorException("invalid definition: " + StringUtils::concat(" ", buf));
                    } 
                } else if (first == ".data" || first == ".text") {
                    // do something 
                } else {
                    close_resources();
                    throw PreprocessorException("not supported: " + first);
                }     
                continue;
            }
            int last = first.size() - 1;
            if (buf.front()[last] == ':') {
                if (buf.size() == 1) {
                    first.erase(last, 1);
                    labels[first] = counter;
                    continue; 
                }
                close_resources();
                throw PreprocessorException("invalid label name: " + StringUtils::concat(" ", buf));
            }
            counter++;
            current_line = StringUtils::concat(" ", buf);
            replace_eqv(current_line);
            out << current_line << std::endl;             
        }
    }
    close_resources();
}