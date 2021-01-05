#pragma once


#include <iostream>
#include <vector>
#include <algorithm>
#include <math/point.h>
#include <random>
#include <chrono>

class KMeans {
private:
    int _k;
    int _width;
    int _height;

    struct Centroid {
        int x;
        int y;
        int id;
    };

    std::vector<Point> &_points;
    std::vector<Centroid> _centroids;

    std::random_device rd;
    std::mt19937::result_type seed = rd() ^(
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count());

    std::mt19937 _gen{seed};

    std::uniform_int_distribution<int> _width_distribution{0, _width};
    std::uniform_int_distribution<int> _height_distribution{0, _height};

private:
    static double _euclidean_distance(Centroid &centroid, Point &point);

    int _find_nearest_centroid_id(Point &point);

    static Point _get_mean(std::vector<Point> &points);

public:

    KMeans(int k, int width, int height, std::vector<Point> &points);

    inline std::vector<Centroid> &get_centroids() { return _centroids; }

    void tick();
};

