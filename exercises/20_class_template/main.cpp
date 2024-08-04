#include "../exercise.h"

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template&gt;  

 template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }
        data = new T[size];
        std::wmemcpy(data, data_, size * sizeof(T));
    }
    ~Tensor4D() {
        delete[] data;
    }

    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    Tensor4D &operator+=(Tensor4D const &others) {
        unsigned int broadcast_shape[4];
        for (int i = 0; i < 4; ++i) {
            if (shape[i] == others.shape[i] || others.shape[i] == 1) {
                broadcast_shape[i] = shape[i];
            } else if (shape[i] == 1) {
                broadcast_shape[i] = others.shape[i];
            } else {
                throw std::invalid_argument("Shapes are not compatible for broadcasting");
            }
        }

        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            size *= broadcast_shape[i];
        }

        T *temp_data = new T[size]();
        for (unsigned int i = 0; i < size; ++i) {
            unsigned int idx = i;
            unsigned int index = 0;
            unsigned int b_i = 1;
            for (int d = 3; d >= 0; --d) {
                unsigned int s = idx % broadcast_shape[d];
                idx /= broadcast_shape[d];
                index += s * (shape[d] == 1 ? 0 : b_i);
                b_i *= shape[d];
            }
            temp_data[i] = data[index];
        }

        for (unsigned int i = 0; i < size; ++i) {
            unsigned int idx = i;
            unsigned int index = 0;
            unsigned int b_i = 1;
            for (int d = 3; d >= 0; --d) {
                unsigned int s = idx % broadcast_shape[d];
                idx /= broadcast_shape[d];
                index += s * (others.shape[d] == 1 ? 0 : b_i);
                b_i *= others.shape[d];
            }
            temp_data[i] += others.data[index];
        }

        delete[] data;
        data = temp_data;
        for (int i = 0; i < 4; ++i) {
            shape[i] = broadcast_shape[i];
        }

        return *this;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}