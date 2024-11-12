#include <limits>
#include <cmath>

namespace MCR
{

struct Compare {

static bool equalFloat (float a, float b, float epsilon = std::numeric_limits<float>::epsilon())
{
    return std::abs (a - b) < epsilon;
}

static bool equalDouble (double a, double b, double epsilon = std::numeric_limits<float>::epsilon())
{
    return std::abs (a - b) < epsilon;
}

};

}