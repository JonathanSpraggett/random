
#include <iostream>
#include <vector>
#include <unordered_map>
#include <optional>
#include <cmath>
#include <algorithm>
#include <string>

// ========================================
// PROVIDED DATA STRUCTURES
// ========================================

struct Point2D {
    double x;
    double y;
};

struct Obstacle {
    int id;
    Point2D position;
    double timestamp;
};

// ========================================
// YOUR IMPLEMENTATION
// ========================================

class ObstacleMonitor {
   
    
public:
    ObstacleMonitor(double safety_radius, double timeout) : safety_radius_{safety_radius},timeout_{timeout} {
        // TODO
    }

    void updateObstacle(const Obstacle& obs) {
        auto it = obs_list.find(obs.id);
        if (it != obs_list.end()) {
            if (it->second.timestamp <= obs.timestamp ){
                it->second = obs;
            }
        }
        else{
            obs_list.insert({obs.id, obs});
        }
        
        
    }

    void removeObstacle(int id) {

        obs_list.erase(id);
            
        
       
    }

    std::optional<int> closestBlockingObstacle(
        const Point2D& start,
        const Point2D& end,
        double current_time) const
    {
        double min_obs = std::numeric_limits<double>::infinity();
        int min_id = 0;
        for (const auto&  [id, obs] : obs_list){
            if (current_time - obs.timestamp <= timeout_ && current_time - obs.timestamp >= 0) {
                // std::cout << id << "  22 " << obs.timestamp << "   " << obs.position.x << "   " << obs.position.y << std::endl;
                
                Point2D s_e, s_obs, e_obs;
                s_e.x = end.x - start.x;
                s_e.y = end.y - start.y;
                s_obs.x = obs.position.x - start.x;
                s_obs.y = obs.position.y - start.y;
                e_obs.x = obs.position.x - end.x;
                e_obs.y = obs.position.y - end.y;
                double num ;
                double denom;

                double height = std::numeric_limits<double>::infinity();

                double dot_1 = (s_e.x * s_obs.x + s_e.x * s_obs.x);
                double dot_2 = (s_e.x * e_obs.x + s_e.x * e_obs.x);


                if (s_e.x == 0 && s_e.y == 0) {
                    height = std::hypot(s_obs.x, s_obs.y);

                }
                else if (dot_1 <= 0) {
            // Closest point is START
                height = std::hypot(s_obs.x, s_obs.y);
            }
            else if (dot_2 >= 0) {
                // Closest point is END
                height = std::hypot(e_obs.x, e_obs.y);
                }       
                else{
                     
                   

                     num = s_e.y * s_obs.x - s_e.x * s_obs.y;
                     denom = std::hypot(s_e.x, s_e.y);

                     height = std::abs(num/denom);

                std::cout << id << "   " << obs.timestamp << "   " << obs.position.x << "   " << obs.position.y  << "   " << dot_1 << "   " << dot_2  << "   " << height << std::endl;
                    
                }

            
                if (height <= safety_radius_){
                    if (height == min_obs && id < min_id) {
                        
                        min_obs = height;
                        min_id = id;
                    }
                    else if (height < min_obs) {
                        min_obs = height;
                        min_id = id;
                    }

                }

            }
        }

        if (min_obs != std::numeric_limits<double>::infinity()){
            return min_id;
        }
        return std::nullopt;
    }

private:
    std::unordered_map<int,Obstacle> obs_list;
    double safety_radius_, timeout_;
};

// ========================================
// TEST FRAMEWORK - DO NOT MODIFY
// ========================================

int passed = 0;
int total = 0;

void check(
    const std::string& name,
    std::optional<int> actual,
    std::optional<int> expected)
{
    total++;

    if (actual == expected) {
        passed++;
        std::cout << "[PASS] " << name << "\n";
    } else {
        std::cout << "[FAIL] " << name
                  << " | Expected: ";

        if (expected)
            std::cout << *expected;
        else
            std::cout << "nullopt";

        std::cout << " | Got: ";

        if (actual)
            std::cout << *actual;
        else
            std::cout << "nullopt";

        std::cout << "\n";
    }
}

// ========================================
// TEST CASES
// ========================================

