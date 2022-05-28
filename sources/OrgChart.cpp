#include<iostream>
#include <string>
#include <vector>
#include "OrgChart.hpp"
#include<iterator>
#include <list>
#include <bits/stdc++.h>

using namespace ariel;
using namespace std; 


void check_input(string boss, string employ = "Diamond"){
    int countSpace = 0;
    for(size_t i = 0; i < boss.size(); i++){
        if(boss.at(i) < '!' || boss.at(i) >= '~'){
            if(boss.at(i) != ' '){
                throw invalid_argument("ASCII value of chars needs to be between 33-126");
            }
            countSpace++;
        }
    }

    if(countSpace == boss.size()){
        throw invalid_argument("Name can't be with just spaces");
    }

    countSpace = 0;
    if(employ != "Diamond"){
        for(size_t i = 0; i < employ.size(); i++){
            if(employ.at(i) < '!' || employ.at(i) >= '~'){
                if(employ.at(i) != ' '){
                    throw invalid_argument("ASCII value of chars needs to be between 33-126");
                }
                countSpace++;
            }
        }
        if(countSpace == employ.size()){
            throw invalid_argument("Name can't be with just spaces");
        }
    }
}

OrgChart::OrgChart(const OrgChart &org){
    for(auto const & itr : org.getData()){
        vector<string> newVec = vector<string>(*itr.second);
        this->org.insert({itr.first, &newVec});
    }
    this->set_root(org.get_root());
}

OrgChart & OrgChart::operator=(OrgChart const& org){
    *this = OrgChart(org);
    return *this;
}

OrgChart & OrgChart::operator=(OrgChart &&org)noexcept{
    *this = OrgChart(org);
    return *this;
}

OrgChart::~OrgChart(){
    for(auto const & it : this->org){
        delete(it.second);
    }
}

void OrgChart::set_root(string bigBoss){
    this->bigBoss = move(bigBoss);
}

string OrgChart::get_root()const{
    return this->bigBoss;
}

OrgChart &OrgChart::add_root(string const & boss){
    check_input(boss);
    if(!this->get_root().empty()){
        vector<string> *employes = nullptr;
        auto it = this->org.find(this->get_root());
        employes = it->second;
        this->org.erase(this->get_root());
        this->org[boss] = employes;
        this->set_root(boss);
    }
    else{
        vector<string> *vec = nullptr;
        vec = new vector<string>;
        this->set_root(boss);
        this->org.insert({boss, vec});
    }
    return *this;
}

OrgChart &OrgChart::add_sub(string const & boss, string const & employ){
    check_input(boss, employ);
    if(this->get_root().empty()){throw ("Can't add when the big boss is undefined");}
    auto it = this->org.find(boss);
    if(it == this->org.end()){throw ("Unable to add role for a role not hired yet");}
    it->second->push_back(employ);
    if(boss != employ){
        vector<string> *vec = nullptr;
        vec = new vector<string>;
        this->org.insert({employ, vec});
    }
    return *this;
}

string OrgChart::get_boss(string const & employ){
    return "";
}

ostream & ariel::operator<< (ostream & out, const OrgChart& orgChart){
    string bigBoss = orgChart.get_root();
    queue <string> q;
    queue <int> level;
    level.push(1);
    q.push(bigBoss);
    while(! q.empty()){
        string boss = q.front();
        int currlvl = level.front();
        out << currlvl << ") "<< boss << " ---> ( ";
        vector <string> employ = *orgChart.getData().find(boss)->second;
        for(auto const & emp : employ){
            out << emp << " ";
            q.push(emp);
            level.push(currlvl + 1);
        }
        out << ")"<< endl;
        q.pop();
        level.pop();
    }
    return out;
}


OrgChart::Iterator::Iterator(){}

OrgChart::Iterator::Iterator(unordered_map<string, vector <string>*> org, string const & bigBoss, string const & flag){
    if(flag == "beginLevelOrder"){
        this->beginLevelOrder(org, bigBoss);
    }
    else if(flag == "beginReverseLevelOrder"){
        this->beginReverseLevelOrder(org, bigBoss);
    }
    else if(flag == "beginPreOrder"){
        this->beginPreOrder(org, bigBoss);
    }
    // else if(flag == "endPreOrder"){
    //     // this->endPreOrder(org, bigBoss);
    // }   
}


