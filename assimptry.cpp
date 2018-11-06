#include <vector>
#include <iostream>
using namespace std;

int main(){
  std::vector<int> v;
  v.push_back(21);
  v.push_back(213);
  v.push_back(221);
  v.push_back(211);
  v.push_back(231);
  v.push_back(221);
  v.push_back(231);
  v.push_back(2114);
  v.push_back(221);
  v.push_back(211);
  v.push_back(212);
  v.push_back(231);
  v.push_back(2131);
  v.push_back(231);
  v.push_back(221);
  v.push_back(221);
  v.push_back(211);
  v.push_back(211);
  v.push_back(211);
  v.push_back(211);
  v.push_back(231);
  v.push_back(241);
  cout<<v.size()<<endl;
  cout<<v.at(1);
  return 0;
}