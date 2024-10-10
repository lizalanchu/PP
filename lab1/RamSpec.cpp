#include <iostream>
#include <string>

class RamSpec {
public:
    std::string type;
    int size;  // В МБ

    RamSpec(std::string t = "Unknown", int s = 0) 
        : type(t), size(s) {}

    void Print() const {
        std::cout << "RAM Type: " << type 
                  << ", Size: " << size << " MB" << std::endl;
    }

    void Import(std::istream& in) {
        in >> type >> size;
    }

    void Export(std::ostream& out) const {
        out << type << " " << size << std::endl;
    }
};
