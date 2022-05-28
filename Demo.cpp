/**
 * Demo file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
#include <unordered_map>
#include <vector>
#include "sources/OrgChart.hpp"
using namespace ariel;

int main() {
  OrgChart organization;
  vector<string> vec;
  unordered_map<string,vector<string>> umap;
  vec.push_back(" employ1");
  vec.push_back(" employ2");
  vec.push_back(" employ3");
  vector<unordered_map<string, vector<string>>> org;
  umap["boss"] = vec;
  unordered_map<string, vector<string>>:: iterator itr;
  org.push_back(umap);
  organization.add_root("CEO")
      .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
      .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
      .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
      .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
      .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO
    
  cout << organization << endl;
  // organization.add_root("DIAMOND");
  // organization.add_sub("DIAMOND", "Or");
  // cout << organization << endl;

  /* Prints the org chart in a reasonable format. For example:
       CEO
       |--------|--------|
       CTO      CFO      COO
       |                 |
       VP_SW             VP_BI
 */
  // organization.BFS_search("CEO");

  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
  {
    cout << (*it) << " " ;
  } // prints: CEO CTO CFO COO VP_SW VP_BI
  cout << endl << "**************"<<endl;
  for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
  {
    cout << (*it) << " " ;
  } // prints: VP_SW VP_BI CTO CFO COO CEO
  cout << endl << "**************"<<endl;
  for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: CEO CTO VP_SW CFO COO VP_BI
  cout << endl << "**************"<<endl;

  
  for (auto element : organization)
  { // this should work like level order
    cout << element << " " ;
  } // prints: CEO CTO CFO COO VP_SW VP_BI

  // demonstrate the arrow operator:
  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
  {
    cout << it->size() << " ";
  } // prints: 3 3 3 3 5 5
}