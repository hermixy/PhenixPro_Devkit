#pragma once

#include "AP_HAL_PX4.h"
#include "uORB/topics/actuator_outputs.h"
#include "uORB/topics/actuator_armed.h"
#include "perf/perf_counter.h"

#include "pilot_print.h"

#define PX4_NUM_OUTPUT_CHANNELS 16

class PX4::PX4RCOutput : public AP_HAL::RCOutput 
{
public:
    void     init() override;
    void     set_freq(uint32_t chmask, uint16_t freq_hz) override;
    uint16_t get_freq(uint8_t ch) override;
    void     enable_ch(uint8_t ch) override;
    void     disable_ch(uint8_t ch) override;
    void     write(uint8_t ch, uint16_t period_us) override;
    uint16_t read(uint8_t ch) override;
    void     read(uint16_t* period_us, uint8_t len) override;
    uint16_t read_last_sent(uint8_t ch) override;
    void     read_last_sent(uint16_t* period_us, uint8_t len) override;
    void     set_safety_pwm(uint32_t chmask, uint16_t period_us) override;
    void     set_failsafe_pwm(uint32_t chmask, uint16_t period_us) override;
    bool     force_safety_on(void) override;
    void     force_safety_off(void) override;
    void     set_esc_scaling(uint16_t min_pwm, uint16_t max_pwm) override {
        _esc_pwm_min = min_pwm;
        _esc_pwm_max = max_pwm;
    }

    void _timer_tick(void);

private:
    int _pwm_fd;
    int _alt_fd;
    uint16_t _freq_hz;
    uint16_t _period[PX4_NUM_OUTPUT_CHANNELS];
    volatile uint8_t _max_channel;
    volatile bool _need_update;
    perf_counter_t  _perf_rcout;
    uint32_t _last_output;
    uint32_t _last_config_us;
    unsigned _servo_count;
    unsigned _alt_servo_count;
    uint32_t _rate_mask;
    uint16_t _enabled_channels;
    struct {
        int pwm_sub;
        actuator_outputs_s outputs;
    } _outputs[ORB_MULTI_MAX_INSTANCES] {};
    actuator_armed_s _armed;

    orb_advert_t _actuator_direct_pub = NULL;
    orb_advert_t _actuator_armed_pub = NULL;
    uint16_t _esc_pwm_min = 0;
    uint16_t _esc_pwm_max = 0;

    void _init_alt_channels(void);
    void _publish_actuators(void);
    void _arm_actuators(bool arm);
    void set_freq_fd(int fd, uint32_t chmask, uint16_t freq_hz);
};
