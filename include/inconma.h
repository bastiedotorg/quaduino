//
// Created by bastie on 25.11.20.
//

#ifndef QUADIUNO_INCONMA_SENSOR_H
#define QUADIUNO_INCONMA_SENSOR_H

#include "datatypes.h"


bool range_check_sint32(SINT32 , SINT32, SINT32 );
bool range_check_uint32(UINT32 , UINT32 , UINT32 );
bool range_check_float64(FLOAT64 , FLOAT64 , FLOAT64 );

SINT32 scaling_sint32(SINT32 , SINT32 );
UINT32 scaling_uint32(UINT32 , UINT32 );
FLOAT64 scaling_float64(FLOAT64 , FLOAT64 );

SINT32 offset_sin32(SINT32 , SINT32 );
UINT32 offset_uint32(SINT32 , UINT32 );
FLOAT64 offset_float64(FLOAT64 , FLOAT64 );

#endif QUADIUNO_INCONMA_SENSOR_H


