#pragma once

#include <iostream>
#include <vector>
#include <istream>
#include <ostream>


class Matrix
{
    friend std::istream& operator>>(std::istream& input_stream, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

public: 
    Matrix(const size_t column_number, const size_t line_number);
    Matrix() = default;
    virtual ~Matrix() = default;

    size_t GetHeight() const;
    size_t GetWidth() const;

    int GetValue(const size_t height_index, const size_t width_index) const;
    void SetValue(const size_t height_index, const size_t width_index,
                  const int value);

    Matrix Transpose() const;
    Matrix operator*(const Matrix& rhs);
    Matrix operator+(const Matrix& rhs);

    Matrix TmpMultiplication(const Matrix& rhs, const int beg_pos, const int end_pos);

    bool operator==(const Matrix& rhs) const;
    bool operator!=(const Matrix& rhs) const;

    const std::vector<std::vector<int>>& GetData() const;

private:
    std::vector<std::vector<int>> data_;
};


std::istream& operator>>(std::istream& input_stream, Matrix& matrix);
std::ostream& operator<<(std::ostream& output_stream, const Matrix& matrix);

