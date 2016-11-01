#ifndef __BF_RAW_DATA_HPP__
#define __BF_RAW_DATA_HPP__

#include "typefwd.hpp"

class rawData_t;

class rawData_t{
public:
      unsigned char *data;
      uint32_t length;
      
      rawData_t();
      rawData_t(const rawData_t &);
      rawData_t(const unsigned char *, uint32_t);
      rawData_t &operator =(const rawData_t &);
      ~rawData_t();
      
      void setData(const unsigned char *, uint32_t);
};

#endif
