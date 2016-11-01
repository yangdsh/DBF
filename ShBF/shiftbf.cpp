#include "shiftbf.hpp"

#include "../Common Files/typefwd.hpp"

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <vector>
using namespace std;

uint32_t sbf_array_bool_t :: operator [](uint32_t pos){
	uint32_t p1 = pos >> 3;
	uint8_t p2 = pos & 7;
	
	uint32_t r = (uint32_t)array[p1] >> p2;
	
	uint8_t g = 8 - p2;
	if (g >= MaxSetNum) return r;
	
	for (; g + 8 < MaxSetNum; g += 8)
		r |= array[++p1] << g;
	
	r |= (uint32_t)array[++p1] << g;
	return r;
}

/*****************************************************************/

shiftBF :: shiftBF(uint32_t _w, uint32_t _k): wide(_w), k(_k){
    bf.setlength(wide + MaxSetNum - 1);
    bf.clear();
  
    BOBHash hashFunc;
    hf.resize(k);
    for (uint32_t i = 0; i < k; ++i){
      hashFunc.initialize(i * 10);
      hf[i] = hashFunc;
    }
	srand(time(NULL));
};

void shiftBF :: insert(uint8_t g, const unsigned char *data, uint32_t length){
    for (uint32_t i = 0; i < k; ++i){
	  uint32_t hash = hf[i].run(data, length) % wide;
      bf.set(hash + g);
    }
}

int shiftBF :: search(const unsigned char *data, uint32_t length){
    uint32_t r = ~0u;
    for (uint32_t i = 0; i < k; ++i){
		uint32_t hash = hf[i].run(data, length) % wide;
		r &= bf[hash];
	}
/*
	for (uint8_t g = 0; g < MaxSetNum; ++g)
	  if (r & (1 << g)) return g;
*/
	static vector<uint8_t> Ans; Ans.clear();
	for (uint8_t g = 0; g < MaxSetNum; ++g)
	 if (r & (1 << g)) Ans.push_back(g);
	if (uint8_t s = Ans.size())
		return Ans[rand() % s];
	 else
		return -1;
/*
    for (uint8_t g = 0; g < MaxSetNum; ++g){
      uint32_t s = 0;
 
      for (uint32_t i = 0; i < k; ++i)
        s += bf[hash[i] + g];
 
      if (s == k)
		return g;
    }
*/
 
    return -1;
}
