#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <string>
#include <filesystem>
#include <sstream>
#include <cstdlib>
#include <unistd.h> 
#include <sys/stat.h>
#include <sys/types.h>

std::unordered_set<std::string> used_variable_names;

std::string random_string(size_t length);
std::string generate_random_variable_name();
bool is_variable_name_unique(const std::string& name);
std::string generate_random_shit();

std::string generate_random_variable_name() {
    std::string name;
    do {
        name = random_string(7);
    } while (!is_variable_name_unique(name));
    used_variable_names.insert(name);
    return name;
}

bool is_variable_name_unique(const std::string& name) {
    return used_variable_names.find(name) == used_variable_names.end();
}

std::string generate_random_shit() {
    std::string fork = random_string(7);
    
    
    std::vector<std::string> actions = {
        "int " + generate_random_variable_name() + " = " + std::to_string(rand() % 100) + ";",
        "float " + generate_random_variable_name() + " = " + std::to_string(rand() % 100) + ".0f;",
        "char " + generate_random_variable_name() + " = '" + static_cast<char>('a' + rand() % 26) + "';",
        "long " + generate_random_variable_name() + " = " + std::to_string(rand() % 100000) + "L;",
        "double " + generate_random_variable_name() + " = " + std::to_string(rand() % 10000) + ".0;",
        "short " + generate_random_variable_name() + " = " + std::to_string(rand() % 50) + ";",
        "unsigned int " + generate_random_variable_name() + " = " + std::to_string(rand() % 200) + ";",
        "unsigned char " + generate_random_variable_name() + " = '" + static_cast<char>('a' + rand() % 26) + "';",
        "long long " + generate_random_variable_name() + " = " + std::to_string(rand() % 1000000000) + "LL;",
        "unsigned long " + generate_random_variable_name() + " = " + std::to_string(rand() % 100000) + "UL;",
        "for (int " + fork + " = 0; " + fork + " < " + std::to_string(rand() % 10 + 1) + "; " + fork + "++) {\nprintf(\"ok\");\n}",
        "if (" + std::to_string(rand()%100+10) + " == " + std::to_string(rand() % 10) + ") { int " + generate_random_variable_name() + " = " + std::to_string(rand() % 100) + "; }",
        "/* no operation */"
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, actions.size() - 1);

    return actions[dis(gen)];
}

std::string generate_random_action() {
    static std::vector<std::string> actions = {
        "int dkihrg = 0;",
        "printf(\"Debug message\");",
        "long dflkhg = 67543;",
        "char krigyuo= \'y\';",
        "/*skip*/",
        "short jrklhyg = 38;"
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, actions.size() - 1);

    return actions[dis(gen)];
}

std::string generate_random_action2() {
    static std::vector<std::string> actions = {
        "int dkihrg = 0;",
        "long dflkhg = 67543;",
        "char krigyuo= \'y\';",
        "/*TODO:*/",
        "short jrklhyg = 38;"
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, actions.size() - 1);

    return actions[dis(gen)];
}

std::string generate_random_operate() {
    static std::vector<std::string> types = {
        "int", "long", "char", "float", "double", "unsigned int", "unsigned long"
    };

    static std::vector<std::string> operations = {
        "+", "-", "*", "/", "%"
    };

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> type_dis(0, types.size() - 1);
    std::string type = types[type_dis(gen)];

    std::string var_name = generate_random_variable_name();

    std::uniform_int_distribution<> value_dis(1, 1000);
    std::string value = std::to_string(value_dis(gen));
    std::string operation = operations[type_dis(gen) % operations.size()];
    std::string action = type + " " + var_name + " = " + value + " " + operation + " " + std::to_string(value_dis(gen)) + ";";

    return action;
}

std::string insert_dummy_conditions(std::string code, int depth = 1) {
    if (depth <= 0) {
        return code;
    }

    std::istringstream stream(code);
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(stream, line)) {
        lines.push_back(line);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    std::string new_code;

    for (size_t i = 0; i < lines.size(); ++i) {
        new_code += lines[i] + "\n";
        if (lines[i].back() == ';') {
            if (dis(gen)) {
                std::string condition = "if (" + std::to_string(rand()) + " == " + std::to_string(rand()) + ") \n{ \n";
                condition += generate_random_shit();
                condition += " \n} else \n{ \n";
                condition += insert_dummy_conditions(generate_random_action2(), depth - 1);
                condition += " \n}\n";
                new_code += condition;
            }
        }
    }

    return new_code;
}

