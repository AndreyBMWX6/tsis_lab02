#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <sstream>
#include "TextTable.h"

double get_fucn_val(double x) {
    return ((1 - x) * (1 - x) + exp(x));
}

double get_multi_fucn_val(double x) {
    return get_fucn_val(x) * sin(5 * x);
}

std::string get_spec_str(double x) {
    std::stringstream s;
    std::string str;
    s.precision(4);
    s << x;
    s >> str;
    return str;
}

std::string get_str(double x) {
    std::stringstream s;
    std::string str;
    s << std::fixed;
    s.precision(4);
    s << x;
    s >> str;
    return str;
}

void get_dependence_matrix(double a, double b, std::vector<double> p, std::vector<double> q) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(a, b);
    TextTable N_dependence_matrix('-', '|', '+');
    TextTable uni_func_min_matrix('-', '|', '+');
    TextTable multi_func_min_matrix('-', '|', '+');
    for (int i = 0; i < q.size() + 1; ++i) {
        for (int j = 0; j < p.size() + 1; ++j) {
            if (i == 0 && j == 0) {
                N_dependence_matrix.add("q/P");
                uni_func_min_matrix.add("q/P");
                multi_func_min_matrix.add("q/P");
                continue;
            } else if (i == 0) {
                N_dependence_matrix.add(get_spec_str(p[j - 1]));
                uni_func_min_matrix.add(get_spec_str(p[j - 1]));
                multi_func_min_matrix.add(get_spec_str(p[j - 1]));
            } else if (j == 0) {
                N_dependence_matrix.add(get_spec_str(q[i - 1]));
                uni_func_min_matrix.add(get_spec_str(q[i - 1]));
                multi_func_min_matrix.add(get_spec_str(q[i - 1]));
            } else {
                double N = ceil((log(1 - p[j - 1])) / log(1 - q[i - 1]));
                N_dependence_matrix.add(std::to_string(int(N)));
                double f_min = get_fucn_val(a);
                double f_cur;
                for (int iter = 0; iter < N; ++iter) {
                    double x = dis(gen);
                    f_cur = get_fucn_val(x);
                    if (f_cur < f_min) {
                        f_min = f_cur;
                    }
                }
                uni_func_min_matrix.add(get_str(f_min));

                f_min = get_multi_fucn_val(dis(gen));
                for (int it = 0; it < N; ++it) {
                    double x = dis(gen);
                    f_cur = get_multi_fucn_val(x);
                    if (f_cur < f_min) {
                        f_min = f_cur;
                    }
                }
                multi_func_min_matrix.add(get_str(f_min));
            }
        }
        N_dependence_matrix.endOfRow();
        uni_func_min_matrix.endOfRow();
        multi_func_min_matrix.endOfRow();
    }
    std::cout << N_dependence_matrix << "\n" << uni_func_min_matrix << "\n" << multi_func_min_matrix;
}

int main() {
    std::vector<double> p, q;
    for (int i = 0; i < 10; ++i) {
        p.push_back(0.9 + 0.01 * i);
    }
    for (int i = 0; i < 20; ++i) {
        q.push_back(0.005 * (i + 1));
    }
    get_dependence_matrix(-4, 3, p, q);
    return 0;
}
