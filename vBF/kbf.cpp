#include "kbf.hpp"

#include "../Common Files/typefwd.hpp"

#include <cstdlib>
#include <ctime>

#include <vector>
using namespace std;

KBF :: KBF(uint32_t _w, uint32_t _k): k(_k){
#if (SET_NUM == 2) && defined(PROPORTION)
	wide[0] = (uint32_t)(_w * A_SET_PROPORTION);
	wide[1] = _w - wide[0];
#else
	for (uint8_t g = 0; g < MaxSetNum; ++g)
	  wide[g] = _w / MaxSetNum;
#endif
    for (uint8_t g = 0; g < MaxSetNum; ++g){
      bf[g].setlength(wide[g]);
      bf[g].clear();
    }
  
    BOBHash hashFunc;
    for (uint8_t g = 0; g < MaxSetNum; ++g){
	  hf[g].resize(k);	
	  for (uint32_t i = 0; i < k; ++i){
	    hashFunc.initialize(g * k + i);
        hf[g][i] = hashFunc;
      }
    }
	srand(time(NULL));
};

void KBF :: insert(uint8_t g, const unsigned char *data, uint32_t length){
	if (wide[g] == 0) return ;
    for (uint32_t i = 0; i < k; ++i){
	  uint32_t hash = hf[g][i].run(data, length) % wide[g];	
      bf[g].set(hash);
    }
}

int KBF :: search(const unsigned char *data, uint32_t length){
 /*   
    int r = -1;
    for (uint8_t g = 0; g < MaxSetNum; ++g){
      uint32_t s = 0;
      for (uint32_t i = 0; i < k; ++i)
        s += bf[g][hash[i]];
      if (s == k)
        if (r == -1) r = g; else return -1;
    }   
    return r;
*/
	static vector<uint8_t> Ans; Ans.clear();
    for (uint8_t g = 0; g < MaxSetNum; ++g)
	 if (wide[g] != 0){
	  uint32_t s = 0;
	  for (uint32_t i = 0; i < k; ++i){
	    uint32_t hash = hf[g][i].run(data, length) % wide[g];
	    s += bf[g][hash];
	  }
	  if (s == k) Ans.push_back(g);
     }
	if (uint8_t s = Ans.size())
	  return Ans[rand() % s];
	 else
	  return -1;
}
