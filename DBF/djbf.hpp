#ifndef __DJBF_HPP__
#define __DJBF_HPP__

#include <vector>
using namespace std;

#include "../Common Files/config.hpp"
#include "../Common Files/typefwd.hpp"
#include "../Common Files/rawData.hpp"
#include "../Common Files/array_bool.hpp"
#include "../Common Files/BOBHash.hpp"

class ID_t;
class DJBF;

class ID_t{
public:
      uint8_t  gID;
      uint32_t dID;
      
      ID_t();
      ID_t(uint8_t, uint32_t);
      ID_t(const ID_t &);
      ID_t &operator =(const ID_t &);
      bool operator ==(const ID_t &) const;
      bool operator !=(const ID_t &) const;
};

class DJBF{
private:
      uint32_t wide;
      
      array_bool_t bf;
      
      enum {
           PHASE_INSERT_ENUM = 0,
           PHASE_SEARCH_ENUM = 1
      } phase;
      
      static const uint8_t MaxSetNum = SET_NUM;
      
      vector<rawData_t> dataSet[MaxSetNum];
      vector< vector<ID_t> > dataID;
      
      uint32_t k;
      vector<BOBHash> hf;
      
      DJBF();
      DJBF(const DJBF &);
      DJBF &operator =(const DJBF &);
      void bf_clear();
      bool flip_bit(uint32_t);
      bool settle_flip_bit(const ID_t &, uint32_t);
      int bf_insert(const ID_t &);

      void getHashValue(const rawData_t &, uint32_t *);
public:
      DJBF(uint32_t, uint32_t);
      ~DJBF();
      int insert(uint8_t, const unsigned char *, uint32_t);
      void insert_finish(uint32_t *);
      int search(const unsigned char *, uint32_t);
};

#endif

