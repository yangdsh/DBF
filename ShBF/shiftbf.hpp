#ifndef __SHIFTBF_BF_HPP__
#define __SHIFTBF_BF_HPP__

#include "../Common Files/config.hpp"
#include "../Common Files/typefwd.hpp"
#include "../Common Files/array_bool.hpp"
#include "../Common Files/rawData.hpp"
#include "../Common Files/BOBHash.hpp"

#include <vector>
using namespace std;

class sbf_array_bool_t;
class shiftBF;

class sbf_array_bool_t: public array_bool_t{
private:
      static const uint8_t MaxSetNum = SET_NUM;  
public:
      uint32_t operator[](uint32_t);
};

class shiftBF{
private:
      uint32_t wide;
      
      static const uint8_t MaxSetNum = SET_NUM;
      sbf_array_bool_t bf;
      
      uint32_t k;
      vector<BOBHash> hf;
      
      shiftBF();
      shiftBF(const shiftBF &);
      shiftBF &operator =(const shiftBF &);
public:
      shiftBF(uint32_t, uint32_t);
//      void getHashValue(const rawData_t &, uint32_t *);
      void insert(uint8_t, const unsigned char *, uint32_t);
      int search(const unsigned char *, uint32_t);
};
  

#endif
