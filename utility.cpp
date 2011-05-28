#include "utility.h"

const double Utility::SMALL_DOUBLE_STEP = 1.0e-10;
const double Utility::DOUBLE_LARGE = 1000000000.0;
const int Utility::INT_LARGE = 20000;
const string Utility::className = "Utility";

double Utility::changePrecision(double number, int precision) {
    assert(precision >= 0);

    int d = precision;
    double n = number;

    return floor(n * pow(10., d) + .5) / pow(10., d);
}

/// Return string version of "true" or "false".
string Utility::boolToString(bool value) {
    if(value)
        return "true";
    else
        return "false";
}

bool Utility::stringToBool(string str) {
    assert(isBoolean(str));
    return toLower(str) == "true";
}

/// convert from integer to string optionally adding leading zeroes for number less than the minimum size of the string
/// to be returned
string Utility::intToString(long number, int minStringSize) {
    string result = "";
    if(number == 0) {
        for(int i=0; i<std::max(minStringSize, 1); i++)
            result.push_back('0');

        return result;
    }
    
    string negative = "";
    if(number < 0) {
        negative = "-";
        number *= -1;
    }
        
    long temp;
    string resultReverse = "";
    while(number != 0) {
        temp = number % 10;
        result.push_back((char)((long)'0' + temp));
        number /= 10;
    }
    
    int size = result.size();
    
    for(int i=size; i<minStringSize; i++)
        result.push_back('0');
    
    //reverse the string
    size = result.size();
    for(int i=1; i<=size; i++)
        resultReverse.push_back(result[size-i]);
    
    return negative + resultReverse;
}

string Utility::doubleToString(double x) {
    ostringstream oss;
    oss << x;
    
    return oss.str();
}

/// @brief Return the string representation of an integer, adding zeroes to its beginning such that the total length of
/// the string is no less than minStringSize.
///
/// If 'showSign' is true, then the sign on the number is also displayed. This extra sign character is not counted as
/// part of the 'minStringSize'.
///
string Utility::addZeros(long number, int minStringSize, bool showSign) {
    long temp;
    string result = "";
    string resultReverse = "";
    
    string sign = "";
    
    if(showSign) {
        if(number < 0)
            sign = "-";
        else
            sign = "+";
    }

    number = abs(number);
    
    while(number != 0) {
        temp = number % 10;
        result.push_back((char)((long)'0' + temp));
        number /= 10;
    }
    int size = result.size();
    
    for(int i=size; i<minStringSize; i++)
        result.push_back('0');
    
    //reverse the string
    size = result.size();
    for(int i=1; i<=size; i++)
        resultReverse.push_back(result[size-i]);
    
    return sign + resultReverse;
}


/// @brief Add a string in front of an integer. Optionally quotes are added around the output if 'inQuotes' is true.
///
string Utility::addLabelToInt(string label, int number, bool inQuotes) {
    string output;
    output = label + Utility::intToString(number);
    if(inQuotes)
        output = (string)("\"") + output + (string)("\"");
    return output;  
}

/// @brief Determine if the input character is a digit (0-9).
///
/// Note that passing an int type to this function is not a compile-time error, since its actually passing an ASCII
/// value of a character. '0' is 48 in ASCII. So for the int type the range which will return 'true' is [48,57]. Also,
/// note that multi-character char types are not accepted by this function, so if you pass it such a character, the
/// result is undefined, but will most likely return false.
///
bool Utility::isDigit(char c) {
    int number = ((int)c - (int)'0');
    return (number >= 0) && (number <= 9);
}

/// Determine if the input string is either "true" or "false"
///
bool Utility::isBoolean(string const & s) {
    return (toLower(s) == "true" || toLower(s) == "false");
}

/// @brief Seperate the 'input' string into tokens delimitted by the same characters as is used by iostream (spaces,
/// tabs, etc.)
///
/// @param input Input string that is to be tokenized
/// @param tokens Output 
///
/// Note that the term 'tokenize' is commonly used (especially in the world of Java) in reference to breaking strings
/// into pieces based on a set of delimiters.
///
void Utility::tokenize(string const & input, vector<string> & tokens) {
    /// form a string stream from the input string
    istringstream sin(input);

    tokens.clear();
    string piece;
    while(sin >> piece)
        tokens.push_back(piece);
}

