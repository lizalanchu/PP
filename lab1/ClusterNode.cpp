#include <iostream>
#include <string>

class ClusterNode {
public:
    CpuSpec cpu;
    GpuSpec gpu;
    RamSpec ram;
    LanSpec lan;

    ClusterNode(CpuSpec c, GpuSpec g, RamSpec r, LanSpec l) 
        : cpu(c), gpu(g), ram(r), lan(l) {}

    void Print() const {
        std::cout << "Cluster Node Specifications:\n";
        cpu.Print();
        gpu.Print();
        ram.Print();
        lan.Print();
    }

    void Import(std::istream& in) {
        cpu.Import(in);
        gpu.Import(in);
        ram.Import(in);
        lan.Import(in);
    }

    void Export(std::ostream& out) const {
        cpu.Export(out);
        gpu.Export(out);
        ram.Export(out);
        lan.Export(out);
    }
};
