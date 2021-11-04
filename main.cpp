#include <iostream>
#include "matrix.h"

using namespace alinal;
using std::cin;
using std::cout;

int main() {
    cout << "Enter size of your slae:";
    size_t size; cin >> size;
    matrix slae(size, size), comp(size, 1);
    cout << "Enter your slae:\n";
    cin >> slae;
    cout << "Enter your answers:\n";
    cin >> comp;
    auto ans = gaussian_method(slae, comp);
    cout << "Gaussian method: { ";
    for(size_t i = 0; i < ans.size(); i++) cout << "x" << i + 1 << " = " << ans[i] << "; ";
    cout << "}\n";
    ans = cramer_method(slae, comp);
    cout << "Cramer method: { ";
    for(size_t i = 0; i < ans.size(); i++) cout << "x" << i + 1 << " = " << ans[i] << "; ";
    cout << "}";
}