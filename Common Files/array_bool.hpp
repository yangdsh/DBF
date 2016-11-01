#ifndef __BF_ARRAY_BOOL_HPP__
#define __BF_ARRAY_BOOL_HPP__

#include "typefwd.hpp"

class array_bool_t;

class array_bool_t{
protected:
      uint8_t *array;
      uint32_t length;
public:
      array_bool_t(); 
      array_bool_t(uint32_t);
      array_bool_t(const array_bool_t &);
      array_bool_t &operator =(const array_bool_t &);
      ~array_bool_t();
      void setlength(uint32_t);
      void set(uint32_t, bool = 1);
      void flip(uint32_t);
      bool operator[](uint32_t);
      
      void clear();
};


#endif