/// @brief Extract the first non-interrupted sequence of [0-9] from the string 'str'. Negative numbers (designated by a
/// minus preceding the number) are not detected. If no number is found in the string, -1 is returned.
///
/// For example, input "test123test456" provides output 123. Input "test-123test456" provides output 123.
///
int Utility::getIntFromLabel(string str) {
    int i, j;
    string number = "";
    for(i=0; i<(int)str.size(); i++)
        if(isDigit(str[i])) break;
    
    if(i == (int)str.size()) /// no number were found in the string
        return -1;

    for(j=i; j<(int)str.size(); j++) {
        if(!isDigit(str[j])) break;
        number += str[j];
    }

    return atoi(number.c_str());
}

/// \brief Remove the extension from a file name, and return the file name without the extension. File name that begin
/// with ".", such as ".." or ".bash_profile" will return an empty string.
/// 
/// \param filename File name (that may or may not include the file's path) with the extension at the end
/// 
/// \return 'filename' without the '.' or the extension
///
string Utility::removeExtension(string filename) {
    string result = "";
    for(int i=0; i<(int)filename.size(); i++)
        if(filename[i] != '.')
            result.push_back(filename[i]);
        else
            break;
    
    return result;
}

string Utility::removePath(string filename) {
    string result = "";
    for(int i=filename.size()-1; i>=0; i--)
        if(filename[i] != '/')
            result.push_back(filename[i]);
        else
            break;
    
    return reverse(result);
}

/// @brief Return the extension of a filename (the part after the '.' character). If a file has no extension, an empty
/// string is returned
string Utility::extension(string filename) {
    string result = "";
    bool found = false;
    for(int i=filename.size()-1; i>=0; i--)
        if(filename[i] != '.')
            result.push_back(filename[i]);
        else {
            found = true;
            break;
        }
    
    if(!found)
        return "";    
    
    return reverse(result);
}

string Utility::reverse(string x) {
    stack<char> s;
    const int n = x.length();
  
    //Put characters from x onto the stack
    for(int i=0; i<n; ++i)
        s.push(x[i]);
  
    //take characters off of stack and put them back into x
    for(int i=0; !s.empty(); ++i, s.pop())
        x[i]=s.top();
  
    return x;
}

/// \brief Find the first appearance of a pattern in a string and replace it with another pattern
/// 
/// \param original Input string that is being searched
/// \param targetPattern The character pattern that is being searched for.
/// \param replacePattern The string that will replace the character pattern
/// \return The string that results from the replacement
string Utility::replace(string original, string targetPattern, string replacePattern) {
    int counter = 0;
    int position;

    while(true) {
        if(counter > 10000) assert(false);

        position = original.find(targetPattern, 0);

        if(position == (int)string::npos)
            break;

        original.replace(position, targetPattern.size(), replacePattern);
        
        counter++;
    }

    return original;
}

/// \brief Replace the spaces in a string with another character that is more Unix friendly
/// 
/// \param str Input string that is being searched
/// \param replacementChar Character with which to replace the space
/// \return The processed string without any spaces, and with replaceChar instead of the spaces
string Utility::replaceSpaces(string str, char replaceChar) {
    for(int i=0; i<(int)str.size(); i++)
        if(str[i] == ' ') str[i] = replaceChar;
    return str;
}

/// @brief Determine if 'x' is odd. Negative numbers ARE allowed.
///
bool Utility::odd(int x) {
    x = abs(x);
    return (x % 2) == 1;
}

/// @brief Determine if 'x' is even. Negative numbers ARE allowed.
///
bool Utility::even(int x) {
    return !odd(x);
}

/// \brief Find the mean of a vector of values
/// \param v a pointer to a non-empty STL vector
/// \return the value of the vector mean
double Utility::mean(vector<double> const & v) {
    assert(v.size() > 0);

    double total = 0.0;
    for(int i=0; i<(int)v.size(); i++)
        total += v[i];
    return total / (double)v.size();
}

