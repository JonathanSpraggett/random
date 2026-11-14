#pragma once
#include <iostream>
#include <vector>


using namespace std;

string mergeAlternately(string word1, string word2) {
        string result = "";
        int n = word1.length();
        int m = word2.length();
        int counter = 0;
        while (counter <= max(n,m)){
            if (counter < n) {
                result += word1[counter];
            }

            if (counter < m) {
                result += word2[counter];
            }
            counter +=1;

        }
        
        return result;

    }
bool checkStraightLine(vector<vector<int>>& coordinates) {
    
        double last_x = coordinates[1][0] , last_y = coordinates[1][1];
        double first_x = coordinates[0][0] , first_y = coordinates[0][1];

        double last_slope_dir = 0;
            // std::cout <<  slope << coordinates[coordinates.size() -1][1] - coordinates[0][1] << "  " <<  coordinates[coordinates.size() -1][0] - coordinates[0][0] << "Hello, from projects!\n";
         double last_slope ;
            if ((last_x - first_x) == 0) {
                last_slope = 0;
                last_slope_dir = 1;
        }
        else{
            last_slope = (last_y - first_y)/(last_x - first_x);
            last_slope_dir = 0;
            if (last_y - first_y == 0 ){
                last_slope_dir = -1;
            }
        }
        
        double last_b = first_y - last_slope*first_x;
        for (int i = 1; i < coordinates.size(); i++){
            
            last_x = coordinates[i][0] , last_y = coordinates[i][1];
            first_x = coordinates[i-1][0] , first_y = coordinates[i-1][1];
            double slope , slope_dir;
             if ((last_x - first_x) == 0) {
                slope = 0;
                slope_dir = 1;
            }
            else{
                slope = (last_y - first_y)/(last_x - first_x);
                slope_dir = 0;
                if (last_y - first_y == 0 ){
                slope_dir = -1;
                
                }
                
            }
            
            double b = first_y - last_slope*first_x;
            cout << slope <<"   " << last_slope <<"   " << b  <<"   " << last_b <<"   " << slope_dir  <<"   " << last_slope_dir<< endl;
            if (slope != last_slope ||  last_slope_dir != slope_dir){
                return false;
            }
            last_slope = slope;
            last_b = b;       
            last_slope_dir = slope_dir;     
        }
        return true;
        
    }

bool checkStraightLine2(vector<vector<int>>& coordinates) {

        if (coordinates.size() == 2){
            return true;
        }
        
        
        double x1 = coordinates[0][0] , y1 = coordinates[0][1];
        double x2 = coordinates[1][0] - x1 , y2 = coordinates[1][1] - y1;
        for (int i = 2; i < coordinates.size(); i++){
            double x3 = coordinates.at(i).at(0) - x1, y3 = coordinates.at(i).at(1) - y1;
            double cross = x2*y3 - y2*x3;
            if (cross != 0){
                return false;
            }
        }
       
        return true;
        
    }
   



