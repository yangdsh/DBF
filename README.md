# 4colorclassifier
## What is this?
This is the source code of our research paper accepted by ICC 2017. In this paper, we propose a new data structure named ***Difference Bloom filter***, which is a probabilistic data structure for multi-set query.
Experiments and mathematical analysis show that it has higher accuracy and faster query speed than the state-of-the-art. 
## Content
We implement the Difference Bloom filter (DBF), the Multiple Bloom filter (vBF), and the shifting Bloom filter (ShBF) in C++. We use BOB hashing as the hashing functions. Code for DBF is in folder 'DBF'. Code for vBF is in folder 'vBF'. Code for ShBF is in folder 'ShBF'. Code for experiments is in folder 'comparison'.
## How to run it?
Please run those codes in Linux environment.
```makefile
./comparison/compile_run.sh
```
## How to change parameters?
If you want to change configures, please modify the configuration file: */Common Files/config.hpp*
```makefile
  SET_NUM: defines the number of set(s). It should never exceed 32.
  DATA_SCALE: controls the input data scale on proportionn
  BF_WIDE: defines the number of bits used by these filters.
  BF_HASH_FUNCTION_NUM: defines the number of hash functions used in these filters. It should be greater than SET_NUM.
  ELEM_START: defines the first element of the first data set.  
  SET_ELEM_CNT: defines the size of the data set.(how many numbers are contained)
  PROPORTION: if SET_NUM equals to 2, this macro controls that whether the two sets should contain different proportion of the complete data set.
  A_SET_PROPORTION: if SET_NUM equals to 2 and PROPORTION is set, this macro defines the percentage of the size of the first set in the complete data set. It should be ranged into [0, 1].
  A_SET_ELEM_CNT: if SET_NUM equals to 2, this macro gives the size of the first data set.
  B_SET_ELEM_CNT: if SET_NUM equals to 2, this macro gives the size of the second data set.
```