int main() {

    const Point2D start{0.0, 0.0};
    const Point2D end{10.0, 0.0};

    // TEST 1: Empty monitor
    {
        ObstacleMonitor monitor(1.0, 3.0);

        check("Empty monitor",
              monitor.closestBlockingObstacle(
                  start, end, 12.0),
              std::nullopt);
    }

    // TESTS 2-6: Updates, expiry, and removal
    {
        ObstacleMonitor monitor(1.0, 3.0);

        monitor.updateObstacle(
            {101, {4.0, 0.5}, 10.0});

        monitor.updateObstacle(
            {102, {7.0, 2.0}, 11.0});

        monitor.updateObstacle(
            {103, {9.0, 0.3}, 8.0});

        check("Initial observations",
              monitor.closestBlockingObstacle(
                  start, end, 12.0),
              101);

        // Move obstacle 102 closer
        monitor.updateObstacle(
            {102, {7.0, 0.2}, 12.0});

        check("Obstacle updated",
              monitor.closestBlockingObstacle(
                  start, end, 12.0),
              102);
              
        // Older observation should be ignored
        monitor.updateObstacle(
            {102, {7.0, 2.0}, 11.0});

        check("Ignore older observation",
              monitor.closestBlockingObstacle(
                  start, end, 12.0),
              102);

        monitor.removeObstacle(102);

        check("Remove obstacle",
              monitor.closestBlockingObstacle(
                  start, end, 12.0),
              101);

        check("Exactly at timeout",
              monitor.closestBlockingObstacle(
                  start, end, 13.0),
              101);

        check("Expired observations",
              monitor.closestBlockingObstacle(
                  start, end, 13.01),
              std::nullopt);
    }

    // TEST 8: Exactly at safety radius
    {
        ObstacleMonitor monitor(1.0, 3.0);

        monitor.updateObstacle(
            {201, {5.0, 1.0}, 20.0});

        check("Safety radius boundary",
              monitor.closestBlockingObstacle(
                  start, end, 20.0),
              201);
    }

    // TEST 9: Obstacle beyond path endpoint
    {
        ObstacleMonitor monitor(1.0, 3.0);

        monitor.updateObstacle(
            {202, {12.0, 0.0}, 20.0});

        check("Beyond segment endpoint",
              monitor.closestBlockingObstacle(
                  start, end, 20.0),
              std::nullopt);
    }

    // TEST 10: Zero-length path
    {
        ObstacleMonitor monitor(1.0, 3.0);

        monitor.updateObstacle(
            {301, {2.6, 2.0}, 20.0});

        check("Zero-length segment",
              monitor.closestBlockingObstacle(
                  {2.0, 2.0},
                  {2.0, 2.0},
                  20.0),
              301);
    }

    // TEST 11: Equal distances
    {
        ObstacleMonitor monitor(1.0, 3.0);

        monitor.updateObstacle(
            {9, {4.0, 0.5}, 20.0});

        monitor.updateObstacle(
            {3, {6.0, -0.5}, 20.0});

        check("Tie breaking",
              monitor.closestBlockingObstacle(
                  start, end, 20.0),
              3);
    }

    // TEST 12: Future timestamp
    {
        ObstacleMonitor monitor(1.0, 3.0);

        monitor.updateObstacle(
            {401, {5.0, 0.0}, 30.0});

        check("Future observation",
              monitor.closestBlockingObstacle(
                  start, end, 29.0),
              std::nullopt);
    }
    // TEST 13: Obstacle exactly at start
    {
        ObstacleMonitor monitor(1.0, 3.0);
        monitor.updateObstacle({501, {0.0, 0.0}, 20.0});

        check("Obstacle at start",
              monitor.closestBlockingObstacle(
                  {0.0, 0.0}, {10.0, 0.0}, 20.0),
              501);
    }

    // TEST 14: Obstacle near endpoint
    {
        ObstacleMonitor monitor(1.0, 3.0);
        monitor.updateObstacle({502, {10.5, 0.0}, 20.0});

        check("Near endpoint",
              monitor.closestBlockingObstacle(
                  {0.0, 0.0}, {10.0, 0.0}, 20.0),
              502);
    }

    // TEST 15: Diagonal segment, beyond endpoint
    {
        ObstacleMonitor monitor(1.08, 3.0);
        monitor.updateObstacle({503, {11.0, 9.5}, 20.0});

        check("Diagonal endpoint distance",
              monitor.closestBlockingObstacle(
                  {0.0, 0.0}, {10.0, 10.0}, 20.0),
              std::nullopt);
    }

    // ====================================
    // RESULTS
    // ====================================

    std::cout << "\n"
              << passed << "/" << total
              << " tests passed.\n";

    return 0;
}
