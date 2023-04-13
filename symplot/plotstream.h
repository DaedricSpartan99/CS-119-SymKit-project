#ifndef PLOTSTREAM_H
#define PLOTSTREAM_H

#include "plotdata.h"
#include "plotutils.h"

#include <vector>
#include <initializer_list>

//Represente une courbe
template <class T>
class PlotStream
{
    std::vector<plot_data<T>> data;

public:

    PlotStream(const std::initializer_list<plot_data<T>>& data = {})

        : data(data) {}

    PlotStream& operator<<(const plot_data<T>& point)
    {
        append(point);
        return *this;
    }

    const plot_data<T>& operator[](std::size_t n)
    {
        return data[n];
    }

    typedef typename std::vector<plot_data<T>>::iterator iterator;
    typedef typename std::vector<plot_data<T>>::const_iterator const_iterator;

    iterator begin()
    {
        return data.begin();
    }

    iterator end()
    {
        return data.end();
    }

    const_iterator begin() const
    {
        return data.begin();
    }

    const_iterator end() const
    {
        return data.end();
    }

    void append(const plot_data<T>& point)
    {
        data.push_back(point);
    }

    void remove(std::size_t n)
    {
        data.erase(n);
    }

    void clear()
    {
        data.clear();
    }
};

#endif // PLOTSTREAM_H
