Code for DBF is in DBF.

Code for vBF is in vBF.

Code for ShBF is in ShBF

Code for experiments is in comparison

run the file ./comparison/compile_run.sh on bash to generate the data and do the experiment.

Please do the experiment in Linux environment.

If you want to change configures, please modify the configuration file: ./Common Files/config.hpp

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

The original input files are very large, so we provide sample input files by Gen_data.exe.
