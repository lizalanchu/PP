#include <iostream>
#include <string>

class CpuSpec {
public:
    std::string model;
    int cores;
    double frequency;  // В ГГц

    CpuSpec(std::string m = "Unknown", int c = 0, double f = 0.0)
        : model(m), cores(c), frequency(f) {}

    void Print() const {
        std::cout << "CPU Model: " << model 
                  << ", Cores: " << cores 
                  << ", Frequency: " << frequency << " GHz" << std::endl;
    }

    void Import(std::istream& in) {
        in >> model >> cores >> frequency;
    }

    void Export(std::ostream& out) const {
        out << model << " " << cores << " " << frequency << std::endl;
    }
};
