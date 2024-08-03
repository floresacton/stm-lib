#ifndef CONFIG_MEMORY_CONF_H_
#define CONFIG_MEMORY_CONF_H_

#define MEMORY_BYTES  4 //including MemHash
#define MEMORY_SHORTS 8
#define MEMORY_INTS   0
#define MEMORY_FLOATS 2

//Change to reset memory on upload
#define MEMORY_HASH 19

//T(name, default value) -> enum Mem+name
#define MEMORY_BYTE_LIST T(Tach1Spokes, 10) T(Tach2Spokes, 10) T(Tach3Spokes, 10)
#define MEMORY_SHORT_LIST T(MinRpm, 20) T(AuxThresh, 1000) T(Tach1Max, 10000) T(Tach2Max, 10000) T(Tach3Max, 10000)\
T(Tach1Thresh, 2048) T(Tach2Thresh, 2048) T(Tach3Thresh, 2048)
#define MEMORY_INT_LIST
#define MEMORY_FLOAT_LIST T(GpsTire, 53.4) T(SlipThresh, 10.0)

#endif
