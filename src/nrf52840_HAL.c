#include <nrf.h>
#include <stdbool.h>

#include "nrf52840_HAL.h"

static volatile int16_t result[MAX_ANALOG_INPUTS];
static bool pinSet[MAX_ANALOG_INPUTS] = {false, false, false, false, false, false, false, false};

static uint8_t convertInputToIndex(uint8_t input){
    int i;
    uint8_t ct = 0;
    for(i=0; i<sizeof(pinSet)/ sizeof(pinSet[0]); i++){
        if(pinSet[i]){
            if(i==input){
                return ct;
            }else{
                ct++;
            }
        }
    }

    return ct;
}

void setAnalog(uint8_t input){
    static bool baselineConfig = false;

    if(input > MAX_ANALOG_INPUTS){return;}

    if(pinSet[input]){return;}
    
    if(!baselineConfig){
        // Start HFCLK from crystal oscillator, this will give the SAADC higher accuracy
        NRF_CLOCK->TASKS_HFCLKSTART = 1;
        while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
        NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;

        // Configure the SAADC resolution.
        NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_10bit << SAADC_RESOLUTION_VAL_Pos;

        // Configure result to be put in RAM at the location of "result" variable.
        NRF_SAADC->RESULT.PTR = (uint32_t)&result[0];

        // No automatic sampling, will trigger with TASKS_SAMPLE.
        NRF_SAADC->SAMPLERATE = SAADC_SAMPLERATE_MODE_Task << SAADC_SAMPLERATE_MODE_Pos;

        // Enable SAADC
        NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Enabled << SAADC_ENABLE_ENABLE_Pos;

        // Calibrate the SAADC (only needs to be done once in a while)
        NRF_SAADC->TASKS_CALIBRATEOFFSET = 1;
        while (NRF_SAADC->EVENTS_CALIBRATEDONE == 0);
        NRF_SAADC->EVENTS_CALIBRATEDONE = 0;
        while (NRF_SAADC->STATUS == (SAADC_STATUS_STATUS_Busy <<SAADC_STATUS_STATUS_Pos));

        baselineConfig = true;
    }

    //  This array of flags keeps track of which pins have been set to Analog input
    //  This is needed because the data is written to RAM so that there are no spaces
    //  This means that if analog channel 0 and 5 are turned and and data is written
    //  The data will be placed at result[0] & result [1] and NOT result[0] & result[5]
    pinSet[input] = true;


    //  Sets the number of samplings.  convertInputToIndex will return the ct of setPins when set the it's upper limit (MAX_ANALOG_INPUTS-1)
    NRF_SAADC->RESULT.MAXCNT = convertInputToIndex(MAX_ANALOG_INPUTS);

    // Configure SAADC singled-ended channel, Internal reference (0.6V) and 1/6 gain.
    NRF_SAADC->CH[input].CONFIG = (SAADC_CH_CONFIG_GAIN_Gain1_6    << SAADC_CH_CONFIG_GAIN_Pos) |
                                (SAADC_CH_CONFIG_MODE_SE         << SAADC_CH_CONFIG_MODE_Pos) |
                                (SAADC_CH_CONFIG_REFSEL_Internal << SAADC_CH_CONFIG_REFSEL_Pos) |
                                (SAADC_CH_CONFIG_RESN_Bypass     << SAADC_CH_CONFIG_RESN_Pos) |
                                (SAADC_CH_CONFIG_RESP_Pulldown     << SAADC_CH_CONFIG_RESP_Pos) |
                                (SAADC_CH_CONFIG_TACQ_3us        << SAADC_CH_CONFIG_TACQ_Pos);

    // Configure the SAADC channel with VDD as positive input, no negative input(single ended).
    NRF_SAADC->CH[input].PSELN = SAADC_CH_PSELN_PSELN_NC << SAADC_CH_PSELN_PSELN_Pos;
    NRF_SAADC->CH[input].PSELP = (input + 1) << SAADC_CH_PSELP_PSELP_Pos;
}

void unsetAnalog(uint8_t input){
    if(input > MAX_ANALOG_INPUTS){return;}
    pinSet[input] = false;

    NRF_SAADC->CH[input].PSELP = SAADC_CH_PSELP_PSELP_NC << SAADC_CH_PSELP_PSELP_Pos;
    NRF_SAADC->CH[input].CONFIG = 0;

    //  Sets the number of samplings.  convertInputToIndex will return the ct of setPins when set the it's upper limit (MAX_ANALOG_INPUTS-1)
    NRF_SAADC->RESULT.MAXCNT = convertInputToIndex(MAX_ANALOG_INPUTS);
}

int readAnalog(uint8_t input){
    if(input > MAX_ANALOG_INPUTS){return 0;}

    if(!pinSet[input]){return 0;}


    // Start the SAADC and wait for the started event.
    NRF_SAADC->TASKS_START = 1;
    while (NRF_SAADC->EVENTS_STARTED == 0);
    NRF_SAADC->EVENTS_STARTED = 0;

    // Do a SAADC sample, will put the result in the configured RAM buffer.
    NRF_SAADC->TASKS_SAMPLE = 1;
    while (NRF_SAADC->EVENTS_END == 0);
    NRF_SAADC->EVENTS_END = 0;

    return result[convertInputToIndex(input)];
}