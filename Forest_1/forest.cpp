#include "forest.h"
#include <cassert>


struct Tree
{
    size_t health_ = 0;
    size_t current_state_ = 0;
    bool indicator_ = false;
};


Forest::Forest(const size_t line_number, const size_t column_number)
{
    
    for (size_t i = 0; i < line_number; i++)
    {
        std::vector<Tree> line;
        for (size_t j = 0; j < column_number; j++)
        {
            Tree tree;
            line.push_back(tree);
        }
        data_.push_back(line);
    }
    
}


void Forest::Update()
{
    for (size_t y = 0; y < data_.size(); y++)
    {
        for (size_t x = 0; x < data_[0].size(); x++)
        {
            if (data_[x][y].current_state_ == 2)
            {
                data_[x][y].current_state_ = 0;
                data_[x][y].health_ = 5;
            }
            else if (data_[x][y].current_state_ == 1)
            {
                if (data_[x][y].health_ > 0)
                {
                    data_[x][y].health_ -= 1;
                }
                else if (data_[x][y].health_ == 0)
                {
                    data_[x][y].current_state_ = 2;
                    data_[x][y].health_ = 5;
                    data_[x][y].indicator_ = false;
                }
                //---------------------------//

                if (data_[x - 1][y - 1].health_ > 0 & y - 1 >= 0 & x - 1 >= 0 & data_[x - 1][y - 1].current_state_ == 0)
                {
                    data_[x - 1][y - 1].health_ -= 1;
                    data_[x - 1][y - 1].current_state_ == 1;
                    data_[x - 1][y - 1].indicator_ = true;
                }

                if (data_[x][y - 1].health_ > 0 & y - 1 >= 0 & data_[x][y - 1].current_state_ == 0)
                {
                    data_[x][y - 1].health_ -= 1;
                    data_[x][y - 1].current_state_ == 1;
                    data_[x][y - 1].indicator_ = true;
                }


                if (data_[x][y + 1].health_ > 0 & x <= data_.size() & y + 1 <= data_[0].size() & data_[x][y + 1].current_state_ == 0)
                {
                    data_[x][y + 1].health_ -= 1;
                    data_[x][y + 1].current_state_ == 1;
                    data_[x][y + 1].indicator_ = true;
                }

                if (data_[x - 1][y].health_ > 0 & x - 1 >= 0 & y >= 0 & data_[x - 1][y].current_state_ == 0)
                {
                    data_[x - 1][y].health_ -= 1;
                    data_[x - 1][y].current_state_ == 1;
                    data_[x - 1][y].indicator_ = true;
                }

 /*               
                if (data_[x + 1][y].health_ > 0 & x + 1 <= data_[0].size() & data_[x + 1][y].current_state_ == 0)
                {
                    data_[x + 1][y].health_ -= 1;
                    data_[x + 1][y].current_state_ == 1;
                    data_[x + 1][y].indicator_ = true;
                }

                /*
                if (data_[x + 1][y - 1].health_ > 0 & x + 1 <= data_.size() & y - 1 >= 0 & data_[x + 1][y - 1].current_state_ == 0)
                {
                    data_[x + 1][y - 1].health_ -= 1;
                    data_[x + 1][y + 1].current_state_ == 1;
                    data_[x + 1][y - 1].indicator_ = true;
                }
       
               if (x + 1 < data_.size() & y + 1 < data_[0].size() & data_[x + 1][y + 1].health_ > 0 & data_[x + 1][y + 1].current_state_ == 0)
                {
                    data_[x + 1][y + 1].health_ -= 1;
                    data_[x + 1][y + 1].current_state_ == 1;
                    data_[x + 1][y + 1].indicator_ = true;
                }
              

                if (data_[x + 1][y - 1].health_ > 0  & x + 1 <= data_.size() & y - 1 >= 0 & data_[x + 1][y - 1].current_state_ == 0)
                {
                    data_[x + 1][y - 1].health_ -= 1;
                    data_[x + 1][y - 1].indicator_ = true;
                }
                


                if (data_[x + 1][y].health_ > 0 & x + 1 <= data_.size() & y >= 0 & data_[x + 1][y].current_state_ == 0)
                {
                    data_[x + 1][y].health_ -= 1;
                    data_[x + 1][y].indicator_ = true;
                }
                
                if (data_[x - 1][y + 1].health_ > 0 & x - 1 >= 0 & y + 1 <= data_[0].size() & data_[x - 1][y + 1].current_state_ == 0)
                {
                    data_[x - 1][y + 1].health_ -= 1;
                    data_[x - 1][y + 1].indicator_ = true;
                }

                if (data_[x][y + 1].health_ > 0 & x <= data_.size() & y + 1 <= data_[0].size() & data_[x][y + 1].current_state_ == 0)
                {
                    data_[x][y + 1].health_ -= 1;
                    data_[x][y + 1].indicator_ = true;
                }

                if (data_[x + 1][y + 1].health_ > 0 & x + 1 <= data_.size() & y + 1 <= data_[0].size() & data_[x + 1][y + 1].current_state_ == 0)
                {
                    data_[x + 1][y + 1].health_ -= 1;
                    data_[x + 1][y + 1].indicator_ = true;
                }
            */
            }
        }
    }
    
    for (size_t y = 0; y < data_.size(); y++)
    {
        for (size_t x = 0; x < data_[0].size(); x++)
        {
            if (data_[x][y].indicator_ == 1 & data_[x][y].current_state_ != 2)
            {
                data_[x][y].current_state_ = 1;
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
            if (matrix.GetCurrState(x, y) == 0)
            {
                os << '|' << " ";
            }
            if (matrix.GetCurrState(x, y) == 1)
            {
                os << '*' << " ";
            }
            if (matrix.GetCurrState(x, y) == 2)
            {
                os << ' ' << " ";
            }
        }
        os << "]" << "\n";
    }
    return os;
}



void Forest::SetValue(const size_t line_index, const size_t column_index,
    const int health, const int curr_state)
{
    data_[line_index][column_index].health_ = health;
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

