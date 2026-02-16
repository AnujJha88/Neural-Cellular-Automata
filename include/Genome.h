#pragma once
#include<vector>
struct Genome{
std::vector<float> w1;//48->32
std::vector<float> b1;
std::vector<float> w2;//32->16
std::vector<float> b2;
};

Genome create_random_genome()
