#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;


class Neuron
{
public:

    int n;
    double* w;
    double* x;
    double (*function)(double);

    Neuron(int entersNum, double (*function)(double))
    {
        n = entersNum;
        w = new double[n];
        x = new double[n];
        this->function = function;
    }

    void setX(int i, double value)
    {
        x[i] = value;
    }

    void setW(int i, double value)
    {
        w[i] = value;
    }

    double getY() 
    {
        double h = 0;
        for (int i = 0; i < n; i++)
        {
            h += w[i] * x[i];
        }
        return function(h);
    }

    Neuron(const Neuron& source)
    {
        this->n = source.n;
        this->w = new double[n];
        this->x = new double[n];
        this->function = source.function;
        for (int i = 0; i < n; i++)
        {
            this->w[i] = source.w[i];
            this->x[i] = source.x[i];
        }
    }

    Neuron& operator=(const Neuron& source)
    {
        delete[] this->w;
        delete[] this->x;
        this->n = source.n;
        this->w = new double[n];
        this->x = new double[n];
        this->function = source.function;
        for (int i = 0; i < n; i++)
        {
            this->w[i] = source.w[i];
            this->x[i] = source.x[i];
        }
        return *this;
    }

    
    ~Neuron()
    {
        delete[] w;
        delete[] x;
    }

};

double useFunction(double h)
{
    return 1.0 / (1 + exp(-h));
}

int main()
{
    int n = 3;
    int z = 4;
    Neuron first = Neuron(n, useFunction);

    double c;
    for (double i = 0; i < n; i++)
        first.setX(i, 1.0 / (i + 1));

    cout << endl;
    for (int j = 0; j < n; j++)
        first.setW(j, j);

    Neuron second(z, useFunction);
    second = first;

    cout << first.getY() << endl;
    cout << second.getY() << endl;

    return 0;
}
