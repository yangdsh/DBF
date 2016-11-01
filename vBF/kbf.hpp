#ifndef __KBF_KBF_HPP__
#define __KBF_KBF_HPP__

#include "../Common Files/config.hpp"
#include "../Common Files/typefwd.hpp"
#include "../Common Files/array_bool.hpp"
#include "../Common Files/rawData.hpp"
#include "../Common Files/BOBHash.hpp"

#include <vector>
using namespace std;

class KBF;

class KBF{
private:
      static const uint8_t MaxSetNum = SET_NUM;
      uint32_t wide[MaxSetNum];
      array_bool_t bf[MaxSetNum];
      
      uint32_t k;
      vector<BOBHash> hf[MaxSetNum];
      
      KBF();
      KBF(const KBF &);
      KBF &operator =(const KBF &);
public:
      KBF(uint32_t, uint32_t);
//      void getHashValue(const rawData_t &, uint32_t *);
      void insert(uint8_t, const unsigned char *, uint32_t);
      int search(const unsigned char *, uint32_t);
};

#endif
