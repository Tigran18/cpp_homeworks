#pragma once
template <typename T>
class Add {
private:
    size_t row;
    size_t column;
    std::vector<std::vector<T>> vec1;
    std::vector<std::vector<T>> vec2;
    class Row {
        private:
            const std::vector<T>& vec1_row;
            const std::vector<T>& vec2_row;
    
        public:
            Row(const std::vector<T>& vec1_row, const std::vector<T>& vec2_row) 
                : vec1_row(vec1_row), vec2_row(vec2_row) {}
    
            T operator[](size_t j) const {
                return vec1_row[j] + vec2_row[j];
            }
        };

public:
    Add(const std::vector<std::vector<T>>& vec1, const std::vector<std::vector<T>>& vec2) 
        : vec1(vec1), vec2(vec2), row(vec1.size()), column(vec1[0].size()) {}


    Row operator[](size_t i) const {
        return Row(vec1[i], vec2[i]);
    }

    void print() const {
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < column; ++j) {
                std::cout << (*this)[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};
