#include "TinyML.h"
#include <random>

namespace TinyML {
Matrix::Matrix(int r, int c) : rows(r), cols(c) { data.resize(r * c, 0.0f); }

void Matrix::fill(float value) { std::fill(data.begin(), data.end(), value); }

void Matrix::randomize(float min, float max) {
  static std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<float> dist(min, max);
  for (float &v : data)
    v = dist(rng);
}

Linear::Linear(int in_size, int out_size) {
  weights = Matrix(out_size, in_size);
  biases = Matrix(1, out_size);
  weights.randomize(-1.0f, 1.0f);
  biases.fill(0.0f);
}

void Linear::forward(const Matrix &input, Matrix &output) const {
  if (output.rows != input.rows || output.cols != weights.cols) {
    output = Matrix(input.rows, weights.cols);
  }
  for (int i = 0; i < output.cols; i++) {
    float b = biases.data[i];
    for (int r = 0; r < input.rows; ++r) {
      float sum = b;
      for (int j = 0; j < input.cols; ++j) {
        sum += input(r, j) * weights(i, j);
      }
      output(r, i) = sum;
    }
  }
}
void relu(Matrix &m) {
  for (float &v : m.data)
    v = std::max(v, 0.0f);
}
void sigmoid(Matrix &m) {
  for (float &v : m.data)
    v = 1.0f / (1.0f + exp(-v));
}

void tanh(Matrix &m) {
  for (float &v : m.data)
    v = std::tanh(v);
}
void softmax(Matrix &m) {
  float sum = 0.0f;
  for (float &v : m.data)
    sum += std::exp(v);
  for (float &v : m.data)
    v = std::exp(v) / sum;
}
} // namespace TinyML
