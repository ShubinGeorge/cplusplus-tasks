#include "forest.h"
#include <cassert>


Forest::Forest(const size_t line_number, const size_t column_number)
{
    for (size_t i = 0; i < line_number; i++)
    {
        std::vector<Tree> line;
        for (size_t j = 0; j < column_number; j++)
        {
            Tree tree;
            line.push_back(std::move(tree));
        }
        data_.push_back(std::move(line));
    }    
}

int Forest::GetBurnNeighbour(int y, int x)
{
    int burn_neighbours_count = 0;
    for (int j = y - 1; j <= y + 1; j++)
    {
        for (int i = x - 1; i <= x + 1; i++)
        {
            if (j < 0 || j >= data_.size() || i < 0
                || i >= data_[0].size() || i == x && j == y)
            {
                continue;
            }
            else
            {
                if (data_[j][i].current_state_ == STATUS_BURN)
                {
                    burn_neighbours_count++; 
                }
            }
        }
    }
    return burn_neighbours_count;
}

void Forest::Update()
{
    for (int y = 0; y < data_.size(); y++)
    {
        for (int x = 0; x < data_[0].size(); x++)
        {
            int burn_neighbours_count = GetBurnNeighbour(y, x);
            if (data_[y][x].current_state_ == STATUS_GROW)
            {
                if (data_[y][x].armor_ - burn_neighbours_count >= 0)
                {
                    data_[y][x].armor_ -= burn_neighbours_count;
                }
                else
                {
                    data_[y][x].armor_ = 0;
                }
            }

            if (data_[y][x].current_state_ == STATUS_BURN)
            {
                if (data_[y][x].health_ - burn_neighbours_count >= 0)
                {
                    data_[y][x].health_ -= burn_neighbours_count;
                }
                else
                {
                    data_[y][x].health_ = 0;
                }
            }
        }
    }

    for (int y = 0; y < data_.size(); y++)
    {
        for (int x = 0; x < data_[0].size(); x++)
        {
            if (data_[y][x].current_state_ == STATUS_DEAD)
            {
                data_[y][x].current_state_ = STATUS_GROW;
                data_[y][x].armor_ = 5;
                data_[y][x].health_ = 10;
            }
            if (data_[y][x].armor_ == 0 && data_[y][x].health_ != 0)
            {
                data_[y][x].current_state_ = STATUS_BURN;
            }
            if (data_[y][x].health_ == 0)
            {
                data_[y][x].current_state_ = STATUS_DEAD;
            }
        }
    }
}

                  
std::ostream& operator << (std::ostream& os, const Forest& matrix)
{
    for (size_t y = 0; y < matrix.GetHeight(); y++)
    {
        os << "[ ";
        for (size_t x = 0; x < matrix.GetWidth(); x++)
        {
            if (matrix.GetCurrState(y, x) == STATUS_GROW)
            {
                os << '|' << " ";
            }
            if (matrix.GetCurrState(y, x) == STATUS_BURN)
            {
                os << '*' << " ";
            }
            if (matrix.GetCurrState(y, x) == STATUS_DEAD)
            {
                os << ' ' << " ";
            }
        }
        os << "]" << "\n";
    }
    return os;
}



void Forest::SetValue(const size_t line_index, const size_t column_index,
    const int health, const int armor, const int curr_state)
{
    data_[line_index][column_index].health_ = health;
    data_[line_index][column_index].armor_ = armor;
    data_[line_index][column_index].current_state_ = curr_state;
}


size_t Forest::GetHealth(const size_t line_index, const size_t column_index) const
{
    return data_[line_index][column_index].health_;
}


size_t Forest::GetCurrState(const size_t line_index, const size_t column_index) const
{
    return data_[line_index][column_index].current_state_;
}


size_t Forest::GetHeight() const
{
    return data_.size();
}


size_t Forest::GetWidth() const
{
    if (data_.size() > 0)
    {
        return data_[0].size();
    }
    return 0;
}

const std::vector<std::vector<Tree>>& Forest::GetData() const
{
    return data_;
}