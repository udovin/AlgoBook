double F(const function<double(double)>& f, double l, double r) {
    return (r - l) / 6 * (f(l) + f(r) + 4 * f((l + r) / 2));
}

double I(const function<double(double)>& f, double l, double r) {
    double m = (l + r) / 2;
    double a = F(f, l, r);
    double b = F(f, l, m) + F(f, m, r);
    if (abs(a - b) < EPS) {
        return b;
    }
    return I(f, l, m) + I(f, m, r);
}
