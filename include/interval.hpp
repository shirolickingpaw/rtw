#ifndef INTERVAL_HPP
#define INTERVAL_HPP

class interval {
    public:
        double min, max;
        interval();

        interval(double min, double max);

        double size() const;
        bool contains(double x) const;
        bool surrounds(double x) const;

        static const interval empty, universe;
};

#endif
