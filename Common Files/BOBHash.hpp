#ifndef __BF_BOB_HASH_HPP_
#define __BF_BOB_HASH_HPP_

#include "typefwd.hpp"

class BOBHash;

class BOBHash{
public:
      BOBHash();
	    BOBHash(uint32_t primeNum);

	    void initialize(uint32_t primeNum);

	    uint32_t run(const unsigned char *str, uint32_t len) const;

private:
	    uint32_t primeNum;
};

extern const uint32_t MaxPrimeCnt;

#endif

