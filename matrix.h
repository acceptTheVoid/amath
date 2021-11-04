#ifndef CPP_LINAL_MATRIX_H
#define CPP_LINAL_MATRIX_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>

/*
 * ---------------------------------------------------
 * Во-первых верни матешу в класс матрицы ирод
 * Нешаблонный класс матриц без возможности
 * Проводить над ним операции смысла не имеет
* ----------------------------------------------------
 * Во-вторых замени все дебажные функции (принт и т.д.)
 * На нормальные интуитивные перегрузки стл функций
* ----------------------------------------------------
 * В-третьих это только библиотека
 * Нет смысла сюда впихивать парсер и другие непонятные классы
 * Работающие с математическими выражениями
 * Напиши несколько библиотек которые можно будет объединить
 *
 * !!!Код должен быть модульным!!!
* ----------------------------------------------------
 * В-четвертых ты делаешь математически точную модель
 * Матриц и всей этой херни
 * Определения и всякие штуки ради оптимизации не пропускать
 * Выстрелишь себе в ногу
* ----------------------------------------------------
 * Да кстати надо обязательно сделать свой обработчик ошибок
 * Пока что текст никак не отличается от обычных собщений
 * Это стремно и плохой стиль
*/

#ifndef lines_
#define lines_   size_.first
#endif

#ifndef columns_
#define columns_ size_.second
#endif

#ifndef ll_t
#define ll_t
typedef long long ll;
#endif

namespace alinal {
        /**
         *  Class of (mostly) mathematically exact matrices and linear algebra.\n
         *  Also includes methods for solving System of Linear Algebraic Equations via
         *  Gaussian method and Cramer method.
        **/
    class matrix {
        ll **data_;
        std::pair<size_t, size_t> size_;

        /**
         *  Class only used for overloading [ ][ ] operator.
        **/
        struct sub_class {
            ll *data_;
            explicit sub_class(ll *arr)
                : data_(arr) {}
            ll &operator[](size_t idx) const { return data_[idx - 1]; }
        };

        void fill(ll n);
        void mul(ll n);
        void mul(matrix const &m);
        void add(matrix const &m);
        void subtract(matrix const &m);
    public:
        /*
         * ###########################################
         *         BLOCK OF UTILITY FUNCTIONS
         * ###########################################
        */

        /**
         * Constructor for matrix class.\n
         * Every element is 0 by default.
         * @param lines     - Number of rows in matrix.
         * @param columns   - Number of columns in matrix.
        **/
        explicit matrix(size_t lines, size_t columns);
        matrix(matrix const &m);
        ~matrix();

        /**
         * Swaps two matrices in memory.
         * @param other - Matrix to swap with.
        **/
        void swap(matrix &other);
        matrix &operator=(matrix const &other);
        sub_class operator[](size_t idx) const;
        /**
         * @return Number of rows and columns in this matrix.
        **/
        [[nodiscard]]
        std::pair<size_t, size_t> size() const;

        /**
         *  Prints matrix to std::cin.\n
         *  CONSIDER AVOIDING USING THIS METHOD.
        **/
        [[maybe_unused]] [[deprecated]]
        void print();

        /**
         *  Inputs matrix from std::cin.\n
         *  CONSIDER AVOIDING USING THIS METHOD.
        **/
        [[maybe_unused]] [[deprecated]]
        void input_matrix();

        /*
         * ##################################################
         *              BLOCK OF MATH FUNCTIONS
         * ##################################################
        */

        /**
         * Checks equality of the matrices.
         * @param right - Other matrix.
         * @return Are matrices equal.
        **/
        [[nodiscard]] bool equals(matrix const &right) const;

        /**
         * Returns equilateral matrix with every element equal to 0.\n
         * Method is static and is generally easier to read than having random matrix.
         * @param size - Size of your matrix.
         * @return Matrix of size x size elements that are all equal to 0.
        **/
        static matrix null_matrix(size_t size);

        /**
         * Returns equilateral matrix with every element equal to 0 except for main diagonal.\n
         * @param size - Size of your matrix.
         * @return Matrix of size size x size which is the identity matrix.
        **/
        static matrix identity_matrix(size_t size);

        /**
         * @return Transposed copy of this matrix.
        **/
        matrix transpose();

        /**
         * Gets minor in position of line and column.\n
         * This method might change in the future.
         * @param line      - Line which you want to erase.
         * @param column    - Column which you want to erase.
         * @return Copy of this matrix without line and column.
        **/
        matrix get_minor(size_t line, size_t column) const;

        /**
         * Recursively finds determinator for this matrix.
         * @return Determinator of this matrix.
         */
        ll find_det() const;

        /**
         * @return Max value in matrix.
        **/
        [[nodiscard]]
        ll max() const;

        /**
         * @return Min value in matrix.
         */
        [[nodiscard]]
        ll min() const;

        matrix &operator*=(ll n);
        matrix &operator*=(matrix const &m);

        matrix &operator+=(matrix const &m);
        matrix &operator-=(matrix const &m);

        matrix operator-();
        matrix operator+();

        /**
         * Prints formatted matrix in ostream.
         * @param out   - Output stream of yout choice.
         * @param right - Printed matrix.
         * @return Out for future use.
         */
        friend std::ostream &operator<<(std::ostream &out, alinal::matrix const &right);

        /**
         * Inputs matrix from istream.
         * @param in    - Input stream of yout choice.
         * @param right - Matrix for input.
         * @return In for future use.
         */
        friend std::istream &operator>>(std::istream &in, alinal::matrix const &right);

        friend std::vector<ll> cramer_method(alinal::matrix const &coefficient, alinal::matrix const &comp);
        friend std::vector<ll> gaussian_method(alinal::matrix coefficient, alinal::matrix comp);
    };
}

/*
 * #################################################
 *                 BINARY FUNCTIONS
 * #################################################
*/

alinal::matrix operator*(ll n, alinal::matrix m);
alinal::matrix operator*(alinal::matrix m, ll n);
alinal::matrix operator*(alinal::matrix m1, alinal::matrix const &m2);

alinal::matrix operator+(alinal::matrix left, alinal::matrix const &right);
alinal::matrix operator-(alinal::matrix left, alinal::matrix const &right);

bool operator==(alinal::matrix const &left, alinal::matrix const &right);

#endif //CPP_LINAL_MATRIX_H