std::string process_numbers(const std::string& input_string) {
    std::string result = input_string;
    std::regex number_regex(R"(\b\d+\b)");
    std::sregex_iterator numbers_begin(result.begin(), result.end(), number_regex);
    std::sregex_iterator numbers_end;

    std::ptrdiff_t offset = 0;
    
    std::srand(std::time(nullptr));

    for (auto it = numbers_begin; it != numbers_end; ++it) {
        std::string number_str = (*it).str();
        long long number = std::stoll(number_str);


        long long a = std::rand() % 1000 + 1;
        long long b = std::rand() % 1000 + 1;
        long long c = std::rand() % 1000 + 1;
        long long d = std::rand() % 1000 + 1;
        long long e = std::rand() % 1000 + 1;
        long long o = std::rand() % 1000 + 1;
        long long u = number+o;

        std::ostringstream new_number_expression;
        new_number_expression << "(((" << u << " + " << a << " - " << b << ")"<< "";
        new_number_expression << " + " << e << " - " << e << ") ";
        new_number_expression << " - " << a << " + " << b << " - "<< o << ")";

        result.replace(it->position() + offset, number_str.length(), new_number_expression.str());
        offset += new_number_expression.str().length() - number_str.length();
    }

    return result;
}

std::string random_string(size_t length);

std::string remove_newlines_and_tabs(const std::string& input_string) {
    return std::regex_replace(input_string, std::regex("[\n\t]"), " ");
}

std::string extract_preprocessor_lines(std::string& code) {
    std::string preprocessor_lines;
    std::regex preprocessor_regex(R"(^\s*#.*$)", std::regex_constants::multiline);
    std::smatch match;

    std::string::const_iterator search_start(code.cbegin());
    while (std::regex_search(search_start, code.cend(), match, preprocessor_regex)) {
        preprocessor_lines += match[0].str() + "\n";
        search_start = match.suffix().first;
    }

    code = std::regex_replace(code, preprocessor_regex, "");

    return preprocessor_lines;
}

bool containsSpecialCharacters(const std::string& text) {
    static const std::regex specialCharactersPattern(R"(\\n|\\r|\\t|\\b|\\f)");
    static const std::regex formatSpecifiersPattern(R"(%[diufxXc%])");

    return std::regex_search(text, specialCharactersPattern) || std::regex_search(text, formatSpecifiersPattern);
}

bool containsPercentageOrBackslash(const std::string& text) {
    return text.find('%') != std::string::npos || text.find('\\') != std::string::npos;
}

bool isInQuotes(const std::string& code, size_t pos) {
    bool inQuotes = false;
    for (size_t i = 0; i < pos; ++i) {
        if (code[i] == '"' && (i == 0 || code[i - 1] != '\\')) {
            inQuotes = !inQuotes;
        }
    }
    return inQuotes;
}

std::string variable_renamer(const std::string& code) {
    //std::regex varRegex(R"(\b(int|float|double|char|std::string|long|short|unsigned|bool)\s*([&\*]*\s*)([a-zA-Z_][a-zA-Z0-9_]*)\b)");
    std::unordered_map<std::string, std::string> varMap; 
    std::regex varRegex(R"(\b(int|float|double|char|std::string|long|short)\s+([a-zA-Z_][a-zA-Z0-9_]*)\b)");
    std::string result = code;
    srand(static_cast<unsigned>(time(0)));

    auto varsBegin = std::sregex_iterator(code.begin(), code.end(), varRegex);
    auto varsEnd = std::sregex_iterator();

    for (std::sregex_iterator i = varsBegin; i != varsEnd; ++i) {
        std::smatch match = *i;
        std::string varName = match.str(2);

        if (varName == "main") {
            continue;
        }

        if (varMap.find(varName) == varMap.end()) {
            varMap[varName] = random_string(12);
        }
    }

    for (const auto& pair : varMap) {
        std::string varPattern = "\\b" + pair.first + "\\b";
        auto varRegex = std::regex(varPattern);
        auto varsBegin = std::sregex_iterator(result.begin(), result.end(), varRegex);
        auto varsEnd = std::sregex_iterator();

        std::string newResult;
        size_t lastPos = 0;

        for (auto i = varsBegin; i != varsEnd; ++i) {
            std::smatch match = *i;
            size_t pos = match.position();

            if (!isInQuotes(result, pos)) {
                newResult += result.substr(lastPos, pos - lastPos);
                newResult += pair.second;
                lastPos = pos + match.length();
            }
        }
        newResult += result.substr(lastPos);
        result = newResult;
    }

    return result;
}


