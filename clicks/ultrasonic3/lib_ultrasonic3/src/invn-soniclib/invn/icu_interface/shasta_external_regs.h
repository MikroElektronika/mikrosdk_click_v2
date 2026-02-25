//
// Created by rprzybyla on 5/6/2020.
//


#ifndef PROJECT_SHASTA_EXTERNAL_REGS_H
#define PROJECT_SHASTA_EXTERNAL_REGS_H

#include "stdint.h"
#include "shasta_pmut_instruction.h"
#include "shasta_atp_format.h"
#include "shasta_iq_format.h"
#include "icu_algo_info.h"

#define REG_FMT_MAJOR   (1)
#define REG_FMT_MINOR   (0)

#define LAST_MEASUREMENT_CONTINUOUS (0x80)
typedef struct raw_output_data{
    volatile uint16_t rtc_cal_result; //the raw result of the RTC calibration process
    volatile uint16_t pmut_clock_fcount; //the raw result of the PMUT3M clk frequency count process
    volatile uint16_t cpu_clock_fcount;//the raw result of the CPU clk frequency count process
    volatile uint8_t last_measurement;//the index of the latest measurement that has finished
    volatile uint8_t odr_out; //output ODR
    volatile uint8_t iq_output_format;//the format of the IQdata buffer (See IQ_OUTPUT_*)
    volatile int8_t reserved; //used for INTCONFIG_ON_TARGET; -1 by default if no algo present
    volatile uint16_t reserved2; // address to read IQ data from
    //! Number of IQ bytes in last measurement
    volatile uint16_t num_iq_bytes;
#ifndef INVN_NO_VIRTUAL_REGS
    // IQdata now defined by ASIC app layer. It is placed at the end of this
    // struct by specifying memory location at link step. For shared memory
    // usage, the host can reference the address of this field to get the correct
    // offset. This field is actually an array on the ASIC. Reference dev_ptr->current_fw->max_samples
    // to get the array size.
    volatile qi_t IQdata;
#endif
}raw_output_data_t;


#define INST_BUF_LENGTH (32)
#define ODR_BM ((uint8_t)7)
#define MEAS_FLAGS_SUPPRESS_DR_BM (0x01) // suppress the data ready interrupt
                                         // if this bit is set
#define MEAS_PERIOD_TIME_HOP_MASK (0xC000) // If bits set, time-hopping disabled

typedef struct measurement{ // size: 172 bytes
    volatile pmut_transceiver_inst_t trx_inst[32]; // 0x00
    volatile uint16_t meas_period; // 0x80 the number of RTC clock periods to wait between the start of this measurement and the next
    volatile uint8_t odr; // 0x82 the I/Q ODR for this measurement
    volatile uint8_t meas_flags; // various additional settings. see above
}measurement_t;


#define TRIGSRC_HWTRIGGER_INT1      (1<<0)
#define TRIGSRC_HWTRIGGER_INT2      (1<<1)
#define TRIGSRC_RTC                 (1<<2)
#define TRIGSRC_CONTINUOUS_RX        (1<<3)
#define TRIGSRC_MEMS_DIRECT_CONNECT  (1<<4)

#define INTCONFIG_DR_INT2       (1<<0) //if this bit is set, use int2 for DATAREADY
#define INTCONFIG_ON_TARGET     (1<<1) //if this bit is set, only output DATAREADY when a target is detected
#define INTCONFIG_PULSE_INT     (1<<2) //if this bit is set, pulse the configured INT rather than latch it til next SPI read
#define INTCONFIG_PUSH_PULL_INT (1<<3)  // if this bit is set, int will be actively driven high instead of using PU resistor

#define READOUT_OPTIONS_DOUBLE_BUFFER_BM (1)  // if set, double buffering mode is enabled
#define READOUT_OPTIONS_METADATA_IN_S0_BM (1<<1)  // if set, IQ buffer address and last_measurement idx will be placed in IQ sample 0
#define READOUT_OPTIONS_DATA_VALIDATION_BM (1<<7)  // if set, IQ data will be overwritten with incrementing counter values.

