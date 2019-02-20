#pragma once

#include <iostream>
#include <vector>
#include <istream>
#include <ostream>

struct Tree;

class Forest
{

	friend std::ostream& operator<<(std::ostream& os, const Forest& matrix);

public: 
    Forest(const size_t column_number, const size_t line_number);

    size_t GetHealth(const size_t height_index, const size_t width_index) const;
    size_t GetCurrState(const size_t line_index, const size_t column_index) const;
    size_t GetHeight() const;
    size_t GetWidth() const;
    void SetValue(const size_t height_index, const size_t width_index,
                                            const int health, const int curr_state);

    void Update();
private:
    std::vector<std::vector<Tree>> data_;
};

std::ostream& operator<<(std::ostream& output_stream, const Forest& matrix);

