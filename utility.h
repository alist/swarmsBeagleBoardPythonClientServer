#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <algorithm>
#include <ext/algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <limits>
using namespace std;
using namespace __gnu_cxx;

#include "stdlib.h"
#include <math.h>
#include <float.h>
#include <assert.h>
#include <time.h>


#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

/* #define M_E         2.71828182845904523536 */
/* #define M_LOG2E     1.44269504088896340736 */
/* #define M_LOG10E    0.434294481903251827651 */
/* #define M_IVLN10    0.434294481903251827651 /\* 1 / log(10) *\/ */
/* #define M_LN2       0.693147180559945309417 */
/* #define M_LOG2_E    0.693147180559945309417 */
/* #define M_LN10      2.30258509299404568402 */
#ifndef M_PI
#define M_PI        3.141592653589793238462643383280
#endif
/* #define M_TWOPI     (M_PI * 2.0) */
/* #define M_PI_2      1.57079632679489661923 */
/* #define M_PI_4      0.785398163397448309616 */
/* #define M_3PI_4     2.3561944901923448370E0 */
/* #define M_SQRTPI    1.77245385090551602792981 */
/* #define M_1_PI      0.318309886183790671538 */
/* #define M_2_PI      0.636619772367581343076 */
#ifndef M_1_SQRTPI
#define M_1_SQRTPI  0.564189583547756286948
#endif
// #define M_2_SQRTPI  1.12837916709551257390
#ifndef M_SQRT2
#define M_SQRT2     1.41421356237309504880
#endif
/* #define M_SQRT_2    0.7071067811865475244008443621048490392848359376887 */
/* #define M_SQRT1_2   0.7071067811865475244008443621048490392848359376887 */
/* #define M_LN2LO     1.9082149292705877000E-10 */
/* #define M_LN2HI     6.9314718036912381649E-1 */
/* #define M_SQRT3     1.73205080756887719000 */
/* #define M_INVLN2    1.4426950408889633870E0 */

/// \class Utility
/// \brief Static helper functions, random number generating methods, and anything else that works with STL structures
/// 
/// Brings together functions that perform the helping tasks like finding the mean of a set of numbers, generating
/// random numbers, coverting numbers to strings, etc. Any methods that could potentially be needed throughout the code
/// should be placed in here. These methods SHOULD NOT operate on any of the fundamental structures of the simulator
/// like the Graph or Network structures.
class Utility {
 public:
    static const double SMALL_DOUBLE_STEP;
    static const double DOUBLE_LARGE;
    static const int INT_LARGE;

    // string manipulation
    static string addZeros(long number, int minStringSize = 0, bool showSign = false);
    static string intToString(long number, int minStringSize = 0);
    static string boolToString(bool value);
    static string doubleToString(double x);
    static bool stringToBool(string str);
    static string addLabelToInt(string label, int number, bool inQuotes = false);
    static int getIntFromLabel(string str);
    static bool isDigit(char c);
    static bool isBoolean(string const & s);
    static string removeExtension(string filename);
    static string removePath(string filename);
    static string extension(string filename);
    static string reverse(string x);
    static string replace(string original, string targetPattern, string replacePattern);
    static string replaceSpaces(string str, char replaceChar = '-');
    static string forceWidth(string const & str, int width);
    static int minDisplayWidth(vector<int> const & v);
    static bool gotoString(std::ifstream & fin, string target);
    static void tokenize(string const & input, vector<string> & tokens);
    static string toLower(string const & s);

    // statistics
    static double normalDensityFunction(double t);
    static double normalCumulativeFunction(double u);
    static double gaussianQFunction(double u);

    // stl helpers
    template <typename TYPE> static void remove(vector<TYPE> & array, int i);
    static void sample(int fullsetSize, int subsetSize, vector<int> & subset);
    template <typename TYPE> static void sample(vector<TYPE> const & fullset, int subsetSize, vector<TYPE> & subset);
    template <typename TYPE> static void sample(vector<TYPE> & array, int subsetSize);
    template <typename TYPE> static void shuffle(vector<TYPE> & array);
    static void shuffle(int size, vector<int> & array);
    static void sampleIndecies(int fullsetSize, int subsetSize, vector<int> & subset);
    