/// @brief Find the sum of all the floating point numbers in the input array
double Utility::sum(vector<double> const & v) {
    double total = 0;
    for(int i=0; i<(int)v.size(); i++) 
        total += v[i];
    return total;
}

/// @brief Normalize each number in the vector such that the total sum of the vector equals to 'weight'
///
/// @param v Input array of numbers to be normalized. The output is written over this array.
/// @param weight The sum of all the elements of the resultant normalized array.
///
void Utility::normalize(vector<double> & v, double weight) {
    double total = sum(v);
    for(int i=0; i<(int)v.size(); i++)
        v[i] = v[i] / total * weight;
}

/// \brief Find the variance of a vector of values
/// \param v a pointer to a non-empty STL vector
/// \return the value of the vector variance (not vector standard deviation)
double Utility::variance(vector<double> const & v) {
    double m = mean(v);
    double variance = 0;
    
    for(int i=0; i<(int)v.size(); i++) 
        variance += pow(v[i]-m , 2.0);

    double result = variance / (double)v.size();
    
    return result;
}

/// @brief Find the standard deviation of a vector of values
///
/// @param v a pointer to a non-empty STL vector
/// @return the value of the vector standard deviation
///
/// This function simply finds the variance of the vector using the variance(...) function and return the square root of
/// that result.
///
double Utility::standardDeviation(vector<double> const & v) {
    assert(v.size() > 0);
    double result = sqrt(variance(v));
    return result;
}

/// \brief Find the largest value in a data set
///
/// \param v Pointer to a vector of unordered double values which is to be traversed
/// \return The largest value in the vector v
double Utility::max(vector<double> const & v) {
    assert(v.size() > 0);
    double val = v[0];
    for(int i=0; i<(int)v.size(); i++)
        if(v[i] > val)
            val = v[i];
    
    return val;
}

/// \brief Find the smallest value in a data set
///
/// \param v Pointer to a vector of unordered double values which is to be traversed
/// \return The smallest value in the vector v
double Utility::min(vector<double> const & v) {
    assert(v.size() > 0);
    double val = v[0];
    for(int i=0; i<(int)v.size(); i++)
        if(v[i] < val)
            val = v[i];
    
    return val;
}

/// \brief Compute the mod (%) operator for a decimal dividend (as opposed to an integer)
/// 
/// \param x The decimal dividend
/// \param y The integer divisor
/// \return The real number remainder from the division operation
double Utility::modulos(double x, int y) {
    assert(y > 0);
    double sign = x < 0.0 ? -1.0 : 1.0;
    x = fabs(x);
    double r = x - (double)(int)x;
    x = (double)((int)x % y);
    return sign * (x + r);
}

/// \brief Compute the mod (%) operator for a decimal dividend and divisor
/// 
/// \param x The decimal dividend
/// \param y The decimal divisor
/// \return The real number remainder from the division operation
double Utility::modulos(double x, double y) {
    assert(y > 0);
    double sign = x < 0.0 ? -1.0 : 1.0;
    x = fabs(x);
    return sign * (x - floor(x / y) * y);
}

/// \brief Change the input angle so that it's between 0 and 360 degrees: [0,360)
///
/// \param angle The angle (in degrees) to be fixed
void Utility::fixDegrees(double & angle) {
    angle = modulos((modulos(angle,360)+360.0),360);
}

/// \brief Change the input angle so that it's between 0 and 2pi radians: [0,2pi)
///
/// \param angle The angle (in radians) to be fixed
void Utility::fixRadians(double & angle) {
    angle = modulos((modulos(angle,2.0*M_PI)+2.0*M_PI),2*M_PI);
}

double Utility::degreesToRadians(double angle) {
    return angle / 180.0 * M_PI;
}

double Utility::radiansToDegrees(double angle) {
    return angle * 180.0 / M_PI;
}

double Utility::max(double a, double b) {
    return (a<b)? b : a;
}

int Utility::max(int a, int b) {
    return (a<b)? b : a;
}

double Utility::min(double a, double b) {
    return (a<b)? a : b;
}

int Utility::min(int a, int b) {
    return (a<b)? a : b;
}