OrgChart::Iterator & OrgChart::Iterator::operator++(){
    this->itr.pop();
    return *this;
}



bool OrgChart::Iterator::operator==(Iterator const & itr){
        return this->itr != itr.itr;
}

bool OrgChart::Iterator::operator!=(Iterator const & itr){
    return this->itr != itr.itr;
}

string& OrgChart::Iterator::operator*(){
    return this->itr.front();
}

string* OrgChart::Iterator::operator->(){
    return &this->itr.front();
}

void OrgChart::Iterator::beginLevelOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss){
    queue <string> q;
    q.push(bigBoss);
    while(! q.empty()){
        string boss = q.front();
        vector <string> employ = *org.find(boss)->second;
        for(auto const & emp : employ){
            if(boss != emp){
                q.push(emp);
            }
        }
        this->itr.push(q.front());
        q.pop();
    }
}

void OrgChart::Iterator::endLevelOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss){
    
}

void OrgChart::Iterator::beginReverseLevelOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss){
    deque <string> ans;
    queue <string> q;
    q.push(bigBoss);
    while(! q.empty()){
        string boss = q.front();
        vector <string> employ = *org.find(boss)->second;
        reverse(employ.begin(), employ.end());
        for(auto const & emp : employ){
            if(boss != emp){
                q.push(emp);
            }
        }
        this->itr.push(q.front());
        q.pop();
    }
    while(!this->itr.empty()){
        ans.push_front(this->itr.front());
        this->itr.pop();
    }
    while(!ans.empty()){
        this->itr.push(ans.front());
        ans.pop_front();
    }
}

void OrgChart::Iterator::endReverseLevelOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss){
    vector<string> a;
}

void OrgChart::Iterator::beginPreOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss){
    deque <string> q;
    q.push_front(bigBoss);
    while(! q.empty()){
        string name = q.back();
        this->itr.push(name);
        q.pop_back();
        vector <string> employ = *org.find(name)->second;
        reverse(employ.begin(), employ.end());
        for(auto const & emp : employ){
            if(name != emp){
                q.push_back(emp);
            }
        }
    }
}

void OrgChart::Iterator::endPreOrder(unordered_map<string, vector <string>*> & org, string const & bigBoss){
    vector<string> a;
}

OrgChart::Iterator OrgChart::begin()const{
    if(this->get_root().empty()){throw ("Empty chart");}
    Iterator ans = Iterator(this->getData(), this->get_root(), "beginLevelOrder");
    return ans;
    
}



OrgChart::Iterator OrgChart::end()const{
    if(this->get_root().empty()){throw ("Empty chart");}
    Iterator ans;
    return ans;
}

OrgChart::Iterator OrgChart::begin_level_order()const{
    if(this->get_root().empty()){throw ("Empty chart");}
    Iterator ans = Iterator(this->getData(), this->get_root(), "beginLevelOrder");
    return ans;
}

OrgChart::Iterator OrgChart::end_level_order()const{
    if(this->get_root().empty()){throw ("Empty chart");}
    Iterator mt;
    return mt;
}

OrgChart::Iterator OrgChart::begin_reverse_order()const{
    if(this->get_root().empty()){throw ("Empty chart");}
    Iterator ans = Iterator(this->getData(), this->get_root(), "beginReverseLevelOrder");
    return ans;
}

OrgChart::Iterator OrgChart::reverse_order()const{
    if(this->get_root().empty()){throw ("Empty chart");}
    Iterator mt;
    return mt;
}

OrgChart::Iterator OrgChart::begin_preorder()const{
    if(this->get_root().empty()){throw ("Empty chart");}
    Iterator ans = Iterator(this->getData(), this->get_root(), "beginPreOrder");
    return ans;
}

OrgChart::Iterator OrgChart::end_preorder() const{
    if(this->get_root().empty()){throw ("Empty chart");}
    Iterator mt;
    return mt;
}