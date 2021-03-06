#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "AP_HAL_Namespace.h"
#include "AP_HAL_Boards.h"
#include "AP_HAL_Macros.h"
#include "AP_HAL_Main.h"

/* HAL Module Classes (all pure virtual) */
#include "UARTDriver.h"
#include "I2CDriver.h"
#include "SPIDriver.h"
#include "AnalogIn.h"
#include "Storage.h"
#include "GPIO.h"
#include "RCInput.h"
#include "RCOutput.h"
#include "Scheduler.h"
#include "Semaphores.h"
#include "Util.h"
#include "OpticalFlow.h"

#include "utility/Print.h"
#include "utility/Stream.h"
#include "utility/BetterStream.h"
#include "utility/functor.h"

/* HAL Class definition */
#include "HAL.h"

#include "system.h"


// zynq add head files
#include "pilot_print.h"
#include "fs/ioctl.h"
#include "FreeRTOS.h"

#define OK 0
#define ERROR -1
