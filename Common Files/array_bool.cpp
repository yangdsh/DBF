#include "typefwd.hpp"
#include "array_bool.hpp"

#include <cstring>

array_bool_t :: array_bool_t(){
             length = 0;
}

array_bool_t :: array_bool_t(uint32_t _n){
             length = (_n >> 3) + (bool)(_n & 7);
             if (length)
                array = new uint8_t[length];
}

array_bool_t :: array_bool_t(const array_bool_t &that): length(that.length){
             if (length){
                array = new uint8_t[length];
                memcpy(array, that.array, length * sizeof(uint8_t));
             }
}

array_bool_t &array_bool_t :: operator =(const array_bool_t &that){
             if (this == &that) return *this;
             if (length) delete []array;
             length = that.length;
             if (that.length){
                array = new uint8_t[that.length];
                memcpy(array, that.array, length * sizeof(uint8_t));
             }
             return *this;
}

array_bool_t :: ~array_bool_t(){
             if (length) delete []array;
}

void array_bool_t :: setlength(uint32_t _n){
     if (length){
        delete []array;
     }
     length = (_n >> 3) + (bool)(_n & 7);
     if (length){
        array = new uint8_t[length];
     }
}

void array_bool_t :: set(uint32_t pos, bool v){
     uint32_t p1 = pos >> 3;
     uint32_t p2 = pos & 7;
     array[p1] &= ~(1 << p2);
     array[p1] |= v << p2;
}

void array_bool_t :: flip(uint32_t pos){
     uint32_t p1 = pos >> 3;
     uint32_t p2 = pos & 7;
     array[p1] ^= (1 << p2);
}

bool array_bool_t :: operator[](uint32_t pos){
     //uint32_t p1 = pos >> 3;
     //uint32_t p2 = pos & 7;
     return array[pos>>3] & ((1 << (pos&7)));
}

void array_bool_t :: clear(){
     if (length)
        memset(array, 0, length * sizeof(uint8_t));
}
