#include<iostream>
#include <string>
#include <vector>
#include "OrgChart.hpp"
#include<iterator>

using namespace ariel;
using namespace std; 

OrgChart OrgChart::add_root(string boss){
    // if(this->root != NULL){
    //     this->root->data = data;
    // }
    // else{
    //     Node *temp = this->root;
    //     this->root->data = data;
    //     this->add_sub(this->root->data, temp->data);
    // }
    return *this;
}

OrgChart OrgChart::add_sub(string boss, string employ){
    
    return *this;
}

string OrgChart::get_boss(string employ){
    return "";
}

ostream & ariel::operator<< (ostream& out, const OrgChart& orgChart){
    string ans;
    out << ans;
    return out;
}

vector<int>::iterator OrgChart::begin(){
    vector<int>::iterator mt;
    return mt;
}

vector<int>::iterator OrgChart::end(){
    vector<int>::iterator mt;
    return mt;
}

vector<string>::iterator OrgChart::begin_level_order(){
    vector<string>::iterator mt;
    return mt;
}

vector<string>::iterator OrgChart::end_level_order(){
    vector<string>::iterator mt;
    return mt;
}

vector<string>::iterator OrgChart::begin_reverse_order(){
    vector<string>::iterator mt;
    return mt;
}

vector<string>::iterator OrgChart::reverse_order(){
    vector<string>::iterator mt;
    return mt;
}

vector<string>::iterator OrgChart::begin_preorder(){
    vector<string>::iterator mt;
    return mt;
}

vector<string>::iterator OrgChart::end_preorder(){
    vector<string>::iterator mt;
    return mt;
}