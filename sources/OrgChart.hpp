#include<iostream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <unordered_map>
#pragma once

using namespace std;
namespace ariel{
    class OrgChart{
        private:
            unordered_map<string, vector <string>*> org;
            string bigBoss = "";
        public:
            class Iterator;
            OrgChart(){}
            OrgChart(const OrgChart &org);
            OrgChart(OrgChart &&org) = default;
            OrgChart & operator=(OrgChart const& org); 
            OrgChart & operator=(OrgChart &&org)noexcept; 
            ~OrgChart();
            static string get_boss(string const & employ);
            string get_root()const{
                return this->bigBoss;
            }
            void set_root(string bigBoss){
                this->bigBoss = move(bigBoss);
            }
            unordered_map<string,vector<string>*> getData()const{return this->org;}
            OrgChart& add_root(string const & boss);
            OrgChart& add_sub(string const & boss, string const & employ);
            Iterator begin()const;
            Iterator end()const;
            Iterator begin_level_order()const;
            Iterator end_level_order()const;
            Iterator begin_reverse_order()const;
            Iterator reverse_order()const;
            Iterator begin_preorder()const;
            Iterator end_preorder() const;
            friend ostream & operator<< (ostream& output, const OrgChart& orgChart);
            
            class Iterator{
            private:
                queue <string> itr;
            public:
                Iterator(unordered_map<string, vector <string>*> org, string const & bigBoss, string const & flag);
                Iterator();
                Iterator & operator++();
                Iterator & operator++(int);
                string & operator*();
                string * operator->();
                bool operator==(Iterator const & itr);
                bool operator!=(Iterator const & itr);
                void beginLevelOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss);
                void endLevelOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss);
                void beginReverseLevelOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss);
                static void endReverseLevelOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss);
                void beginPreOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss);
                static void endPreOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss);
            };
    };
};
