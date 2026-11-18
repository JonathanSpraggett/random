#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>

struct Point {
    int id;
    double x;
    double y;
    bool blocked;
    
};

void print_point(const Point& a){
    std::cout << a.id << "  " << a.x << "  " << a.y << "  " << a.blocked << std::endl;
}

int main(int, char**){

    std::vector<Point> points = {
        {1, 4.0, 0.0, false},
        {2, 1.0, 2.0, true},
        {3, -2.0, 0.0, false},
        {4, 9.0, 0.0, false},
        {5, 3.0, 4.0, false},
        {6, 0.0, 1.0, true}
    };

    double robot_x = 0.0;
    double robot_y = 0.0;
    double max_range = 6.0;

     // 1. SORT: Sort points by X coordinate
    std::cout <<std::boolalpha << "sort before\n";
    for (const auto& i : points) {
        print_point(i);
    }


     std::sort(points.begin(), points.end(), 
     [robot_x, robot_y] (const Point& a, const Point& b) {
        double a_dist = std::hypot(a.x - robot_x, a.y - robot_y);
        double b_dist = std::hypot(b.x - robot_x, b.y - robot_y);
        return a_dist <b_dist;
     }
    );
    std::cout <<std::boolalpha << "sort after \n";
    for (const auto& i : points) {
        print_point(i);
    }
    // 2. FIND_IF: Find first blocked point
    std::cout << "Find \n";
    auto it = std::find_if(points.begin(), points.end(),
    [] (const Point& p) {return p.blocked;}
    );
    if (it != points.end()) {
        std::cout << "first blocked " << it->id << std::endl;
    }

    // 3. COUNT_IF: Count blocked points
    std::cout << "Count \n";
    int count = std::count_if(points.begin(), points.end(), 
     [robot_x, robot_y, max_range] (const Point& a) {
        double a_dist = std::hypot(a.x - robot_x, a.y - robot_y);
        return a_dist <= max_range && a.blocked;
     });
     std::cout << "Blocked count: " << count << '\n';

      // 4. MIN_ELEMENT: Find point with smallest X
    std::cout << "Count \n";
    std::vector<Point> valid;

    std::copy_if(points.begin(), points.end(), std::back_inserter(valid), [] (const Point& p) {return !p.blocked;});

    auto close_x = std::min_element(valid.begin(), valid.end(), 
    [robot_x, robot_y] (const Point& a, const Point& b) {
        double a_dist = std::hypot(a.x - robot_x, a.y - robot_y);
        double b_dist = std::hypot(b.x - robot_x, b.y - robot_y);
        return a_dist <b_dist;
     });
    if (close_x != points.end()) {
         std::cout << "Minimum X: " << close_x->id << '\n';
    }


    // 5. TRANSFORM: Calculate distances from robot
    std::cout << "Transform \n";
    std::vector<double> distances;

    std::transform(points.begin(), points.end(), std::back_inserter(distances), 
                    [robot_x, robot_y] (const Point& p) {return std::sqrt((p.x - robot_x)*(p.x - robot_x) + (p.y - robot_y)*(p.y - robot_y));});
    // std::hypot(p.x - robot_x, p.y - robot_y)
    for (const auto& i: distances){
        std::cout << i << std::endl;
    }

    std::vector<Point> new_point;

    std::transform(points.begin(), points.end(), std::back_inserter(new_point), 
                    [robot_x, robot_y] (const Point& p) {
                        Point a;
                        a.x = p.x - robot_x;
                        a.y = p.y - robot_y;
                        a.blocked = p.blocked;
                        a.id = p.id;
                        return a;
                    });
    // std::hypot(p.x - robot_x, p.y - robot_y)
    for (const auto& i: distances){
        std::cout << i << std::endl;
    }

    for (const auto& i: new_point){
        print_point(i);
    }

    // 6. ACCUMULATE: Sum all distances
    std::cout << "Accum \n";

    double total_dist = std::accumulate(distances.begin(), distances.end(), 0.0
);
    std::cout << "Total distance: " << total_dist << '\n';

   std::vector<double> segments;
for (size_t i = 1; i < points.size(); ++i) {
    segments.push_back(std::hypot(
        points[i].x - points[i-1].x,
        points[i].y - points[i-1].y
    ));
}

double length = std::accumulate(
    segments.begin(), segments.end(), 0.0);

    std::cout << "Total distance: " << length << '\n';

    // 7. REMOVE_IF: Remove blocked or distant points
    std::cout << "Remove \n";

    points.erase(std::remove_if(points.begin(), points.end(), [=] (const Point& p) {
       double d = std::hypot(
                    p.x - robot_x,
                    p.y - robot_y
                );
        return p.blocked || d > max_range;
    }), points.end());
     // Print remaining points
    for (const auto& p : points) {
        std::cout << "Valid point: " << p.id << '\n';
    }
    // std::atan2(y,x)

}

