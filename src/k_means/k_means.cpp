#include "k_means.h"

KMeans::KMeans(int k, int width, int height, std::vector<Point> &points)
        : _k(k), _width(width), _height(height), _points(points) {

    for (int i = 0; i < _k; i++)
        _centroids.push_back({
                                     _width_distribution(_gen),
                                     _height_distribution(_gen),
                                     i
                             });
}

double KMeans::_euclidean_distance(Centroid &centroid, Point &point) {
    return std::pow(centroid.x - point.x, 2) + std::pow(centroid.y - point.y, 2);
}

int KMeans::_find_nearest_centroid_id(Point &point) {
    std::vector<Centroid> centroids(_centroids);

    std::sort(std::begin(centroids), std::end(centroids), [&](Centroid &a, Centroid &b) {
        return _euclidean_distance(a, point) < _euclidean_distance(b, point);
    });

    return centroids.at(0).id;
}

Point KMeans::_get_mean(std::vector<Point> &points) {
    int n = points.size();

    int x = 0;
    int y = 0;

    for (auto &point: points) {
        x += point.x;
        y += point.y;
    }

    return {x / n, y / n};
}

void KMeans::tick() {
    for (auto &point: _points) {
        int nearest_centroid_id = _find_nearest_centroid_id(point);

        point.centroid = nearest_centroid_id;
    }

    for (auto &centroid: _centroids) {
        std::vector<Point> centroid_points;

        std::copy_if(_points.begin(), _points.end(), std::back_inserter(centroid_points),
                     [&](Point &point) { return point.centroid == centroid.id; });

        if (centroid_points.empty())
            continue;

        Point mean = _get_mean(centroid_points);

        centroid.x = mean.x;
        centroid.y = mean.y;
    }
}
