// Martins P 473
// Week 3 Homework 2
//
// For an additional challenge and complete mathematical reasoning of the output, 
// I used an advanced root-finding algorithm to complete this homework.
// The situation can be modeled similarly as an increase due to compound interest (perc) and additions (delta) on
// the principle (p0) value in mathematical finance.
//
// This page http://www.moneychimp.com/articles/finworks/fmbasinv.htm describes how to calculate total accumulated value:
//     p(years) = p0 * (1 + perc)^years + delta/perc * ((1 + perc)^years - 1)
//
// Then p(years) - p[desired] would represent a function, which has the root of the number of years to reach p[desired].
//
// Since root finding is non-trivial here, Newton's method is used (https://en.wikipedia.org/wiki/Newton%27s_method)
// It states that each next x (years in our case) is a better approximation than the previous x in:
//     x_n+1 = x_n - p(x_n) / p'(x_n)
//
// By differentiating p(years):
//     p'(x_n) = (1 + perc)^years * (p0 * perc + delta) * ln(perc + 1) / perc
//
// After some iterations, x_n becomes very precise, describing the years until the population is reached.
// Since p'(x_n) describes the rate of population change, if it is close to zero, then it is not possible to reach 
// the desired population.
//
// This way in just a few iterations, the number of years or the impossibility to reach the population can be determined.
//
#include <iostream>
#include <cmath>
using namespace std;


const float EPSILON = 0.005;

bool areFloatsEqual(float n1, float n2) {
    return abs(n1 - n2) < EPSILON;
}

// Population for the given year
double population(double years, int p0, float perc, int delta) {
    return p0 * pow(1 + perc, years) + delta/perc * (pow(1 + perc, years) - 1);
}

// Derriviative of the population function for the given year
double dPopulation(double years, int p0, float perc, int delta) {
    return pow(1 + perc, years) * (p0 * perc + delta) * log(perc + 1) / perc;
}

int getCityYear(int p0, double perc, int delta, int p) {
    const int CIRCUIT_BREAKER = 20; // This should not be necessary, but better be safe than sorry
    perc = perc / 100; // All further computation deals with percents < 1

    double years = 1; // First guess of the number of years
    int i = 0;

    while (true) {
        float populationFnR = population(years, p0, perc, delta) - p;
        float dPopulationFnR = dPopulation(years, p0, perc, delta);

        if (areFloatsEqual(0, dPopulationFnR) || i > CIRCUIT_BREAKER)
            break;

        // Newton's method gets more close root (number of years)
        years = years - populationFnR / dPopulationFnR;

        if (areFloatsEqual(0, populationFnR))
            return ceil(years);

        i++;
    }

    return -1;
}

int main() {
    printf("%d\n", getCityYear(1000, 2, 50, 1200)); // 3
    printf("%d\n", getCityYear(1000, 2, -50, 5000)); // -1
    printf("%d\n", getCityYear(1500, 5, 100, 5000)); // 15
    printf("%d\n", getCityYear(1500000, 2.5, 10000, 2000000));
    printf("%d\n", getCityYear(1000, -3, 50, 2000));

    return 0;
}
