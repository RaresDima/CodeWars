#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using std::pair;
using std::vector;


class Interval
{
public:
    int begin;
    int end;

    Interval(pair<int, int>& data) : begin(data.first), end(data.second) {}
    Interval(const Interval& other) : begin(other.begin), end(other.end) {}

    int size() { return end - begin; }

    bool operator < (const Interval& other) { return begin < other.begin; }

    bool overlaps(const Interval& other) 
    {
        const Interval* hi;
        const Interval* lo;

        if (*this < other)
        {
            hi = &other;
            lo = this;
        }
        else
        {
            hi = this;
            lo = &other;
        }

        return hi->begin <= lo->end;
    }

    Interval& combine(const Interval& other)
    {
        begin = std::min(begin, other.begin);
        end = std::max(end, other.end);
        return *this;
    }
};


int sum_intervals(vector<pair<int, int>> raw_intervals) 
{
    if (raw_intervals.size() == 0)
        return 0;

    vector<Interval> intervals{ raw_intervals.begin(), raw_intervals.end() };
    std::sort(intervals.begin(), intervals.end());

    int total_size{ 0 };
    Interval current_interval{ intervals[0] };
    for (Interval& interval : intervals)
    {
        if (current_interval.overlaps(interval))
        {
            current_interval.combine(interval);
            std::cout << "[" << current_interval.begin << ", " << current_interval.end << "] ";
        }
        else
        {
            total_size += current_interval.size();
            current_interval = interval;
            std::cout << total_size << std::endl;
        }
    }

    total_size += current_interval.size();

    return total_size;
}


int main()
{
    std::cout << sum_intervals({ {1, 4}, {7, 10}, {3, 5} }) << std::endl;

    std::cout << "Hello World!\n";
}
