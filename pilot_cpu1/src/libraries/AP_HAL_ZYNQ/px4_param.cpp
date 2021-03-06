/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
  This replaces the PX4Firmware parameter system with dummy
  functions. The ArduPilot parameter system uses different formatting
  for FRAM and we need to ensure that the PX4 parameter system doesn't
  try to access FRAM in an invalid manner
 */

#include <AP_HAL/AP_HAL.h>

#include <stdio.h>

#include "param.h"

#include "uORB/uORB.h"
#include "uORB/topics/parameter_update.h"

/** parameter update topic */
ORB_DEFINE(parameter_update, struct parameter_update_s);

param_t param_find(const char *name)
{
    ::printf("PX4: param_find(%s)\n", name);
    return PARAM_INVALID;
}

int param_get(param_t param, void *val)
{
    return -1;
}

int param_set(param_t param, const void *val)
{
    return -1;
}

