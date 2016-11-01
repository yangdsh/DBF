#ifndef __DJBF_CONFIG_HPP__
#define __DJBF_CONFIG_HPP__

#define SET_NUM		10	

#define DATA_SCALE	1

#define	BF_WIDE					((int)(289000000 * DATA_SCALE))
#define BF_HASH_FUNCTION_NUM	(10)

#define ELEM_START				((int)(0 * DATA_SCALE))
//#define ELEM_START				((int)(90000000 * DATA_SCALE))

#define SET_ELEM_CNT            ((int)(2000000 * DATA_SCALE))

#if (SET_NUM == 2)
//  #define PROPORTION
  #ifdef PROPORTION
    #define A_SET_PROPORTION	(0)
    #define A_SET_ELEM_CNT		((int)(2 * SET_ELEM_CNT * A_SET_PROPORTION))
    #define B_SET_ELEM_CNT		((int)(2 * SET_ELEM_CNT * (1 - A_SET_PROPORTION)))
  #else
    #define A_SET_ELEM_CNT		(SET_ELEM_CNT)
    #define B_SET_ELEM_CNT		(SET_ELEM_CNT)
  #endif
#endif

#define OUT_OF_SET_ELEM_CNT		((int)(3000000 * DATA_SCALE))

#endif
