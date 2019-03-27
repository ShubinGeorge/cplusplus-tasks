#include "matrix.h"
#include "profile.h"
#include <cassert>
#include <future>


std::istream& operator >> (std::istream& input_stream, Matrix& matrix)
{
    for (size_t y = 0; y < matrix.GetHeight(); y++)
    {
        for (size_t x = 0; x < matrix.GetWidth(); x++)
        {
            int temp_int = 0;
            input_stream >> temp_int;
            matrix.SetValue(y, x, temp_int);
        }
    }
    return input_stream;
}


std::ostream& operator << (std::ostream& os, const Matrix& matrix)
{
    for (size_t y = 0; y < matrix.GetHeight(); y++)
    {
        os << "| ";
        for (size_t x = 0; x < matrix.GetWidth(); x++)
        {
            os << matrix.GetValue(y, x) << " ";
        }
        os << "|" << "\n";
    }
    return os;
}


bool Matrix::operator==(const Matrix& rhs) const
{
    if (data_.size() == rhs.GetHeight() && data_[0].size() == rhs.GetWidth())
    {
        for (size_t i = 0; i < data_.size(); i++)
        {
            for (size_t j = 0; j < data_[0].size(); j++)
            {
                if (data_[i][j] != rhs.GetValue(i, j))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& rhs) const
{
    return !(*this == rhs);
}


Matrix::Matrix(const size_t line_number, const size_t column_number)
{
    data_.reserve(line_number);
    for (size_t i = 0; i < line_number; i++)
    {
        std::vector<int> line(column_number);
        data_.push_back(std::move(line));
    }
}


void Matrix::SetValue(const size_t line_index,
            const size_t column_index,const int value)
{
    data_[line_index][column_index] = value;
}


int Matrix::GetValue(const size_t line_index, const size_t column_index) const
{
    return data_[line_index][column_index];
}


size_t Matrix::GetHeight() const
{
    return data_.size();
}


size_t Matrix::GetWidth() const
{
    if (data_.size() > 0)
    {
        return data_[0].size();
    }
    return 0;
}


const std::vector<std::vector<int>>& Matrix::GetData() const
{
    return data_;
}

Matrix Matrix::operator+(const Matrix& rhs)
{
    assert(this->GetHeight() == rhs.GetHeight());
    assert(this->GetWidth() == rhs.GetWidth());

    Matrix result(this->GetHeight(), this->GetWidth());

    for (size_t i = 0; i < rhs.GetHeight(); i++)
    {
        for (size_t j = 0; j < rhs.GetWidth(); j++)
        {
            result.SetValue(i, j, data_[i][j] + rhs.GetValue(i, j));
        }
    }
    return result;
}

Matrix Matrix::Transpose() const
{
    if (data_.size() > 0)
    {
        Matrix result(data_[0].size(), data_.size());
        for (size_t i = 0; i < result.GetWidth(); i++)
        {
            for (size_t j = 0; j < result.GetHeight(); j++)
            {
                result.SetValue(j, i, data_[i][j]);
            }
        }
        return result;
    }
    return Matrix(0, 0);
}


Matrix Matrix::TmpMultiplication(const Matrix& rhs, const size_t beg_pos, const size_t end_pos)  
{
    Matrix result(this->GetHeight(),rhs.GetWidth());	
    Matrix intermediate(rhs.GetWidth(), rhs.GetHeight());
    intermediate = rhs.Transpose();

    for (size_t i = beg_pos; i < end_pos; i++)
    {
        int element = 0;
        for (size_t j = 0; j < intermediate.GetHeight(); j++)
        {
            for (size_t k = 0; k < data_[0].size(); k++)
            {
                element += data_[i][k] * intermediate.GetValue(j, k);
            }
            result.SetValue(i, j, element);
            element = 0;
        }
    }	
    return result;
}


Matrix Matrix::operator*(const Matrix& rhs)
{
    if(data_[0].size() == rhs.GetHeight())
    {
        Matrix result(data_.size(), rhs.GetWidth());
		
        const int threads_count = 4;
        std::vector<std::future<Matrix>> partials;
        partials.reserve(threads_count);
		
        for (size_t i = 0; i < threads_count; i++)
        {
            const size_t beg_pos = i * this->GetHeight() / threads_count;
            const size_t end_pos = (i + 1 == threads_count) ?
                    this->GetHeight() : (i + 1) * this->GetHeight() / threads_count;

            std::future<Matrix> part_of_result = std::async(
            std::launch::async,
            &Matrix::TmpMultiplication, this, std::ref(rhs), beg_pos, end_pos
            );			
 
            partials.push_back(std::move(part_of_result));    
        }
	
        for (size_t i = 0; i < threads_count; i++)
        {
            result = result + partials[i].get();
        }

        return result;
    }
    else  std::logic_error{"incorrect sizes of multiplying matrices"};
}