    // calculators
    static bool odd(int x);
    static bool even(int x);
    static double mean(vector<double> const & v);
    static double variance(vector<double> const & v);
    static double standardDeviation(vector<double> const & v);
    static double max(vector<double> const & v);
    static double min(vector<double> const & v);
    template <typename TYPE> static int argmax(vector<TYPE> const & v);
    template <typename TYPE> static int argmin(vector<TYPE> const & v);
    static double sum(vector<double> const & v);
    static void normalize(vector<double> & v, double weight = 1.0);
    static double max(double a, double b);
    static int max(int a, int b);
    static double min(double a, double b);
    static int min(int a, int b);
    static double modulos(double x, int y);
    static double modulos(double x, double y);
    static void fixDegrees(double & angle);
    static void fixRadians(double & angle);
    static double degreesToRadians(double angle);
    static double radiansToDegrees(double angle);
    static inline bool equal(double A, double B)
        { return equal(A, B, 1.0e-10, std::numeric_limits<double>::epsilon()); }
    static bool equal(double A, double B, double maxRelativeError, double maxAbsoluteError);
    static inline bool zero(double value)
        { return equal(value, 0); }
    static bool greater(double a, double b);
    static bool greaterEqual(double a, double b);
    static bool less(double a, double b);
    static bool lessEqual(double a, double b);
    static bool solveQuadraticEquation(double a, double b, double c, double & firstRoot, double & secondRoot);
    static double changePrecision(double number, int precision);
    static void divide(vector<double> const & a, vector<double> const & b, vector<double> & result);

    static void wait(double seconds);
        
 private:
    static const string className;
};

/// @brief Remove a single elements from a templated STL vector in O(1) time
template <typename TYPE>
void Utility::remove(vector<TYPE> & array, int i) {
    assert(i < array.size());

    if(i < array.size() - 1)
        array[i] = array[array.size() - 1];

    array.resize(array.size() - 1);
        
}

/// @brief Sample 'subsetSize' unique values from a vector 'fullset' and write the results in the 'subset' vector.
template <typename TYPE>
void Utility::sample(vector<TYPE> const & fullset, int subsetSize, vector<TYPE> & subset) {
    subset.resize(subsetSize);
    
    if(subsetSize == 0) return;

    random_sample(fullset.begin(), fullset.end(), subset.begin(), subset.end());
}

/// @brief Sample 'subsetSize' unique values from a vector 'array' and overwrite 'array" with the resulting subset.
template <typename TYPE>
void Utility::sample(vector<TYPE> & array, int subsetSize) {
    vector<TYPE> array_copy = array;

    sample(array_copy, subsetSize, array);
}

/// @brief Randomly shuffle the values in an STL vector.
template <typename TYPE>
void Utility::shuffle(vector<TYPE> & array) {
    if(array.size() <= 1)
        return;
        
    std::random_shuffle(array.begin(), array.end());
}

/// Return the index of the input vector containing the minimum value. If there are multiple elements of the same
/// minimum value, then the first one is returned
///
template <typename TYPE>
int Utility::argmin(vector<TYPE> const & v) {
    assert(v.size() > 0);

    TYPE val = v[0];
    int pos = 0;
    for(int i=1; i<v.size(); i++)
        if(v[i] < val) {
            val = v[i];
            pos = i;
        }
    
    return pos;
}

/// Return the index of the input vector containing the maximum value. If there are multiple elements of the same
/// maximum value, then the first one is returned
///
template <typename TYPE>
int Utility::argmax(vector<TYPE> const & v) {
    assert(v.size() > 0);

    TYPE val = v[0];
    int pos = 0;
    for(int i=1; i<v.size(); i++)
        if(v[i] > val) {
            val = v[i];
            pos = i;
        }
    
    return pos;
}


#endif
