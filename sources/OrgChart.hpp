#include<iostream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include "Node.hpp"
#pragma once

using namespace std;
namespace ariel{
    class OrgChart{
        public:
            // Node *root;
            OrgChart(){}
            string get_boss(string employ);
            OrgChart add_root(string boss);
            OrgChart add_sub(string boss, string employ);
            vector<int>::iterator begin();
            vector<int>::iterator end();
            vector<string>::iterator begin_level_order();
            vector<string>::iterator end_level_order();
            vector<string>::iterator begin_reverse_order();
            vector<string>::iterator reverse_order();
            vector<string>::iterator begin_preorder();
            vector<string>::iterator end_preorder();
            friend ostream & operator<< (ostream& output, const OrgChart& orgChart);
    };
};
