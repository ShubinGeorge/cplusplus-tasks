 #include "matrix.h"
#include <cassert>

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



Matrix::Matrix(const size_t line_number, const size_t column_number)
{
	for (size_t i = 0; i < line_number; i++)
	{
		std::vector<int> line;
		for (size_t j = 0; j < column_number; j++)
		{
			line.push_back(0);
		}
		data_.push_back(line);
	}
}


void Matrix::SetValue(const size_t line_index, const size_t column_index,
	const int value)
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


Matrix Matrix::operator*(const Matrix& rhs)
{
	assert(data_[0].size() == rhs.GetHeight());
	Matrix result(data_.size(), rhs.GetWidth());

	int element = 0;
	for (size_t i = 0; i < data_.size(); i++)
	{
		for (size_t j = 0; j < rhs.GetWidth(); j++)
		{
			for (size_t k = 0; k < data_[0].size(); k++)
			{
				element += data_[i][k] * rhs.GetValue(k, j);
			}
			result.SetValue(i, j, element);
			element = 0;
		}
	}

	return result;
}

