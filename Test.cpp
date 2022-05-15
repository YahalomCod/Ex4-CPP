#include <iostream>
#include "doctest.h"
#include <stdexcept>
#include "sources/OrgChart.hpp"
using namespace std;
#include <vector>
using namespace ariel;
#include <string>


TEST_CASE("Good input") {
    OrgChart org;
    CHECK_NOTHROW(org.add_root("CEO"));
    CHECK_NOTHROW(org.add_sub("CEO", "CTO"));
    CHECK_NOTHROW(org.add_sub("CTO", "VP_SW"));
    org.add_sub("CEO", "CFO")         
            .add_sub("CEO", "COO")         
            .add_sub("COO", "VP_BI");    
    CHECK(org.get_boss("CTO") == "CEO");
    CHECK(org.get_boss("VP_BI") == "COO");
    CHECK_NOTHROW(org.add_root("CHAPASH"));
    CHECK(org.get_boss("CTO") == "CHAPASH");
    CHECK_NOTHROW(cout << org);
    CHECK_NOTHROW(org.add_sub("CHAPASH", "SAMAL"));
    CHECK(org.get_boss("SAMAL") == "CHAPASH");
    CHECK(org.begin_preorder() == org.begin_level_order());
    CHECK_NOTHROW(org.add_root("CEO"));
    CHECK_NOTHROW(org.add_sub("CEO", "CHAPASH"));
    CHECK(org.get_boss("CHAPASH") == "CEO");
}

TEST_CASE("Bad input") {
    OrgChart org; 
    org.add_root("CEO")
            .add_sub("CEO", "CTO")         
            .add_sub("CEO", "CFO")         
            .add_sub("CEO", "COO")
            .add_sub("CTO", "VP_SW")
            .add_sub("COO", "VP_BI");
    CHECK_THROWS(org.get_boss("CEO"));      
    CHECK_THROWS(org.add_sub("no manager", "CHAPASH"));
    org.add_root("CHAPASH");
    CHECK_FALSE(org.get_boss("CTO") == "CEO");
    CHECK_THROWS(org.get_boss("CHAPASH"));
    CHECK_THROWS(org.add_sub("CTO", "CHAPASH"));//cant be the boss of his boss
    CHECK_THROWS(org.add_sub("CTO", "CTO"));

}