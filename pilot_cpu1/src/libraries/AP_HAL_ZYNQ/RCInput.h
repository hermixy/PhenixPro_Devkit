/*
 * RCInput.h
 *
 *  Created on: 2016年7月27日
 *      Author: RST011
 */

#ifndef RCINPUT_H_
#define RCINPUT_H_

#include "AP_HAL_PX4.h"
#include "drv_rc_input.h"            //下层提供
#include "semphr.h"
#include "perf/perf_counter.h"


#ifndef RC_INPUT_MAX_CHANNELS
#define RC_INPUT_MAX_CHANNELS 18
#endif

class PX4::PX4RCInput : public AP_HAL::RCInput {
public:
    void init();
    bool new_input();
    uint8_t num_channels();
    uint16_t read(uint8_t ch);
    uint8_t read(uint16_t* periods, uint8_t len);

    bool set_overrides(int16_t *overrides, uint8_t len);
    bool set_override(uint8_t channel, int16_t override);
    void clear_overrides();

    void _timer_tick(void);

    bool rc_bind(int dsmMode);

private:
    /* override state */
    uint16_t _override[RC_INPUT_MAX_CHANNELS];
    struct rc_input_values _rcin;
    int _rc_sub;
    uint64_t _last_read;
    bool _override_valid;
    perf_counter_t _perf_rcin;
    SemaphoreHandle_t rcin_mutex;           //用SemaphoreHandle_t替换掉pthread_mutex_t
};



#endif /* RCINPUT_H_ */