std::string random_string(size_t length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.size() - 1);
    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += characters[dis(gen)];
    }
    return result;
}

std::string comment_remover(std::string given_string) {
    given_string = std::regex_replace(given_string, std::regex(R"(//.*)"), "");
    given_string = std::regex_replace(given_string, std::regex(R"(/\*[^*]*\*+(?:[^/*][^*]*\*+)*/)"), "");
    return given_string;
}

std::string remove_extra_spaces(const std::string& input_string) {
    std::string result = std::regex_replace(input_string, std::regex(R"(\s+)"), " ");
    result = std::regex_replace(result, std::regex(R"(\s*([{}();,])\s*)"), "$1");
    return result;
}

std::string generate_random_function() {
    std::string function_name = generate_random_variable_name();

    static std::vector<std::string> return_types = {"int", "void", "float", "double", "char"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> type_dis(0, return_types.size() - 1);
    std::string return_type = return_types[type_dis(gen)];

    std::string parameters;
    static std::vector<std::string> param_types = {"int", "float", "char", "double"};
    std::uniform_int_distribution<> param_dis(0, param_types.size() - 1);
    int num_params = rand() % 3;
    for (int i = 0; i < num_params; ++i) {
        if (i > 0) parameters += ", ";
        parameters += param_types[param_dis(gen)] + " " + generate_random_variable_name();
    }

    std::string actions;
    int num_actions = 3 + rand() % 5;
    for (int i = 0; i < num_actions; ++i) {
        actions += "    " + generate_random_shit() + "\n";
    }

    std::string function_code = return_type + " " + function_name + "(" + parameters + ") {\n" + actions + "}\n";

    return function_code;
}

std::string insert_random_functions(std::string code, int probability) {
    int balance = 0;
    std::string::size_type pos = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2); 
    std::uniform_int_distribution<> prob_dist(0, 99); 

    while (pos < code.size()) {
        if (code[pos] == '{') {
            balance++;
        } else if (code[pos] == '}') {
            balance--;

            if (balance == 0) {
                int insert_count = dist(gen);

                for (int i = 0; i < insert_count; ++i) {
                    std::string new_function = generate_random_function();
                    pos += 1; 
                    code.insert(pos, "\n" + new_function + "\n");
                    pos += new_function.length() + 1; 
                }
            }
        }
        pos++;
    }

    
    if (prob_dist(gen) < probability) {  
        return insert_random_functions(code, probability);
    }

    return code;
}

std::string textToHexEscape(const std::string& text) {
    std::ostringstream oss;
    bool escapeNext = false;

    for (char c : text) {
        if (escapeNext) {
            oss << c;
            escapeNext = false;
        } else if (c == '\\') {
            escapeNext = true;
            oss << c;
        } else {
            oss << "\\x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(static_cast<unsigned char>(c));
        }
    }

    return oss.str();
}

bool containsSpecialCharactersOrFormatSpecifiers(const std::string& text) {
    static const std::regex specialCharactersPattern(R"(\\n|\\r|\\t|\\b|\\f)");
    static const std::regex formatSpecifiersPattern(R"(%[diufxXc%])");

    return std::regex_search(text, specialCharactersPattern) || std::regex_search(text, formatSpecifiersPattern);
}

