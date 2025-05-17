#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

bool interpret(std::istream& input, std::ostream& output);

std::vector<std::string> tokenize(const std::string& code);
std::unordered_map<std::string, std::function<void()>> parse(const std::vector<std::string>& tokens);
void execute(const std::unordered_map<std::string, std::function<void()>>& functions);
