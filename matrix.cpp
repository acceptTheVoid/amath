#include "matrix.h"

using namespace alinal;

matrix::matrix(size_t lines, size_t columns)
: size_(lines, columns) {
    data_ = new ll *[lines_];
    data_[0] = new ll[lines_ * columns_];
    for(int i = 1; i != lines_; ++i)
        data_[i] = data_[i-1] + columns_;

    fill(0);
}

matrix::~matrix() {
    delete[] data_[0];
    delete[] data_;
}

matrix matrix::null_matrix(size_t size) {
    return matrix(size, size);
}

matrix matrix::identity_matrix(size_t size) {
    matrix m(size, size);
    for(size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            if (i == j) m.data_[i][j] = 1;
    return m;
}

[[maybe_unused]]
void matrix::print() {
    for(size_t i = 0; i < lines_; i++) {
        for (size_t j = 0; j < columns_; j++)
            std::cout << data_[i][j] << " ";
        endl(std::cout);
    }
}

void matrix::fill(ll n) {
    for(int i = 0; i < lines_; i++)
        for(int j = 0; j < columns_; j++)
            data_[i][j] = n;
}

matrix::matrix(const matrix &m)
: size_(m.lines_, m.columns_) {
    data_ = new ll*[lines_];
    data_[0] = new ll[lines_ * columns_];
    for(int i = 1; i != lines_; i++)
        data_[i] = data_[i-1] + columns_;

    for(int i = 0; i < lines_; i++)
        for(int j = 0; j < columns_; j++)
            data_[i][j] = m.data_[i][j];
}

void matrix::swap(matrix &other) {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

matrix &matrix::operator=(const matrix &other) {
    if(this == &other)
        return *this;

    delete[] data_[0];
    delete[] data_;
    matrix tmp(other);
    this->swap(tmp);
    return *this;
}

[[maybe_unused]]
void matrix::input_matrix() {
    for(int i = 0; i < lines_; i++)
        for(int j = 0; j < columns_; j++)
            std::cin >> data_[i][j];
}

std::pair<size_t, size_t> matrix::size() const {
    return size_;
}

matrix matrix::transpose() {
    matrix m(columns_, lines_);
    for(size_t i = 0; i < columns_; i++)
        for(size_t j = 0; j < lines_; j++)
            m.data_[j][i] = data_[i][j];

    return m;
}

matrix matrix::get_minor(size_t line, size_t column) const {
    if(line < 1 || column < 1) {
        std::cerr << "Error! Wrong indecies in get_minor()! This realization starts"
                     "indecies in matrix from 1!\n";
        return null_matrix(1);
    } else if(line > lines_ || column > columns_) {
        std::cerr << "Error! Wrong indecies in get_minor()! You exceeded matrix size!\n";
        return null_matrix(1);
    } else if(lines_ != columns_) {
        std::cerr << "Error! get_minor() makes sense only in quad matrix!\n";
        return null_matrix(1);
    } else if(lines_ < 3 || columns_ < 3) {
        std::cerr << "Error! Matrix size must be at least 3x3 to have minor!\n";
        return null_matrix(1);
    }

    matrix minor(lines_ - 1, columns_ - 1);
    for(size_t i = 0; i < lines_; i++) {
        if(i == line - 1) continue;
        for(size_t j = 0; j < columns_; j++) {
            if(j == column - 1) continue;
            minor.data_[(i > line - 1) ? i - 1 : i][(j > column - 1) ? j - 1 : j] = data_[i][j];
        }
    }

    return minor;
}

ll matrix::find_det() const {
    if(lines_ != columns_) {
        std::cerr << "Error! Matrix must have equal sides if you want to"
                     "find it's determinator!\n";
        return 0;
    }

    ll res = 0;

    if(lines_ == 1)
        return data_[0][0];
    else if(lines_ == 2)
        return data_[0][0] * data_[1][1] - data_[1][0] * data_[0][1];
    else for(size_t j = 0; j < lines_; j++)
            res += data_[0][j] * ((j % 2) ? -1 : 1) * get_minor(1, j + 1).find_det();

    return res;
}

matrix::sub_class matrix::operator[](size_t idx) const { return sub_class(data_[idx - 1]); }

void matrix::mul(ll n) {
    for(int i = 0; i < lines_; i++)
        for(int j = 0; j < columns_; j++)
            data_[i][j] *= n;
}

matrix &matrix::operator*=(ll n) {
    this->mul(n);
    return *this;
}

matrix operator*(ll n, matrix m) {
    return m *= n;
}

matrix operator*(matrix m, ll n) {
    return m *= n;
}

void matrix::mul(const matrix &m) {
    if(columns_ != m.lines_) {
        std::cerr << "Error! When multiplied matrix lines must be equal to other matrix columns!\n";
        return;
    }

    matrix res(lines_, m.columns_);
    for(size_t i = 0; i < lines_; i++)
        for(size_t j = 0; j < m.columns_; j++)
            for(size_t x = 0; x < columns_; x++)
                res.data_[i][j] += data_[i][x] * m.data_[x][j];

    this->swap(res);
}

matrix &matrix::operator*=(matrix const &m) {
    this->mul(m);
    return *this;
}

matrix operator*(matrix m1, matrix const &m2) {
    return m1 *= m2;
}

bool matrix::equals(matrix const &right) const {
    if(lines_ != right.lines_
    || right.columns_ != columns_) return false;

    for(size_t i = 0; i < lines_; i++)
        for(size_t j = 0; j < columns_; j++)
            if(data_[i][j] != right.data_[i][j]) return false;

    return true;
}

bool operator==(matrix const &left, matrix const &right) {
    return left.equals(right);
}

void matrix::add(matrix const &m) {
    if(lines_ != m.lines_ || columns_ != m.columns_) {
        std::cerr << "Error! Matrices must have equal sides in order to add them!\n";
        return;
    }

    for(size_t i = 0; i < lines_; i++)
        for(size_t j = 0; j < columns_; j++)
            data_[i][j] += m.data_[i][j];
}

matrix &matrix::operator+=(const matrix &m) {
    this->add(m);
    return *this;
}

alinal::matrix operator+(alinal::matrix left, alinal::matrix const &right) {
    return left += right;
}

void matrix::subtract(const matrix &m) {
    if(lines_ != m.lines_ || columns_ != m.columns_) {
        std::cerr << "Error! Matrices must have equal sides in order to subtract them!\n";
        return;
    }

    for(size_t i = 0; i < lines_; i++)
        for(size_t j = 0; j < columns_; j++)
            data_[i][j] -= m.data_[i][j];
}

matrix &matrix::operator-=(const matrix &m) {
    this->subtract(m);
    return *this;
}

alinal::matrix operator-(alinal::matrix left, alinal::matrix const &right) {
    return left -= right;
}

matrix matrix::operator-() {
    matrix tmp(*this);
    for(size_t i = 0; i < lines_; i++)
        for(size_t j = 0; j < columns_; j++)
            tmp.data_[i][j] = -tmp.data_[i][j];

    return tmp;
}

matrix matrix::operator+() {
    return *this;
}

std::ostream &alinal::operator<<(std::ostream &out, const matrix &right) {
    ll max = right.max(), min = right.min();
    int counter_max = 1; int counter_min = 1, counter;
    if(max < 0) counter_max++;
    if(min < 0) counter_min++;
    while(max != 0) { counter_max++; max /= 10; }
    while(min != 0) { counter_min++; min /= 10; }
    counter = (counter_max > counter_min) ? counter_max : counter_min;

    for(size_t i = 0; i < right.lines_; i++) {
        out << "[";
        for (size_t j = 0; j < right.columns_; j++) {
            if(j == 0)  out << std::setw(counter - 1);
            else        out << std::setw(counter);
            out << right.data_[i][j];
        }
        out << "]\n";
    }

    return out;
}

std::istream &alinal::operator>>(std::istream &in, const matrix &right) {
    for(size_t i = 0; i < right.lines_; i++)
        for(size_t j = 0; j < right.columns_; j++)
            in >> right.data_[i][j];
    return in;
}

ll matrix::max() const {
    ll max = LONG_LONG_MIN;
    for(size_t i = 0; i < lines_; i++)
        for(size_t j = 0; j < columns_; j++)
            if(data_[i][j] > max) max = data_[i][j];
    return max;
}

ll matrix::min() const {
    ll min = LONG_LONG_MAX;
    for(size_t i = 0; i < lines_; i++)
        for(size_t j = 0; j < columns_; j++)
            if(data_[i][j] < min) min = data_[i][j];
    return min;
}

std::vector<ll> alinal::cramer_method(matrix const &coefficient, matrix const &comp) {
    ll det = coefficient.find_det();
    if(det == 0) return { 0 };

    std::vector<ll> ans(coefficient.lines_);
    for(size_t cur_x = 0; cur_x < ans.size(); cur_x++) {
        matrix tmp(coefficient);
        for(size_t i = 0; i < coefficient.lines_; i++)
            tmp.data_[i][cur_x] = comp.data_[i][0];

        ans[cur_x] = tmp.find_det() / det;
    }
    return ans;
}

std::vector<ll> alinal::gaussian_method(matrix coefficient,matrix comp) {
    std::vector<ll> ans(coefficient.lines_);

    if(coefficient.lines_ != coefficient.columns_) {
        std::cerr << "plesaed dude solve it yourself i cant be fucked rn\n";
        return { 0 };
    }

    for(size_t cur_x = 0; cur_x != coefficient.lines_ - 1; cur_x++) {
        for(size_t i = cur_x + 1; i != coefficient.lines_; i++) {
            ll cur = coefficient.data_[i][cur_x];
            for (size_t j = 0; j != coefficient.columns_; j++)
                coefficient.data_[i][j] = coefficient.data_[i][j] * coefficient.data_[cur_x][cur_x] - cur * coefficient.data_[cur_x][j];
            comp.data_[i][0] = comp.data_[i][0] * coefficient.data_[cur_x][cur_x] - cur * comp.data_[cur_x][0];
        }
    }

    for(size_t cur_x = coefficient.lines_ - 1; cur_x != 0; cur_x--) {
        for(size_t i = cur_x - 1; i != SIZE_MAX; i--) {
            ll cur = coefficient.data_[i][cur_x];
            for(size_t j = coefficient.columns_ - 1; j != SIZE_MAX; j--)
                coefficient.data_[i][j] = coefficient.data_[i][j] * coefficient.data_[cur_x][cur_x] - cur * coefficient.data_[cur_x][j];
            comp.data_[i][0] = comp.data_[i][0] * coefficient.data_[cur_x][cur_x] - cur * comp.data_[cur_x][0];
        }
    }

    for(size_t i = 0; i < coefficient.lines_; i++)
        ans[i] = comp.data_[i][0] / coefficient.data_[i][i];

    return ans;
}
