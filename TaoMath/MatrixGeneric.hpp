#pragma once

#include "Common.hpp"
namespace TaoMath {

template <int N, int M, typename T>
class GenericMatrix {
public:
    GenericMatrix();
    explicit GenericMatrix(const T* values);
    explicit GenericMatrix(State) {}
    const T& operator()(int row, int column) const;
    T& operator()(int row, int column);
    bool isIdentity() const;
    void setToIdentity();
    constexpr inline int rowCount() const { return N; }
    constexpr inline int columnCount() const { return M; }

    void fill(T value);
    GenericMatrix<M, N, T> transposed() const;
    GenericMatrix<N, M, T>& operator=(const GenericMatrix<N, M, T>& o);
    GenericMatrix<N, M, T>& operator+=(const GenericMatrix<N, M, T>& o);
    GenericMatrix<N, M, T>& operator-=(const GenericMatrix<N, M, T>& o);
    GenericMatrix<N, M, T>& operator*=(T factor);
    GenericMatrix<N, M, T>& operator/=(T divisor);
    bool operator==(const GenericMatrix<N, M, T>& o) const;
    bool operator!=(const GenericMatrix<N, M, T>& o) const;
    void copyDataTo(T* values) const;
    T* data() { return *m; }

    const T* data() const { return *m; }
    const T* constData() const { return *m; }

    template <int NN, int MM, typename TT>
    friend GenericMatrix<NN, MM, TT> operator+(const GenericMatrix<NN, MM, TT>& m1, const GenericMatrix<NN, MM, TT>& m2);
    template <int NN, int MM, typename TT>
    friend GenericMatrix<NN, MM, TT> operator-(const GenericMatrix<NN, MM, TT>& m1, const GenericMatrix<NN, MM, TT>& m2);
    template <int NN, int PP, int MM, typename TT>
    friend GenericMatrix<NN, MM, TT> operator*(const GenericMatrix<NN, PP, TT>& m1, const GenericMatrix<PP, MM, TT>& m2);
    template <int NN, int MM, typename TT>
    friend GenericMatrix<NN, MM, TT> operator-(const GenericMatrix<NN, MM, TT>& m);
    template <int NN, int MM, typename TT>
    friend GenericMatrix<NN, MM, TT> operator*(const GenericMatrix<NN, MM, TT>& m, TT factor);
    template <int NN, int MM, typename TT>
    friend GenericMatrix<NN, MM, TT> operator*(TT factor, const GenericMatrix<NN, MM, TT>& m);
    template <int NN, int MM, typename TT>
    friend GenericMatrix<NN, MM, TT> operator/(const GenericMatrix<NN, MM, TT>& m, TT divisor);

private:
    T m[N][M];
    template <int NN, int MM, typename TT>
    friend class GenericMatrix;
};

template <int N, int M, typename T>
GenericMatrix<N, M, T>::GenericMatrix()
{
    setToIdentity();
}
template <int N, int M, typename T>
GenericMatrix<N, M, T>::GenericMatrix(const T* values)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            m[i][j] = values[i * M + j];
        }
    }
}
template <int N, int M, typename T>
const T& GenericMatrix<N, M, T>::operator()(int row, int column) const
{
    assert(0 <= row && row < N);
    assert(0 <= column && column < M);
    return m[row][column];
}
template <int N, int M, typename T>
T& GenericMatrix<N, M, T>::operator()(int row, int column)
{
    assert(0 <= row && row < N);
    assert(0 <= column && column < M);
    return m[row][column];
}
template <int N, int M, typename T>
bool GenericMatrix<N, M, T>::isIdentity() const
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == j) {
                if (m[i][j] != 1.0f) {
                    return false;
                }
            } else {
                if (m[i][j] != 0.0f) {
                    return false;
                }
            }
        }
    }
    return true;
}
template <int N, int M, typename T>
void GenericMatrix<N, M, T>::setToIdentity()
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == j) {
                m[i][j] = 1.0f;
            } else {
                m[i][j] = 0.0f;
            }
        }
    }
}
template <int N, int M, typename T>
void GenericMatrix<N, M, T>::fill(T value)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            m[i][j] = value;
        }
    }
}
template <int N, int M, typename T>
GenericMatrix<M, N, T> GenericMatrix<N, M, T>::transposed() const
{
    GenericMatrix<M, N, T> result(State::Uninitialized);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            result.m[j][i] = m[i][j];
        }
    }
    return result;
}
template <int N, int M, typename T>
GenericMatrix<N, M, T>& GenericMatrix<N, M, T>::operator=(const GenericMatrix<N, M, T>& o) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            m[i][j] = o.m[i][j];
        }
    }
    return *this;
}
template <int N, int M, typename T>
GenericMatrix<N, M, T>& GenericMatrix<N, M, T>::operator+=(const GenericMatrix<N, M, T>& o)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            m[i][j] += o.m[i][j];
        }
    }
    return *this;
}
template <int N, int M, typename T>
GenericMatrix<N, M, T>& GenericMatrix<N, M, T>::operator-=(const GenericMatrix<N, M, T>& o)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            m[i][j] -= o.m[i][j];
        }
    }
    return *this;
}
template <int N, int M, typename T>
GenericMatrix<N, M, T>& GenericMatrix<N, M, T>::operator*=(T factor)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            m[i][j] *= factor;
        }
    }
    return *this;
}
template <int N, int M, typename T>
GenericMatrix<N, M, T>& GenericMatrix<N, M, T>::operator/=(T divisor)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            m[i][j] /= divisor;
        }
    }
    return *this;
}
template <int N, int M, typename T>
bool GenericMatrix<N, M, T>::operator==(const GenericMatrix<N, M, T>& o) const
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (m[i][j] != o.m[i][j]) {
                return false;
            }
        }
    }
    return true;
}
template <int N, int M, typename T>
bool GenericMatrix<N, M, T>::operator!=(const GenericMatrix<N, M, T>& o) const
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (m[i][j] != o.m[i][j]) {
                return true;
            }
        }
    }
    return false;
}
template <int N, int M, typename T>
void GenericMatrix<N, M, T>::copyDataTo(T* values) const
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            values[i * M + j] = m[i][j];
        }
    }
}

