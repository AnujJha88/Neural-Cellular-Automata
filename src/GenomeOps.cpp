#include "GenomeOps.h"
#include <random>

namespace GenomeOps
{

    void mutate_matrix(TinyML::Matrix &m, float rate, float strength)
    {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> prob(0.0f, 1.0f);
        std::normal_distribution<float> noise(0.0f, strength);

        for (int r = 0; r < m.rows; ++r)
        {
            for (int c = 0; c < m.cols; ++c)
            {
                if (prob(rng) < rate)
                {
                    m(r, c) += noise(rng);
                }
            }
        }
    }

    void mutate(Genome &g, float rate, float strength)
    {
        mutate_matrix(g.layer1.weights, rate, strength);
        mutate_matrix(g.layer1.biases, rate, strength);
        mutate_matrix(g.layer2.weights, rate, strength);
        mutate_matrix(g.layer2.biases, rate, strength);
    }

    TinyML::Matrix cross_matrix(const TinyML::Matrix& A, const TinyML::Matrix& B){
    TinyML::Matrix child(A.rows, A.cols);
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> coin(0, 1);

    for(size_t i=0;i<A.data.size();i++){
        child.data[i]=(coin(rng)==0)?A.data[i]:B.data[i];
    }

    return child;
}
    Genome crossover(const Genome &a, const Genome &b)
    {
        Genome child;
        child.layer1.weights = cross_matrix(a.layer1.weights, b.layer1.weights);
        child.layer1.biases = cross_matrix(a.layer1.biases, b.layer1.biases);
        child.layer2.weights = cross_matrix(a.layer2.weights, b.layer2.weights);
        child.layer2.biases = cross_matrix(a.layer2.biases, b.layer2.biases);
        return child;
    }
}
