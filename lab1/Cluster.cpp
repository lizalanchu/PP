#include <iostream>
#include <vector>
#include <fstream>

class Cluster {
public:
    std::vector<ClusterNode> nodes;

    void AddNode(const ClusterNode& node) {
        nodes.push_back(node);
    }

    void Print() const {
        std::cout << "Cluster consists of " << nodes.size() << " nodes:\n";
        for (const auto& node : nodes) {
            node.Print();
            std::cout << "------------------\n";
        }
    }

    void Import(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        int nodeCount;
        file >> nodeCount;
        for (int i = 0; i < nodeCount; ++i) {
            CpuSpec cpu;
            GpuSpec gpu;
            RamSpec ram;
            LanSpec lan;
            cpu.Import(file);
            gpu.Import(file);
            ram.Import(file);
            lan.Import(file);
            nodes.emplace_back(cpu, gpu, ram, lan);
        }
    }

    void Export(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        file << nodes.size() << std::endl;
        for (const auto& node : nodes) {
            node.Export(file);
        }
    }
};