std::string processString(const std::string& input) {
    std::string result;
    std::regex stringPattern(R"("([^"]*)\")");
    std::smatch match;
    std::string::const_iterator searchStart(input.cbegin());

    while (std::regex_search(searchStart, input.cend(), match, stringPattern)) {
        result += std::string(searchStart, match[0].first);
        std::string quotedText = match[1].str();

        if (containsSpecialCharactersOrFormatSpecifiers(quotedText)) {
            result += "\"" + quotedText + "\"";
        } else {
            result += "\"" + textToHexEscape(quotedText) + "\"";
        }
        searchStart = match.suffix().first;
    }
    result += std::string(searchStart, input.cend());
    return result;
}

std::string convert_numbers_to_hex(const std::string& input_string) {
    std::string result = input_string;
    std::regex number_regex(R"(\b\d+\b)");
    std::sregex_iterator numbers_begin(result.begin(), result.end(), number_regex);
    std::sregex_iterator numbers_end;

    std::ptrdiff_t offset = 0;

    for (auto it = numbers_begin; it != numbers_end; ++it) {
        std::string number_str = (*it).str();
        long long number = std::stoll(number_str);
        std::ostringstream hex_number;
        hex_number << "0x" << std::hex << number;

        result.replace(it->position() + offset, number_str.length(), hex_number.str());
        offset += hex_number.str().length() - number_str.length();
    }

    return result;
}

void print_usage() {
    std::cout << "Usage: obf [options] --f input_file\n";
    std::cout << "Options:\n";
    std::cout << "  --comment_remover           Apply comment removal\n";
    std::cout << "  --process_numbers           Process numbers\n";
    std::cout << "  --variable_renamer          Rename variables\n";
    std::cout << "  --convert_numbers_to_hex    Convert numbers to hexadecimal\n";
    std::cout << "  --insert_random_functions   Insert random functions\n";
    std::cout << "  --probability <number>      Set probability for random functions (0-100)\n";
    std::cout << "  --insert_dummy_conditions   Insert dummy conditions\n";
    std::cout << "  --depth <number>            Set nesting depth for dummy conditions\n";
    std::cout << "  --process_string            Process the string\n";
    std::cout << "  --remove_extra_spaces       Remove extra spaces\n";
    std::cout << "  --help                      Show this help message\n";
}

int main(int argc, char* argv[]) {
    std::string input_file = "";
    bool apply_comment_remover = false;
    bool apply_process_numbers = false;
    bool apply_variable_renamer = false;
    bool apply_convert_numbers_to_hex = false;
    bool apply_random_functions = false;
    bool apply_dummy_conditions = false;
    bool apply_process_string = false;
    bool apply_remove_extra_spaces = false;
    int probability = 20;
    int nesting_depth = 1;

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "--help") {
            print_usage();
            return 0;
        } else if (arg == "--comment_remover") {
            apply_comment_remover = true;
        } else if (arg == "--process_numbers") {
            apply_process_numbers = true;
        } else if (arg == "--variable_renamer") {
            apply_variable_renamer = true;
        } else if (arg == "--convert_numbers_to_hex") {
            apply_convert_numbers_to_hex = true;
        } else if (arg == "--insert_random_functions") {
            apply_random_functions = true;
        } else if (arg == "--probability") {
            if (i + 1 < argc) {
                probability = std::stoi(argv[++i]);
            } else {
                std::cerr << "Error: --probability requires a value\n";
                return 1;
            }
        } else if (arg == "--insert_dummy_conditions") {
            apply_dummy_conditions = true;
        } else if (arg == "--depth") {
            if (i + 1 < argc) {
                nesting_depth = std::stoi(argv[++i]);
            } else {
                std::cerr << "Error: --depth requires a value\n";
                return 1;
            }
        } else if (arg == "--process_string") {
            apply_process_string = true;
        } else if (arg == "--remove_extra_spaces") {
            apply_remove_extra_spaces = true;
        } else if (arg == "--f") {
            if (i + 1 < argc) {
                input_file = argv[++i];
            } else {
                std::cerr << "Error: --f requires a file name\n";
                return 1;
            }
        } else {
            std::cerr << "Unknown option: " << arg << "\n";
            print_usage();
            return 1;
        }
    }

    if (input_file.empty()) {
        std::cerr << "Error: Input file must be specified with --f\n";
        return 1;
    }

    const std::string output_dir = "obf1";
    if (mkdir(output_dir.c_str(), 0755) != 0 && errno != EEXIST) {
        std::cerr << "Error: Could not create directory " << output_dir << std::endl;
        return 1;
    }

    std::string output_file = output_dir + "/obf_" + input_file;

    std::ifstream file_data(input_file);
    if (file_data) {
        std::string file_string((std::istreambuf_iterator<char>(file_data)), std::istreambuf_iterator<char>());

        std::string preprocessor_lines = extract_preprocessor_lines(file_string);

        if (apply_comment_remover) {
            file_string = comment_remover(file_string);
        }
        if (apply_process_numbers) {
            file_string = process_numbers(file_string);
        }
        if (apply_variable_renamer) {
            file_string = variable_renamer(file_string);
        }
        if (apply_convert_numbers_to_hex) {
            file_string = convert_numbers_to_hex(file_string);
        }
        if (apply_random_functions) {
            file_string = insert_random_functions(file_string, probability);
        }
        if (apply_dummy_conditions) {
            file_string = insert_dummy_conditions(file_string, nesting_depth);
        }
        if (apply_process_string) {
            file_string = processString(file_string);
        }
        if (apply_remove_extra_spaces) {
            file_string = remove_extra_spaces(file_string);
        }

        std::ofstream f(output_file);
        f << preprocessor_lines << "\n" << file_string;
        std::cout << "Output written to " << output_file << std::endl;
    } else {
        std::cerr << "File not found: " << input_file << std::endl;
        return 1;
    }


    return 0;
}
