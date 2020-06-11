#include <cfloat>
#include <climits>
#include <cmath>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

class EvaluationUtilities {
 public:
  static std::vector<int> normalize(std::vector<int>& y, int newMaxX) {
    std::vector<int> y_new;
    y_new.reserve(y.size());
    int maxX = std::accumulate(y.begin(), y.end(), 0) - y[0];
    for (unsigned int i = 0; i < y.size(); ++i)
      y_new.push_back(round((float)(newMaxX * y[i]) / maxX));
    return y_new;
  }

  static std::vector<int> diff(std::vector<int>& x) {
    if (x.size() < 2) return {};
    std::vector<int> x_new;
    x_new.reserve(x.size() - 1);
    for (unsigned int i = 1; i < x.size(); ++i) {
      x_new.push_back(x[i] - x[i - 1]);
    }
    return x_new;
  }

  static std::vector<int> interp1(std::vector<int>& y, const int step,
                                  const int maxX) {
    if (y.size() < 1) return {};
    std::vector<int> y_new;
    y_new.reserve(maxX / step);

    int x = 0, resample_x = 0;
    for (int i = 0; i + 1 < y.size(); ++i) {
      int x_new = x + y[i + 1];
      int dx = x_new - x;
      int dy = y[i + 1] - y[i];
      float slope = (float)dy / (float)dx;
      float intercept = (float)y[i] - (float)x * slope;
      while (resample_x < x_new) {
        y_new.push_back(slope * resample_x + intercept);
        resample_x += step;
      }
      x = x_new;
    }
    return y_new;
  }

  static float meanSquaredError(std::vector<int>& a, std::vector<int>& b) {
    float ret = 0.0;
    for (unsigned int i = 0; i < a.size(); ++i) {
      int iSqDiff = (a[i] - b[i]) * (a[i] - b[i]);
      ret += iSqDiff / (a.size() - 1);
    }
    if (ret < 0) {
      std::cout << "negative ret: " << ret << " (size " << a.size() << ")"
                << std::endl;
    }
    return ret;
  }

  static float meanAbsoluteError(std::vector<int>& a, std::vector<int>& b) {
    float ret = 0.0;
    for (unsigned int i = 0; i < a.size(); ++i) {
      int iDiff = a[i] - b[i];
      ret += fabs(iDiff);
    }
    ret = ret / (a.size() - 1);
    return ret;
  }
};