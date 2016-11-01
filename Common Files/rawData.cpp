#include "rawData.hpp"

#include <cstring>

rawData_t :: rawData_t(){
          data = 0;
          length = 0;
}

rawData_t :: rawData_t(const rawData_t &that): length(that.length){
          data = new unsigned char[length];
          memcpy(data, that.data, length * sizeof(unsigned char));
}

rawData_t :: rawData_t(const unsigned char *_data, uint32_t _length): length(_length){
          data = new unsigned char[length];
          memcpy(data, _data, length * sizeof(unsigned char));
}

rawData_t &rawData_t :: operator =(const rawData_t &that){
          if (this == &that) return *this;
          if (data){
             delete []data;
             data = 0;
          }
          length = that.length;
          if (that.data){
             data = new unsigned char[length];
             memcpy(data, that.data, length * sizeof(unsigned char));
          }
          return *this;
}

rawData_t :: ~rawData_t(){
          if (data)
             delete []data;
}

void rawData_t :: setData(const unsigned char *_data, uint32_t _length){
     if (data){
        delete []data;
        data = 0;
     }
     length = _length;
     if (length){
        data = new unsigned char[length];
        memcpy(data, _data, length * sizeof(unsigned char));
     }
}