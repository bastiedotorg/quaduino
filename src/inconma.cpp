

#include "inconma.h"
#include "datatypes.h"
#include "database.h"



bool range_check_sint32(SINT32 r_max, SINT32 r_min, SINT32 value){
    return value >= r_min && value <= r_max;
}

bool range_check_uint32(UINT32 r_max, UINT32 r_min, UINT32 value){
    return value >= r_min && value <= r_max;
}

bool range_check_float64(FLOAT64 r_max, FLOAT64 r_min, FLOAT64 value){
    return value >= r_min && value <= r_max;
}

SINT32 scaling_sint32(SINT32 scale_factor, SINT32 value){
    return scale_factor * value;
}

UINT32 scaling_uint32(UINT32 scale_factor, UINT32 value){
    return scale_factor * value;
}

FLOAT64 scaling_float64(FLOAT64 scale_factor, FLOAT64 value){
    return scale_factor * value;
}

SINT32 offset_sin32(SINT32 offset, SINT32 value){
    return value + offset;
}

UINT32 offset_uint32(SINT32 offset, UINT32 value){
    SINT32 result = 0;
    result = value + offset;
    if (result<0){
        return 0;
    }else{
        return value + offset;
    }
}

FLOAT64 offset_float64(FLOAT64 offset, FLOAT64 value){
    return value + offset;
}