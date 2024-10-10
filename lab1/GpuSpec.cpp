#include <iostream>
#include <string>

class GpuSpec {
public:
    std::string model;
    int memorySize;  // В МБ
    int cores;

    GpuSpec(std::string m = "Unknown", int mem = 0, int c = 0)
        : model(m), memorySize(mem), cores(c) {}

    void Print() const {
        std::cout << "GPU Model: " << model 
                  << ", Memory: " << memorySize 
                  << " MB, Cores: " << cores << std::endl;
    }

    void Import(std::istream& in) {
        in >> model >> memorySize >> cores;
    }

    void Export(std::ostream& out) const {
        out << model << " " << memorySize << " " << cores << std::endl;
    }
};