/// Check if two double values are very close.
///
/// Reference: http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
bool Utility::equal(double A, double B, double maxRelativeError, double maxAbsoluteError) {
    if(A == B)
        return true;

    if(fabs(A - B) < maxAbsoluteError)
        return true;

    double relativeError;
    
    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);

    if(relativeError <= maxRelativeError)
        return true;

    return false;
}

bool Utility::greater(double a, double b) {
    return a > b && !equal(a,b);
}

bool Utility::greaterEqual(double a, double b) {
    if(equal(a,b)) return true;

    return a > b;
}

bool Utility::less(double a, double b) {
    return a < b && !equal(a,b);
}

bool Utility::lessEqual(double a, double b) {
    if(equal(a,b)) return true;

    return a < b;
}


// standard normal density function
double Utility::normalDensityFunction(double t) {
    return 0.398942280401433*exp(-t*t/2);
}

double Utility::gaussianQFunction(double u) {
    return (double)1 - normalCumulativeFunction(u);
}

// standard normal cumulative distribution function
double Utility::normalCumulativeFunction(double u) {
    const double a[5] = {
        1.161110663653770e-002,3.951404679838207e-001,2.846603853776254e+001,
        1.887426188426510e+002,3.209377589138469e+003
    };
    const double b[5] = {
        1.767766952966369e-001,8.344316438579620e+000,1.725514762600375e+002,
        1.813893686502485e+003,8.044716608901563e+003
    };
    const double c[9] = {
        2.15311535474403846e-8,5.64188496988670089e-1,8.88314979438837594e00,
        6.61191906371416295e01,2.98635138197400131e02,8.81952221241769090e02,
        1.71204761263407058e03,2.05107837782607147e03,1.23033935479799725E03
    };
    const double d[9] = {
        1.00000000000000000e00,1.57449261107098347e01,1.17693950891312499e02,
        5.37181101862009858e02,1.62138957456669019e03,3.29079923573345963e03,
        4.36261909014324716e03,3.43936767414372164e03,1.23033935480374942e03
    };
    const double p[6] = {
        1.63153871373020978e-2,3.05326634961232344e-1,3.60344899949804439e-1,1.25781726111229246e-1,1.60837851487422766e-2,6.58749161529837803e-4
    };
    const double q[6] = {
        1.00000000000000000e00,2.56852019228982242e00,1.87295284992346047e00,5.27905102951428412e-1,6.05183413124413191e-2,2.33520497626869185e-3
    };
    register double y, z;
    
    y = fabs(u);
    if (y <= 0.46875*M_SQRT2) {
        /* evaluate erf() for |u| <= sqrt(2)*0.46875 */
        z = y*y;
        y = u*((((a[0]*z+a[1])*z+a[2])*z+a[3])*z+a[4]) / ((((b[0]*z+b[1])*z+b[2])*z+b[3])*z+b[4]);
        return 0.5+y;
    }
    z = exp(-y*y/2)/2;
    if (y <= 4.0) {
        /* evaluate erfc() for sqrt(2)*0.46875 <= |u| <= sqrt(2)*4.0 */
        y = y/M_SQRT2;
        y =
            ((((((((c[0]*y+c[1])*y+c[2])*y+c[3])*y+c[4])*y+c[5])*y+c[6])*y+c[7])*y+c[8]) / ((((((((d[0]*y+d[1])*y+d[2])*y+d[3])*y+d[4])*y+d[5])*y+d[6])*y+d[7])*y+d[8]);
        
        y = z*y;
    } else {
        /* evaluate erfc() for |u| > sqrt(2)*4.0 */
        z = z*M_SQRT2/y;
        y = 2/(y*y);
        y = y*(((((p[0]*y+p[1])*y+p[2])*y+p[3])*y+p[4])*y+p[5]) / (((((q[0]*y+q[1])*y+q[2])*y+q[3])*y+q[4])*y+q[5]);
        y = z*(M_1_SQRTPI-y);
    }
    
    return (u < 0.0 ? y : 1-y);
}

