#include "pam.h"
#include <iostream>
#include <algorithm>
using namespace std;

void check(bool test, string message) {
  if (!test) {
    cout << "Failed test: " << message << endl;
    exit(1);
  }
}

struct pp {
  int u;
  int v;
  float dist;
  pp(): u(-1), v(-1), dist(-1){};
  pp(int uu, int vv, float distt): u(uu), v(vv), dist(distt) {}
  friend bool operator<(pp i,pp j) {
    if (i.dist == j.dist) return i.u<j.u;
    return i.dist < j.dist;
  }
};

template<class pp>
struct edge_entry {
  using key_t = pp;
  using aug_t = float;
  using entry_t = pp;
  using val_t = entry_t;
  static inline key_t get_key(const entry_t& e) {return e;}
  static inline val_t get_val(const entry_t& e) {return e;}
  static inline void set_val(entry_t& e, const val_t& v) {
    e.u = v.u;
    e.v = v.v;
    e.dist = v.dist;}
  static inline aug_t from_entry(const entry_t& e) {
    return e.dist;}
  static inline bool comp(key_t a, key_t b) { return a<b;}
  static aug_t get_empty() { return -1;}
  //static aug_t from_entry(key_t k , val_t v) { return v/2.0;}
  static aug_t combine(aug_t a, aug_t b) { return a + b;}
  // following just used for treaps
  //static size_t hash(pair<key_t,val_t> e) { return pbbs::hash64(e.first);}
};

template <class _Entry, class Balance=weight_balanced_tree>
using aug_map_edge =
  aug_map_<edge_entry<_Entry>,
  typename Balance::template
  balance<aug_node<typename Balance::data,
		   edge_entry<_Entry>>>>;

using map_pp  = aug_map_edge<pp>;

template <class map>
void test_map() {
  ////////////////////

  pbbs::sequence<pp> pps = {pp(2,4,1.3), pp(4,5,3.3), pp(6,8,1.1)};
  map_pp mp(pps);

  cout << "mp size = " << mp.size() << endl;
  check(mp.size() == 3, "size check mp");

  check((*mp.find(pp(4,5,3.3))).u == 4, "find check 3.3 u");
  check((*mp.find(pp(4,5,3.3))).v == 5, "find check 3.3 v");
  check(!mp.find(pp(2,4,10.0)), "find check 3");
  check((*mp.find(pp(2,4,1.3))).v == 4, "find test 1.3 v");
  check((*mp.find(pp(6,8,1.1))).v == 8, "find test 1.1 v");
  check((*mp.find(pp(4,5,3.3))).u == 4, "find test 3.3 u");

  check(mp.rank(pp(2,4,1.3)) == 1, "rank test 1.3");
  check(mp.rank(pp(4,5,3.3)) == 2, "rank test 3.3");
  check(mp.rank(pp(6,8,1.1)) == 0, "rank test 1.1");

  //this is by rank
  check((*mp.select(0)).u == 6, "select test 0 u");
  check((*mp.select(1)).v == 4, "select test 1 v");
  check((*mp.select(2)).u == 4, "select test 2 u");

  pbbs::sequence<pp> pps2 = {pp(2,4,2.3), pp(4,5,3.2), pp(6,8,1.0)};
  auto mp2 = map_pp::multi_insert(mp, pps2);
  cout << "mp2 size = " << mp2.size() << endl;
  check(mp2.size() == 6, "size check mp");

  // check(mp2.rank(1.0) == 0, "rank test 1.0");
  // check(mp2.rank(1.1) == 1, "rank test 1.1");
  // check(mp2.rank(1.3) == 2, "rank test 1.3");
  // check(mp2.rank(2.3) == 3, "rank test 2.3");
  // check(mp2.rank(3.2) == 4, "rank test 3.2");
  // check(mp2.rank(3.3) == 5, "rank test 3.3");

  // map_pp mdiff(pps2);
  // auto mp3 = map_pp::map_difference(mp2, mdiff);
  //
  pbbs::sequence<pp> pps3 = {pp(2,2,2.3), pp(4,4,3.2), pp(6,6,1.0)};
  auto mp3 = map_pp::multi_delete(mp2, pps3);

  cout << "mp3 size = " << mp3.size() << endl;
  check(mp3.size() == 3, "size check mp3");

  // check((*mp3.find(3.3)).u == 4, "find check 3.3 u");
  // check((*mp3.find(3.3)).v == 5, "find check 3.3 v");
  // check(!mp3.find(10.0), "find check 3");
  // check((*mp3.find(1.3)).v == 4, "find test 1.3 v");
  // check((*mp3.find(1.1)).v == 8, "find test 1.1 v");
  // check((*mp3.find(3.3)).u == 4, "find test 3.3 u");

  // check(mp3.rank(1.3) == 1, "rank test 1.3");
  // check(mp3.rank(3.3) == 2, "rank test 3.3");
  // check(mp3.rank(1.1) == 0, "rank test 1.1");

  // //this is by rank
  // check((*mp3.select(0)).u == 6, "select test 0 u");
  // check((*mp3.select(1)).v == 4, "select test 1 v");
  // check((*mp3.select(2)).u == 4, "select test 2 u");
  return;
}    

using rb_map = aug_map_edge<edge_entry<pp>,red_black_tree>;

void test_all() {
  test_map<rb_map>();
  cout << "passed!!" << endl;
}

int main() {
  test_all();
}


  
