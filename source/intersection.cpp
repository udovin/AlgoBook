struct Pnt {
    int x, y;
    Pnt() {}
    Pnt(int _x, int _y): x(_x), y(_y) {}
    int operator*(const Pnt& p) {
        return x * p.x + y * p.y;
    }
    int operator%(const Pnt& p) {
        return x * p.y - y * p.x;
    }
    Pnt operator-(const Pnt& p) {
        return Pnt(x - p.x, y - p.y);
    }
};

int sign(int x) {
  if (x < 0)
    return -1;
  if (x > 0)
    return 1;
  return 0;
}

bool intersects(Pnt p11, Pnt p12, Pnt p21, Pnt p22) {
  if (
      sign((p11 - p12) % (p21 - p12)) * sign((p11 - p12) % (p22 - p12)) <= 0 &&
      sign((p22 - p21) % (p11 - p21)) * sign((p22 - p21) % (p12 - p21)) <= 0
      ) {
    return 1;
  }
  return 0;
}

std::pair<double, double> lineLineIntersection(Pnt A, Pnt B, Pnt C, Pnt D)
{
  // Line AB represented as a1x + b1y = c1
  double a1 = B.y - A.y;
  double b1 = A.x - B.x;
  double c1 = a1*(A.x) + b1*(A.x);

  // Line CD represented as a2x + b2y = c2
  double a2 = D.y - C.y;
  double b2 = C.x - D.x;
  double c2 = a2*(C.x)+ b2*(C.y);

  double determinant = a1*b2 - a2*b1;

  if (determinant == 0)
  {
    // The lines are parallel. This is simplified
    // by returning a pair of FLT_MAX
    return std::make_pair(1e18, 1e18);
  }
  else
  {
    double x = (double(b2*c1 - b1*c2))/determinant;
    double y = (double(a1*c2 - a2*c1))/determinant;
    return std::make_pair(x, y);
  }
}