template <int NN, int MM, typename TT>
GenericMatrix<NN, MM, TT> operator+(const GenericMatrix<NN, MM, TT>& m1, const GenericMatrix<NN, MM, TT>& m2)
{
    GenericMatrix<NN, MM, TT> result(State::Uninitialized);
    for (int i = 0; i < NN; ++i) {
        for (int j = 0; j < MM; ++j) {
            result.m[i][j] = m1.m[i][j] + m2.m[i][j];
        }
    }
    return result;
}
template <int NN, int MM, typename TT>
GenericMatrix<NN, MM, TT> operator-(const GenericMatrix<NN, MM, TT>& m1, const GenericMatrix<NN, MM, TT>& m2)
{
    GenericMatrix<NN, MM, TT> result(State::Uninitialized);
    for (int i = 0; i < NN; ++i) {
        for (int j = 0; j < MM; ++j) {
            result.m[i][j] = m1.m[i][j] - m2.m[i][j];
        }
    }
    return result;
}
template <int NN, int PP, int MM, typename TT>
GenericMatrix<NN, MM, TT> operator*(const GenericMatrix<NN, PP, TT>& m1, const GenericMatrix<PP, MM, TT>& m2)
{
    GenericMatrix<NN, MM, TT> result(State::Uninitialized);
    for (int i = 0; i < NN; ++i) {
        for (int j = 0; j < MM; ++j) {
            TT sum(0);
            for (int k = 0; k < PP; ++k) {
                sum += m1.m[i][k] * m2.m[k][j];
            }
            result.m[i][j] = sum;
        }
    }
    return result;
}
template <int NN, int MM, typename TT>
GenericMatrix<NN, MM, TT> operator-(const GenericMatrix<NN, MM, TT>& m)
{
    GenericMatrix<NN, MM, TT> result(State::Uninitialized);
    for (int i = 0; i < NN; ++i) {
        for (int j = 0; j < MM; ++j) {
            result.m[i][j] = -m.m[i][j];
        }
    }
    return result;
}
template <int NN, int MM, typename TT>
GenericMatrix<NN, MM, TT> operator*(const GenericMatrix<NN, MM, TT>& m, TT factor)
{
    GenericMatrix<NN, MM, TT> result(State::Uninitialized);
    for (int i = 0; i < NN; ++i) {
        for (int j = 0; j < MM; ++j) {
            result.m[i][j] = m.m[i][j] * factor;
        }
    }
    return result;
}
template <int NN, int MM, typename TT>
GenericMatrix<NN, MM, TT> operator*(TT factor, const GenericMatrix<NN, MM, TT>& m)
{

    GenericMatrix<NN, MM, TT> result(State::Uninitialized);
    for (int i = 0; i < NN; ++i) {
        for (int j = 0; j < MM; ++j) {
            result.m[i][j] = m.m[i][j] * factor;
        }
    }
    return result;
}
template <int NN, int MM, typename TT>
GenericMatrix<NN, MM, TT> operator/(const GenericMatrix<NN, MM, TT>& m, TT divisor)
{
    GenericMatrix<NN, MM, TT> result(State::Uninitialized);
    for (int i = 0; i < NN; ++i) {
        for (int j = 0; j < MM; ++j) {
            result.m[i][j] = m.m[i][j] / divisor;
        }
    }
    return result;
}
using Matrix2x2 = GenericMatrix<2, 2, real>;
using Matrix2x3 = GenericMatrix<2, 3, real>;
using Matrix2x4 = GenericMatrix<2, 4, real>;
using Matrix3x2 = GenericMatrix<3, 2, real>;
using Matrix3x3 = GenericMatrix<3, 3, real>;
using Matrix3x4 = GenericMatrix<3, 4, real>;
using Matrix4x2 = GenericMatrix<4, 2, real>;
using Matrix4x3 = GenericMatrix<4, 3, real>;

}