typedef struct measurement_queue{ // size: 142 bytes
    volatile uint8_t intconfig; // 0x02 switch interrupts to INT2 (see INTCONFIG_*)
    volatile uint8_t meas_start; // 0x03 which measurement do we start on
    volatile uint8_t meas_stop; // 0x04 which measurement do we stop on
    volatile uint8_t current_meas; // 0x05 which measurement do we do next
    volatile uint8_t trigsrc;// 0x06 add optional triggers from hardware pins (falling edge of INT1 or INT2) or LPWKUP timer (see TRIGSRC_*)
    volatile uint8_t reserved; // for double buffering and metadata packing options, as well as test data mode
    volatile measurement_t meas[MEAS_QUEUE_MAX_MEAS]; // 0x08 up to MEAS_QUEUE_MAX_MEAS measurements can be held at one time
}measurement_queue_t;


typedef struct test_result{//12 bytes
    uint16_t rtc_clock_frequency_Hz; //RTC clock frequency in Hz. If it reads 0xFFFF, it means the test result was not written
    uint16_t pmut_fcount; //The PMUT_CLK_3M frequency count result (allowing to convert range to TOF, and specifying the FT operating frequency)
    uint16_t range; //raw range
    uint16_t amplitude; //raw amplitude
    uint16_t pmut_code; //The PMUT_CLK_3M code used in the test
    uint8_t cpu_code;
    uint8_t reserved;
}test_result_t;

typedef struct serial_format{//10 bytes
    uint8_t production_site;
    uint8_t year_since_2000;
    uint8_t work_week;
    char lot[3];
    char serial_num[4];
}serial_format_t;

// TODO: OTP format related stuff should probably be pushed into libshasta

typedef enum {
    PRODUCT_ICU20201 = 1,
    PRODUCT_ICU10201 = 2,
    PRODUCT_ICU30201 = 3
} product_variant_t;

#define OTP_EXPECTED_MAJOR_VERSION (4)

typedef struct otp_copy{
    uint8_t otp_format_minor; //minor is updated when meaning of field(s) changes but the fields themselves are unchanged
    uint8_t otp_format_major; //major is udpated when fields are added, re-sized, or moved
    serial_format_t serial; //unique serial number tied to 2D barcode
    uint8_t product_variant; //e.g. ICU-20201=1, ICU-10201=2, ICU-30201=3
    uint8_t package_variant; //e.g. added microcap, changed bondwires
    uint8_t mems_variant; //e.g. CH101/201/CypressZ1/A1
    uint8_t module_variant; //e.g. Kelso, Joshua, etc (written at module test)
    uint8_t test_invalid_bitfield; //starting from the LSB, write a bit to 0 to indicate that test is valid
    uint8_t test_type_FT_bitfield; //starting from the LSB, write a bit to 0 to indicate that test is a module test
    test_result_t test[3]; //test results (that may be useful to the FW)
    uint16_t reserved[32-3-5-6*3-2]; //4 reserved words
}otp_copy_t;

#define OTP_EXT_CNTL_TEST_BM        (3)
#define OTP_EXT_CTRL_WR_STEP_BM    (0x000C)
#define OTP_EXT_CTRL_WR_STEP_BS     (2)
#define OTP_WR_STEP_NOT_STARTED     (0)
#define OTP_WR_STEP_START           (1)
#define OTP_WR_STEP_VPP_READY       (2)
#define OTP_WR_STEP_WR_DONE         (3)
typedef struct otp_data{
    uint16_t ext_cntl; //controls the write step or allows the read to be done in test mode (0=normal, 1=margin1, 2=margin2)
    otp_copy_t otp_copy; //holds a copy of the OTP. Write this before writing the OTP, or read this after triggering a read of the OTP
}otp_data_t;

#define CLK_CONTROL_PMUT_ON (1)
#define CLK_CONTROL_CPU_ON  (2)
#define CLK_CONTROL_WDT_ON  (4)
#define CLK_CONTROL_PW_BM   (15<<4)
#define CLK_CONTROL_PW_BS   (4)
#define CLK_CONTROL_PW_VAL  (0x5<<4)

typedef struct clock_control{ //controls for the clocks; size: 8 bytes
    uint8_t rtc_sources; // this sets the CLKMOD.RTC register when the EVENT_CONFIG_CLOCKS action is triggered
    uint8_t cpu_trim; // this sets the CLKMOD.CPU register when the EVENT_CONFIG_CLOCKS action is triggered
    uint16_t pmut_trim; // this sets the CLKMOD.PMUT (PMUT_3M clock) register when the EVENT_CONFIG_CLOCKS action is triggered
    uint16_t fcount_cycles; // controls how many RTC cycles the frequency count will use (uses fcount_cycles/16 for CPU fcount). Consumed when the EVENT_
    uint8_t control; // Can use this register to force on the CPU clock or PMUT_3M clock according to the CLK_CONTROL_* bits
    int8_t step; // Set this to a non-zero value when a frequency sweep is desired. Changes the CLKMOD.PMUT.pmut_trim by this amount each measurement (handling overflow), without affecting the bias bits
}clock_control_t;

