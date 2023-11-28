#include <iostream>
#include <unordered_map>
/* unordered_map like as map, but faster and need more memory
   in map, data are pair ( <datatype key, datatype value> )
   key only appear once in map, it can use to one-to-one mapping
*/
class String {
public:
    static std::unordered_map<char, int> Frequency(const std::string& str) {
        std::unordered_map<char, int> frequencyMap;

        for (char ch : str) {            // for all the char in the string
            frequencyMap[ch]++;          // the mapped value of key will be plus, if it doesn't exist, it would be created as <key, 1>
        } 

        return frequencyMap;
    }
};

int main() {
    std::string str;
    while(getline(std::cin, str)){
        std::unordered_map<char, int> result = String::Frequency(str);

        std::cout << "Character frequencies in the string:\n";
        for (const auto& pair : result) {
            std::cout << "'" << pair.first << "': " << pair.second << " times\n";
        }
    }
    return 0;
}