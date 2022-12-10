#include <iostream>
#include <array>
#include <cmath>

namespace utility
{
    constexpr static auto T{0.000001}; // small time step
    constexpr static auto PI{3.14159265359};
} // namespace utility

class SmoothDerivative
{
private:
    double y;
    double u;
public:
    SmoothDerivative(double const t_y, double const t_u) noexcept : y{t_y}, u{t_u} {}

    double operator()(double const t_u, double const tau, double const T) noexcept
    {
        y = (t_u - u + tau * y) / (T + tau);
        u = t_u;
        return y;
    }
};

int main()
{
    std::array<double, 100> us{};
    for (auto i{0}; i < 100; ++i)
    {
        us[i] = std::fmod(i, utility::PI);
    }
    SmoothDerivative smooth_derivative{0.0, 0.0};
    auto t{0.0};
    for (auto const u : us)
    {
        auto const y{smooth_derivative(u, 2, t)};
        std::cout << t << ',' << y << '\n';
        t+= utility::T;
    }
    return 0;
}
