#include "TinyML.h"
#include <random>

namespace TinyML{
    Matrix::Matrix(int r, int c):rows(r),cols(c){
        data.resize(r*c,0.0f);
    }

    void Matrix::fill(float value){
        std::fill(data.begin(),data.end(),value);
        }
    }

    void Matrix::randomize(float min, float max)
}