/// @brief Take the input string and reduce its length to 'width' by taking the first width-1 characters of the string
/// and appending a '~', that is if the input string is longer than 'width'. If 'str' is shorter than 'width', then
/// spaces are appended to the end to make it exactly 'width' long.
///
/// If width is zero, an empty string is returned.
///
string Utility::forceWidth(string const & str, int width) {
    assert(width >= 0);

    if(width == 0)
        return "";

    string output = str;

    if((int)output.size() > width) {
        output = output.substr(0, width);
        output[output.size()-1] = '~';
        return output;
    }

    for(int i=(int)output.size()+1; i<=width; i++)
        output.push_back(' ');

    return output;
}

int Utility::minDisplayWidth(vector<int> const & v) {
    int largest = 0;
    for(int i=0; i<(int)v.size(); i++) {
        int size = (int)(intToString(v[i])).size();
        if(size > largest)
            largest = size;
    }

    return largest;
}

/// @brief Iterate through the file stream 'fin' until the string 'target' is found, at which point the functions
/// returns true. If no such string is ever found, then the function returns false.
///
/// If you pass an empty string as 'target', the behavior is undefined, however, usually the function will simply return
/// false.
///
bool Utility::gotoString(std::ifstream & fin, string target) {
    string current;
    while(true) {
        fin >> current;
        if(fin.eof()) return false;
        if(current == target) return true;
    }
    return false;
}

/// @brief Find the two roots of the quadratic equation defined by the three parameters 'a', 'b', and 'c'
///
bool Utility::solveQuadraticEquation(double a, double b, double c, double & firstRoot, double & secondRoot) {
    double discriminant = (b * b) - (4 * a * c);

    if(discriminant < 0) {
        cerr << "OMAN ERROR: Quadratic equation provided to the solver does not have any real roots. ";
        cerr << "This case is not accounted for." << endl;
        return false;
    }

    double arg_sqrt = sqrt(discriminant);
            
    firstRoot = (-b/(2 * a)) + (arg_sqrt/(2 * a));
    secondRoot = (-b/(2 * a)) - (arg_sqrt/(2 * a));

    return true;
}

/// Select 'subsetSize' unique integers from 0 to 'fullsetSize'-1 and write them to the 'subset' vector.
///
void Utility::sampleIndecies(int fullsetSize, int subsetSize, vector<int> & subset) {
    assert(subsetSize <= fullsetSize);
    vector<int> fullset(fullsetSize);

    for(int i=0; i<fullsetSize; i++)
        fullset[i] = i;    

    sample(fullset, subsetSize, subset);
}

/// @brief Randomly shuffle the values in an STL vector of 'size' consecutive integers (starting from 0).
void Utility::shuffle(int size, vector<int> & array) {
    array.resize(size);
    for(int i=0; i<size; i++)
        array[i] = i;
    Utility::shuffle(array);
}

/// @brief Sample 'subsetSize' unique values from a vector of 'fullsetSize' consecutive integers (starting with zero)
/// and write the results in the 'subset' vector.
void Utility::sample(int fullsetSize, int subsetSize, vector<int> & subset) {
    vector<int> fullset(fullsetSize);
    for(int i=0; i<fullsetSize; i++)
        fullset[i] = i;
    Utility::sample(fullset, subsetSize, subset);
}

/// @brief Convert a string to be all lower case and return the new lower case string
string Utility::toLower(const string & s) {
	string returnVal;
	///resize our return string to the same size of our input string
	returnVal.resize(s.size());
	
	///loop over each character in the original string and convert it to lower case
	for(size_t q = 0; q < s.size(); q++) {
		returnVal[q] = tolower(s[q]);
	}
	
	return returnVal;
}

/// Element-wise division, requiring 'a' and 'b' of the same size.
///
void Utility::divide(vector<double> const & a, vector<double> const & b, vector<double> & result) {
    assert(a.size() == b.size());

    result.resize(a.size());
    
    for(int i=0; i<(int)result.size(); i++)
        result[i] = a[i] / b[i];
}

void Utility::wait(double seconds) {
    clock_t endwait;
    endwait = clock() + (int)((double)seconds * (double)CLOCKS_PER_SEC);
    while (clock() < endwait) {}
}
