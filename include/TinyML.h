#pragma once

#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>

namespace TinyML{
    struct Matrix{
        int rows,cols;
        std::vector<float> data;

        Matrix():rows(0),cols(0){};
        Matrix(int r, int c);

        float& operator()(int r, int c){return data[r*cols+c];}
        const float& operator()(int r, int c)const{return data[r*cols+c];}
        void fill(float value);
        void randomize(float min, float max);
        static Matrix add(const Matrix& a,const Matrix& b);
        static Matrix multiply(const Matrix& a,const Matrix& b);
    };

    struct Linear{
        Matrix weights;
        Matrix biases;

        Linear(int in_size,int out_size);
        void forward(const Matrix& input,Matrix& output) const;

    };

    void relu(Matrix& m);
    void softmax(Matrix& m);
    void sigmoid(Matrix& m);
    void tanh(Matrix& m);
}

