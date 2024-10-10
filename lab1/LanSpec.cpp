#include <iostream>
#include <string>

class LanSpec {
public:
    std::string type;
    double speed;  // В Гбит/с

    LanSpec(std::string t = "Unknown", double s = 0.0) 
        : type(t), speed(s) {}

    void Print() const {
        std::cout << "LAN Type: " << type 
                  << ", Speed: " << speed << " Gbps" << std::endl;
    }

    void Import(std::istream& in) {
        in >> type >> speed;
    }

    void Export(std::ostream& out) const {
        out << type << " " << speed << std::endl;
    }
};