typedef struct bist{
    volatile uint16_t fcount;
    volatile uint16_t pmut_clock_fn_code;
    volatile uint16_t sf;
    volatile uint16_t rd[2];
    volatile pmut_transceiver_inst_t tx_opt_cal_inst[5];
}bist_t;

//These define one-time events that the host will trigger on Shasta through the config.libshasta.event_trigger register
#define EVENT_SLEEP           (0)
#define EVENT_SW_TRIG         (1)
#define EVENT_MUT_FCOUNT      (2)
#define EVENT_CPU_FCOUNT      (4)
#define EVENT_BIST            (8)
#define EVENT_TX_OPTIMIZE     (16)
#define EVENT_RTC_CAL         (32)

#define EVENT_COPY_OTP_TO_RAM (128)

#define EVENT_PREPARE_MEAS    (512)
#define EVENT_SET_ATP_MODE    (1024)
#define EVENT_CONFIG_TRIGGER    (2048)
#define EVENT_CONFIG_CLOCKS     (4096)
#define EVENT_ALGO_INIT         (8192)

//These define interrupt flags that the Shasta will use to signal the source of a GPIO0 (INT1) data ready event from Shasta to the host
#define INT_SRC_NONE            (0)
#define INT_SRC_DATA_RDY        (1)
#define INT_SRC_MUT_FCOUNT_RDY  (2)
#define INT_SRC_CPU_FCOUNT_RDY  (4)
#define INT_SRC_BIST_RDY        (8)
#define INT_SRC_TX_OPTIMIZE     (16)
#define INT_SRC_RTC_CAL_RDY     (32)

#define INT_SRC_COPY_OTP_TO_RAM (128)
#define INT_SRC_OTP_WR_STEP     (256)
#define INT_SRC_WDT_EXPIRY      (1024)
#define INT_SRC_PGM_LOADED      (2048)
#define INT_SRC_ALGO_ERROR      (8192)
#define INT_SRC_DEBUG           (16384)
#define INT_SRC_ERROR           (32768U)

#define CURRENT_MEAS_BIST       (255)
#define CURRENT_MEAS_TXOPT      (254)

#define SHASTA_FIXED_CFG_ADDR     (0x1014)

typedef struct reg_map_format{
    uint8_t minor;
    uint8_t major;
    uint8_t rsvd1; // rsvd1/2 now hold the counter value for data validation mode
    uint8_t rsvd2;
}reg_map_format_t;

typedef struct common_regs{ // size: 16 bytes
    //TODO: signal which format is used for specific fw types (icu_presence, init, etc)
    reg_map_format_t reg_map_format; // constant that tells the driver what config version is used
    volatile  uint16_t int_source; // interrupt flags to tell the driver the source of a wakeup event; see INT_SRC_* above. Do not write. Cleared automatically
    volatile uint16_t active_events; // to tell the driver which events are active. Do not write. not currently implemented
    volatile uint16_t event_trigger; // way for driver to trigger an event to happen on Shasta; see EVENT_* above
    volatile clock_control_t clock; // clock control struct
}common_regs_t;

#define DEBUG_LEN (32)
typedef struct debug_{
    uint16_t len; //the length of the valid debug data (update by FW when debug data is written to the debug_array)
    uint16_t debug_array[DEBUG_LEN]; //array of debug data for readout by driver
}debug_t;

typedef struct shasta_config {
    volatile common_regs_t common; //common functions that generally would remain even if much of the rest of the interface were changed
    volatile measurement_queue_t meas_queue; //the meas_queue defines the behavior of the transceiver during a measurement, and the amount of time between measurements
    volatile bist_t bist; //intended to hold BIST data; not actually implemented yet
    const otp_data_t otp; //intended to hold a copy of the OTP contents; not actually implemented yet
    volatile atp_t atp; //to control the analog test pad functions
    volatile debug_t dbg; //a scratch pad for debug data that can be read by driver
    volatile raw_output_data_t raw; //the out struct defines the format of the data that should be read out when data is ready
} shasta_config_t;


#endif //PROJECT_SHASTA_EXTERNAL_REGS_H
