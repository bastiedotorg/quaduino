

#include "inconma.h"
#include "datatypes.h"
#include "database.h"


/**
 * checks if a value is within a predefined interval or not
 *
 * @param r_max Upper limit for allowed range for value
 * @param r_min Lower limit for allowed range for value
 * @param value SINT32 value to be checked
 * @return true if value is within the range and false if its outside
 */
bool range_check_sint32(SINT32 r_max, SINT32 r_min, SINT32 value){
    return value >= r_min && value <= r_max;
}


/**
 * checks if a value is within a predefined interval or not
 *
 * @param r_max Upper limit for allowed range for value
 * @param r_min Lower limit for allowed range for value
 * @param value UINT32 value to be checked
 * @return true if value is within the range and false if its outside
 */
bool range_check_uint32(UINT32 r_max, UINT32 r_min, UINT32 value){
    return value >= r_min && value <= r_max;
}


/**
 * checks if a value is within a predefined interval or not
 *
 * @param r_max Upper limit for the allowed range for value
 * @param r_min Lower limit for the allowed range for value
 * @param value FLOAT64 value to be checked
 * @return true if value is within the range and false if its outside
 */
bool range_check_float64(FLOAT64 r_max, FLOAT64 r_min, FLOAT64 value){
    return value >= r_min && value <= r_max;
}


/**
 * scales a SINT32 value with a scale factor (e.g. from m/s to km/h)
 *
 * @param scale_factor SINT32 scale factor (e.g. 3.6 to scale from m/s to km/h)
 * @param value SINT32 value to be scaled
 * @return scaled SINT32 value
 */
SINT32 scaling_sint32(SINT32 scale_factor, SINT32 value){
    return scale_factor * value;
}

/**
 * scales a UINT32 value with a scale factor (e.g. from m/s to km/h)
 *
 * @param scale_factor UINT32 scale factor (e.g. 3.6 to scale from m/s to km/h)
 * @param value UINT32 value to be scaled
 * @return scaled UINT32 value
 */
UINT32 scaling_uint32(UINT32 scale_factor, UINT32 value){
    return scale_factor * value;
}

/**
 * scales a FLOAT64 value with a scale factor (e.g. from m/s to km/h)
 *
 * @param scale_factor FLOAT64 scale factor (e.g. 3.6 to scale from m/s to km/h)
 * @param value FLOAT64 value to be scaled
 * @return scaled FLOAT64 value
 */
FLOAT64 scaling_float64(FLOAT64 scale_factor, FLOAT64 value){
    return scale_factor * value;
}

/**
 * applies an offset to an SINT32 value
 *
 * @param offset SINT32 offset to value
 * @param value SINT32
 * @return SINT32
 */
SINT32 offset_sin32(SINT32 offset, SINT32 value){
    return value + offset;
}

/**
 * applies an offset to an UINT32 value and checks if the result is not less than zero
 *
 * @param offset SINT32 offset to value
 * @param value UINT32 value
 * @return if the result is bigger than 0 the result will be returned otherwise 0 will be returned
 */
UINT32 offset_uint32(SINT32 offset, UINT32 value){
    SINT32 result = 0;
    result = value + offset;
    if (result<0){
        return 0;
    }else{
        return value + offset;
    }
}

/**
 * applies an offset to an FLOAT64 value
 *
 * @param offset FLOAT64 offset to value
 * @param value FLOAT64 value
 * @return
 */
FLOAT64 offset_float64(FLOAT64 offset, FLOAT64 value){
    return value + offset;
}