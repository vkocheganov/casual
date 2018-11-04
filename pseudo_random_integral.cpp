#include <random>
#include <chrono>
#include <vector>
#include <iostream>

using namespace std;

static mt19937 generator;

double calc_func(vector<double>& x)
{
    double sum{};
    for (auto& a:x)
        sum += a*a;
    return sum;
}

double calc_theoretical_integral(int p)
{
    return double(p)/3;
}

double make_experiment_rand(int N, int p)
{
    double sum{};
    vector<double> x(p);
    uniform_real_distribution<float> distribution(0., 1.);
    for (int i = 0; i < N; i++)
    {
        for (auto& a:x) a = distribution(generator);
        sum += calc_func(x);
    }
    return sum/N;
}


double make_experiment_determ(int n, int p)
{
    vector<int> dims(p,0);
    vector<int> idxs(p,0);
    vector<double> x(p);
    double delta = 1./n;
    for (auto& a:dims) a = n;
    double sum = 0;
    int count =0;
    
    while (1)
    {
        // Print
        for (int i = 0; i < p; i++)
        {
            x[i] = idxs[i] * delta;
        }
        sum += calc_func(x);

        // Update
        int j;
        for (j = 0; j < p; j++)
        {
            idxs[j]++;
            if (idxs[j] < dims[j]) break;
            idxs[j] = 0;
        }
        if (j == dims.size()) break;
        count++;
    }
    cout<<"count = "<<count<<endl;

    for (int i = 0; i < p; i++)
        sum /= n;
    return sum;
}


const int NN = 1000000;
const int n = 10;
const int PP = 4;
int main ()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);

    cout<<"hello, world!\n";
    int N = 1;
    for (int i = 0; i < PP; i++) N *= n;
    double exper = make_experiment_rand(N, PP);
    cout << exper <<"; error = "<<exper - calc_theoretical_integral(PP)<<endl;
    double exper_det = make_experiment_determ(n, PP);
    cout << exper_det <<"; error = "<<exper_det - calc_theoretical_integral(PP)<<endl;
    return 0;
}
