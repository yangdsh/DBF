#include "djbf.hpp"

#include <cstdio> 
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <vector>
#include <algorithm>
using namespace std;

ID_t :: ID_t(uint8_t _gID, uint32_t _dID): gID(_gID), dID(_dID){
}

ID_t :: ID_t(const ID_t &that): gID(that.gID), dID(that.dID){
}

ID_t &ID_t :: operator =(const ID_t &that){
     gID = that.gID;
     dID = that.dID;
}

bool ID_t :: operator ==(const ID_t &that) const{
     return gID == that.gID && dID == that.dID;
}

bool ID_t :: operator !=(const ID_t &that) const{
     return gID != that.gID || dID != that.dID;
}

/*********************************************************************/

DJBF :: DJBF(uint32_t _w, uint32_t _k): wide(_w), k(_k){
    if (k < MaxSetNum) k = MaxSetNum;
    
    bf.setlength(wide);
    bf.clear();
    
    phase = PHASE_INSERT_ENUM;
    
    dataID.resize(wide);
    
    hf.resize(k);
    BOBHash hashFunc;
    for (uint32_t i = 0; i < k; ++i){
        hashFunc.initialize(i * 10);
        hf[i] = hashFunc;
    }
}

DJBF :: ~DJBF(){
}

int DJBF :: insert(uint8_t g, const unsigned char *data, uint32_t length){
    if (g >= MaxSetNum) return -1;
    rawData_t rd(data, length);
    dataSet[g].push_back(rd);
    if (phase != PHASE_INSERT_ENUM){
       ID_t ID(g, dataSet[g].size()-1);
       return bf_insert(ID);
    }
    return 0;
}

void DJBF :: getHashValue(const rawData_t &rd, uint32_t *hash){
     for (uint32_t i = 0; i < k; ++i){
         hash[i] = hf[i].run(rd.data, rd.length) % wide;
     }
}

void DJBF :: bf_clear(){
     bf.clear();
     
     for (uint32_t i = 0; i < wide; ++i)
         dataID[i].clear();
}

bool DJBF :: flip_bit(uint32_t p){
     if (dataID[p].size() >= 2) return 0;
     
     const ID_t &other_ID = *dataID[p].begin();
     static uint32_t *hash = new uint32_t[k];
     getHashValue(dataSet[other_ID.gID][other_ID.dID], hash);
     
     for (uint32_t i = 0; i < k; ++i)
         if (hash[i] != p && bf[hash[i]] != bf[p]){
             if (dataID[hash[i]].size() == 1){
                     bf.flip(hash[i]);
                     bf.flip(p);
                     return 1;
             }
         }
     return 0;
}

bool DJBF :: settle_flip_bit(const ID_t &ID, uint32_t p){
     vector<ID_t> :: iterator id;
     for (id = dataID[p].begin(); id != dataID[p].end(); ++id)
        if (id -> gID == 0) return 0;
     
     static uint32_t *hash = new uint32_t[k];
     for (id = dataID[p].begin(); id != dataID[p].end(); ++id)
      if (*id != ID)
      {
        getHashValue(dataSet[id -> gID][id -> dID], hash);
        uint32_t s = 0;
        for (uint32_t i = 0; i < k; ++i)
          s += bf[hash[i]];
  
        if ((s > k - id -> gID) == bf[p]) continue;

        uint32_t i;
        for (i = 0; i < k; ++i)
          if (bf[hash[i]] != bf[p])
            if (dataID[hash[i]].size() == 1){
              bf.flip(hash[i]);
              break;
            }
        if (i == k) break;
     }
     
     if (id == dataID[p].end()){
         bf.flip(p);
         return 1;
     } else {
         for (vector<ID_t> :: reverse_iterator jd(id); jd != dataID[p].rend(); ++jd)
          if (*jd != ID){
            getHashValue(dataSet[jd -> gID][jd -> dID], hash);
            uint32_t s = 0;
            for (uint32_t i = 0; i < k; ++i)
              s += bf[hash[i]];
            if ((s > k - jd -> gID) == bf[p]) continue;
            
            for (uint32_t i = 0; i < k; ++i)
              if (hash[i] != p && bf[hash[i]] == bf[p] && dataID[hash[i]].size() == 1){
                bf.flip(hash[i]);
                break;
              }
         }
         return 0;
     }
}

int DJBF :: bf_insert(const ID_t &ID){
    uint8_t g = ID.gID;
    
    static uint32_t *hash = new uint32_t[k];
    getHashValue(dataSet[g][ID.dID], hash);
    
    uint32_t s = 0;
    for (uint32_t i = 0; i < k; ++i)
        s += bf[hash[i]];
    
    if (s < k - g)
       for (uint32_t i = 0; i < k && s < k - g; ++i)
           if (dataID[hash[i]].size() == 0){
                 ++s;
                 bf.set(hash[i]);
           }
  
    if (s != k - g)
       for (uint32_t i = 0; i < k && s != k - g; ++i)
           if (bf[hash[i]] == s > k - g)
              if (s > k - g && s - 1 >= k - g)
                 s -= flip_bit(hash[i]);
              else if (s < k - g && s + 1 <= k - g)
                 s += flip_bit(hash[i]);

    if (s != k - g) return -1;
    
    for (uint32_t i = 0; i < k; ++i)
        dataID[hash[i]].push_back(ID);
    
    return 0;
}

void DJBF :: insert_finish(uint32_t *ins_fail){
     if (phase != PHASE_INSERT_ENUM) return ;
     phase = PHASE_SEARCH_ENUM;
     
     static uint32_t *hash = new uint32_t[k];
     for (uint8_t g = 0; g < MaxSetNum; ++g){
         for (uint32_t d = 0; d < dataSet[g].size(); ++d){
             ID_t ID(g, d);
             getHashValue(dataSet[g][d], hash);
             for (uint32_t i = 0; i < k; ++i){
                 bf.set(hash[i]);
                 dataID[hash[i]].push_back(ID);
             }
         }
     }
      
//     for (uint8_t g = 1; g < MaxSetNum; ++g) 
     for (uint8_t g = MaxSetNum-1; g; --g)
       for (uint32_t d = 0; d < dataSet[g].size(); ++d){
         getHashValue(dataSet[g][d], hash);
         uint32_t s = 0;
         for (uint32_t i = 0; i < k; ++i)
           s += bf[hash[i]];
         
         for (uint32_t i = 0; i < k - 1; ++i)
           for (uint32_t j = 0; j < k - i - 1; ++j)
             if (dataID[hash[j]].size() > dataID[hash[j+1]].size())
               swap(hash[j], hash[j+1]);
         
         for (uint32_t i = 0; i < k && s != k - g; ++i)
             if (bf[hash[i]] == (s > k - g))
              if (settle_flip_bit(ID_t(g, d), hash[i])){
                if (s < k - g) ++s; else --s;
             }
		 if (s != k - g) ++ins_fail[g];
       }
}

int DJBF :: search(const unsigned char *data, uint32_t length){
//    if (phase != DJBF :: PHASE_SEARCH_ENUM) return -1;
    
    uint32_t s = 0;
    for (uint32_t i = 0; i < k; ++i){
		uint32_t hash = hf[i].run(data, length) % wide;
		s += bf[hash];
	}
	
    if (s > k - MaxSetNum) return k - s;
    return -1;
}
