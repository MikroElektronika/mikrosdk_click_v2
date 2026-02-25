/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file ultrasonic3.c
 * @brief Ultrasonic 3 Click Driver.
 */

#include "ultrasonic3.h"
#include "invn/soniclib/ch_log.h"
#include "invn/soniclib/soniclib.h"
#include "invn/soniclib/sensor_fw/icu_gpt/icu_gpt.h"
#include "bsp.h"
#include "app_config.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/* Bit flags used in main loop to check for completion of sensor I/O.  */
#define DATA_READY_FLAG ( 1 )

/* chirp_data_t - Structure to hold measurement data for one sensor
 *   This structure is used to hold the data from one measurement cycle from
 *   a sensor.  The data values include the measured range, the ultrasonic
 *   signal amplitude, the number of valid samples  in the measurement, and
 *   (optionally) the full amplitude data or raw I/Q data
 *   from the measurement.
 *
 *  The format of this data structure is specific to this example application, so
 *  you may change it as desired.
 *
 *  A "chirp_data[]" array of these structures, one for each possible sensor,
 *  is declared in the main.c file.  The sensor's device number is
 *  used to index the array.
 */
typedef struct 
{
    uint8_t rx_sensor_num;  // receiving sensor number
    uint8_t tx_sensor_num;  // transmitting sensor number
    uint32_t range;         // from ch_get_range()
    uint16_t amplitude;     // from ch_get_amplitude()
    uint16_t num_samples;   // from ch_get_num_samples()

} chirp_data_t;

/* Detection level settings
 *   This structure is passed to the icu_gpt_algo_configure() function to set the target
 *   detection thresholds.  Each threshold entry consists of a starting sample
 *   number and a threshold amplitude level.  The values are defined in app_config.h.
 */
ch_thresholds_t chirp_detect_thresholds = 
{
    .threshold = 
    {
        { CHIRP_THRESH_0_START, CHIRP_THRESH_0_LEVEL }, /* threshold 0 */
        { CHIRP_THRESH_1_START, CHIRP_THRESH_1_LEVEL }, /* threshold 1 */
        { CHIRP_THRESH_2_START, CHIRP_THRESH_2_LEVEL }, /* threshold 2 */
        { CHIRP_THRESH_3_START, CHIRP_THRESH_3_LEVEL }, /* threshold 3 */
        { CHIRP_THRESH_4_START, CHIRP_THRESH_4_LEVEL }, /* threshold 4 */
        { CHIRP_THRESH_5_START, CHIRP_THRESH_5_LEVEL }, /* threshold 5 */
        { CHIRP_THRESH_6_START, CHIRP_THRESH_6_LEVEL }, /* threshold 6 */
        { CHIRP_THRESH_7_START, CHIRP_THRESH_7_LEVEL }, /* threshold 7 */
    }
};
ch_thresholds_t *chirp_detect_thresholds_ptr = &chirp_detect_thresholds;

/* Measurement configuration struct - starting/default values */
static ch_meas_config_t meas_config = 
{
    .odr         = CHIRP_SENSOR_ODR,
    .meas_period = 0,
};

static icu_gpt_algo_config_t algo_config = 
{
    .num_ranges              = CHIRP_MAX_TARGETS,
    .ringdown_cancel_samples = 20,
    .static_filter_samples   = 0,            // may be changed later using ch_set_static_range()
    .iq_output_format        = CH_OUTPUT_IQ, /* return (Q, I) */
    .filter_update_interval  = 0,            /* update filter every sample */
};

InvnAlgoRangeFinderConfig gpt_algo_instance[ CHIRP_MAX_NUM_SENSORS ];

/* Array of structs to hold measurement data, one for each possible device */
chirp_data_t chirp_data[ CHIRP_MAX_NUM_SENSORS ];

/* Array of ch_dev_t device descriptors, one for each possible device */
static ch_dev_t chirp_devices[ CHIRP_MAX_NUM_SENSORS ];

/* Descriptor structure for group of sensors */
ch_group_t chirp_group;

/* Task flag word
 *   This variable contains the DATA_READY_FLAG bit flag that are set in interrupt callback routines.
 *   The flag is checked in the loop and, if set, will cause an appropriate function to
 *   be called to process sensor data.
 */
volatile uint32_t task_flags = 0;

/* Device tracking variables
 *   These are bit-field variables which contain a separate bit assigned to
 *   each (possible) sensor, indexed by the device number.  The active_devices
 *   variable contains the bit pattern describing which ports have active
 *   sensors connected.  The data_ready_devices variable is set bit-by-bit
 *   as sensors interrupt, indicating they have completed a measurement
 *   cycle.  The two variables are compared to determine when all active
 *   devices have interrupted.
 */
static uint32_t active_devices;
static uint32_t data_ready_devices;

/* Number of connected sensors */
static uint8_t num_connected_sensors = 0;

/* Number of sensors that use external triggering to start measurement */
static uint8_t num_triggered_sensors = 0;

extern uint8_t icu_init_init ( ch_dev_t *dev_ptr, fw_info_t **fw_info );

/* Forward declarations */
static uint8_t configure_sensors ( ch_group_t *grp_ptr, uint8_t num_ports, uint32_t *active_devices_ptr,
                                   uint8_t *num_connected_ptr, uint8_t *num_triggered_ptr );
static uint8_t handle_data_ready ( ch_group_t *grp_ptr );
static void sensor_int_callback ( ch_group_t *grp_ptr, uint8_t dev_num, ch_interrupt_type_t int_type );

static void display_algo_output ( ch_dev_t *dev_ptr, uint8_t dev_num );

ch_group_t *grp_ptr;  // pointer to group descriptor
ch_dev_t *dev_ptr;    // pointer to individual device descriptor
uint8_t num_ports;
uint8_t dev_num;

void ultrasonic3_cfg_setup ( ultrasonic3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->dev_pwm_freq = ULTRASONIC3_PWM_DEF_FREQ;
}

err_t ultrasonic3_init ( ultrasonic3_t *ctx, ultrasonic3_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );
    
    ultrasonic3_set_duty_cycle ( ctx, ULTRASONIC3_PWM_DEF_DC );
    ctx->int_pin_name = cfg->int_pin;

    return SPI_MASTER_SUCCESS;
}

err_t ultrasonic3_default_cfg ( ultrasonic3_t *ctx ) 
{
    err_t error_flag = ULTRASONIC3_OK;
    
    /* Initialize board hardware functions */
    grp_ptr = &chirp_group;
    chbsp_init ( grp_ptr, ctx );

    CH_LOG_APP( "Hello Chirp! - SonicLib Example Application for ICU Sensors" );
    CH_LOG_APP( "    Compile time:  %s %s", __DATE__, __TIME__ );
    CH_LOG_APP( "    SonicLib version: %u.%u.%u%s", SONICLIB_VER_MAJOR, SONICLIB_VER_MINOR, 
                                                    SONICLIB_VER_REV, SONICLIB_VER_SUFFIX );

    ch_group_init ( &chirp_group, CHIRP_MAX_NUM_SENSORS, CHIRP_NUM_BUSES, CHIRP_RTC_CAL_PULSE_MS );

    /* Get the number of (possible) sensor devices on the board */
    num_ports = ch_get_num_ports ( grp_ptr );

    /* Initialize sensor descriptors.
     *   This loop initializes each (possible) sensor's ch_dev_t descriptor,
     *   although we don't yet know if a sensor is actually connected.
     *
     *   The call to ch_init() specifies the sensor descriptor, the sensor group
     *   it will be added to, the device number within the group, and the sensor
     *   firmware initialization routine that will be used.
     */
    CH_LOG_APP( "Initializing sensor(s)... " );

    for ( dev_num = 0; dev_num < num_ports; dev_num++ ) 
    {
        dev_ptr = &( chirp_devices[ dev_num ] );    // Init struct in array
        error_flag |= ch_init ( dev_ptr, grp_ptr, dev_num, icu_gpt_init );
        error_flag |= ch_set_init_firmware ( dev_ptr, icu_init_init );
    }

    /* Start all sensors.
     *   The ch_group_start() function will search each port (that was
     *   initialized above) for a sensor. If it finds one, it programs it (with
     *   the firmware specified above during ch_init()) and waits for it to
     *   perform a self-calibration step.  Then, once it has found all the
     *   sensors, ch_group_start() completes a timing reference calibration by
     *   applying a pulse of known length to the sensor's INT line.
     */
    if ( error_flag == 0 ) 
    {
        CH_LOG_APP_START( "starting group... " );
        error_flag = ch_group_start ( grp_ptr );
    }

    if ( error_flag == 0 ) 
    {
        CH_LOG_APP_MSG( "OK" );
    }
    else
    {
        CH_LOG_APP_MSG( "FAILED: %d", error_flag );
    }
    CH_LOG_APP_END( );

#if IS_CH_LOG_USED
    /* Get and display the initialization results for each connected sensor.
     *   This loop checks each device number in the sensor group to determine
     *   if a sensor is actually connected.  If so, it makes a series of
     *   function calls to get different operating values, including the
     *   operating frequency, clock calibration values, and firmware version.
     */
    ch_extra_display_init_info ( grp_ptr );
#endif

    /* Register callback function to be called when Chirp sensor interrupts */
    ch_io_int_callback_set ( grp_ptr, sensor_int_callback );

    /* Configure each sensor with its operating parameters */
    error_flag = configure_sensors ( grp_ptr, num_ports, &active_devices, &num_connected_sensors, &num_triggered_sensors );

    if ( !error_flag )
    {
        CH_LOG_APP ( "Starting measurements..." );
    }

    return error_flag;
}

err_t ultrasonic3_set_duty_cycle ( ultrasonic3_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t ultrasonic3_pwm_stop ( ultrasonic3_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t ultrasonic3_pwm_start ( ultrasonic3_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void ultrasonic3_get_measurements ( void )
{
    if ( ( CHIRP_TRIGGER_TYPE == CH_TRIGGER_TYPE_HW ) && ( num_triggered_sensors > 0 ) )
    {
        ch_group_trigger ( &chirp_group );
    }
    else if ( CHIRP_TRIGGER_TYPE == CH_TRIGGER_TYPE_SW ) 
    {
        for ( dev_num = 0; dev_num < num_ports; dev_num++ )
        {
            dev_ptr = ch_get_dev_ptr ( grp_ptr, dev_num );
            if ( ch_sensor_is_connected ( dev_ptr ) )
            {
                ch_trigger_soft ( dev_ptr );
            }
        }
    }

    /* Check for sensor data-ready interrupt(s) */
    if ( task_flags & DATA_READY_FLAG )
    {
        /* All sensors have interrupted - handle sensor data */
        task_flags &= ~DATA_READY_FLAG; // clear flag
        handle_data_ready ( grp_ptr );  // read and display measurement
    }
}

/*
 * configure_sensors() - apply configuration settings
 *
 * This function performs the detailed configuration of the sensor, including
 * definition of the measurement and selecting various optional features.
 * Values defined in the app_config.h file are used here as parameters to
 * individual SonicLib API functions.
 */
uint8_t configure_sensors( ch_group_t *grp_ptr,           // pointer to sensor group
                           uint8_t num_ports,             // number of possible sensors on board
                           uint32_t *active_devices_ptr,  // pointer to active devices tracking var
                           uint8_t *num_connected_ptr,    // pointer to count of connected devices
                           uint8_t *num_triggered_ptr )   // pointer to count of triggered devices
{
    ch_dev_t *dev_ptr;
    ch_mode_t mode;
    uint8_t dev_num;
    err_t error_flag;
    uint8_t first_connected_num = 0;
#if IS_CH_LOG_USED
    char const *mode_string = "";
#endif

    error_flag         = 0;
    *num_connected_ptr  = 0;
    *active_devices_ptr = 0;

    /* Set configuration values for each connected sensor */
    for ( dev_num = 0; dev_num < num_ports; dev_num++ ) 
    {
        dev_ptr = ch_get_dev_ptr( grp_ptr, dev_num );       // get this device's ch_dev_t addr

        if ( ch_sensor_is_connected( dev_ptr ) )
        {
            CH_LOG_APP( "Configuring Device %u...", dev_num );

            ( *num_connected_ptr )++;                       // count one more connected sensor
            ( *active_devices_ptr ) |= ( 1 << dev_num );    // add to active device bit mask

            if ( 1 == *num_connected_ptr )
            {
                mode                = CHIRP_FIRST_SENSOR_MODE;
                first_connected_num = dev_num;
            } 
            else
            {
                mode = CHIRP_OTHER_SENSOR_MODE;
            }

#if IS_CH_LOG_USED
            switch ( mode ) 
            {
                case CH_MODE_FREERUN:
                {
                    mode_string = "CH_MODE_FREERUN";
                    break;
                }
                case CH_MODE_TRIGGERED_TX_RX:
                {
                    mode_string = "CH_MODE_TRIGGERED_TX_RX";
                    break;
                }
                case CH_MODE_TRIGGERED_RX_ONLY:
                {
                    mode_string = "CH_MODE_TRIGGERED_RX_ONLY";
                    break;
                }
                case CH_MODE_IDLE:
                {
                    mode_string = "CH_MODE_IDLE";
                    break;
                }
                case CH_MODE_CONTINUOUS_RX:
                {
                    mode_string = "CH_MODE_CONTINUOUS_RX";
                    break;
                }
                default:
                {
                    error_flag = 1;  // bad mode specified in app_config.h
                    CH_LOG_ERR( "ERROR - bad sensor mode %d", mode );
                    break;
                }
            }
#endif
            /* Initialize application structure(s) to hold measurement data */
            if ( !error_flag ) 
            {
                chirp_data[ dev_num ].rx_sensor_num = dev_num;      // this will be the receiving sensor
                if ( CH_MODE_TRIGGERED_RX_ONLY == mode )
                {
                    chirp_data[ dev_num ].tx_sensor_num = first_connected_num;  // first sensor will transmit
                }
                else
                {
                    chirp_data[ dev_num ].tx_sensor_num = dev_num;  // this sensor will transmit
                }
            }

            /* Initialize algorithm on sensor */
            if ( !error_flag )
            {
                error_flag = icu_gpt_algo_init( dev_ptr, &gpt_algo_instance[ dev_num ] );
            }

            /* Initialize measurement */
            if ( !error_flag )
            {
                CH_LOG_APP_START( "  Initializing measurement %d... ", CH_DEFAULT_MEAS_NUM );
                error_flag  = ch_meas_init( dev_ptr, CH_DEFAULT_MEAS_NUM, &meas_config, NULL );
                error_flag |= icu_gpt_algo_configure( dev_ptr, CH_DEFAULT_MEAS_NUM, &algo_config, chirp_detect_thresholds_ptr );
                if ( !error_flag && CH_MODE_CONTINUOUS_RX == mode )
                {
                    // initialize the other meas config since both are used in continuous rx
                    error_flag  = ch_meas_init( dev_ptr, ( CH_DEFAULT_MEAS_NUM + 1 ) % 2, &meas_config, NULL );
                    error_flag |= icu_gpt_algo_configure( dev_ptr, ( CH_DEFAULT_MEAS_NUM + 1 ) % 2, &algo_config,
                                                           chirp_detect_thresholds_ptr );
                }
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            /* Add transmit segment unless rx-only */
            if ( !error_flag )
            {
                if ( CH_MODE_TRIGGERED_RX_ONLY != mode && CH_MODE_CONTINUOUS_RX != mode )
                {
                    CH_LOG_APP_START( "  Adding tx segment... " );
                    error_flag = ch_meas_add_segment_tx( dev_ptr, CH_DEFAULT_MEAS_NUM, CHIRP_TX_SEG_CYCLES, 
                                                          CHIRP_TX_SEG_PULSE_WIDTH, CHIRP_TX_SEG_PHASE, CHIRP_TX_SEG_INT_EN );
                }
                else
                {
                    CH_LOG_APP_START( "  Adding count (delay) segment to match Tx sensor... " );
                    error_flag = ch_meas_add_segment_count( dev_ptr, CH_DEFAULT_MEAS_NUM, CHIRP_TX_SEG_CYCLES, 0 );
                }
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            /* Add first receive segment for very early part of measurement */
            if ( !error_flag )
            {
                CH_LOG_APP_START( "  Adding rx segment 0... " );
                error_flag = ch_meas_add_segment_rx( dev_ptr, CH_DEFAULT_MEAS_NUM, CHIRP_RX_SEG_0_SAMPLES, 
                                                      CHIRP_RX_SEG_0_GAIN_REDUCE, CHIRP_RX_SEG_0_ATTEN, CHIRP_RX_SEG_0_INT_EN );
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            /* Add second receive segment for remainder of measurement */
            if ( !error_flag )
            {
                CH_LOG_APP_START( "  Adding rx segment 1... " );
                error_flag = ch_meas_add_segment_rx( dev_ptr, CH_DEFAULT_MEAS_NUM, CHIRP_RX_SEG_1_SAMPLES,
                                                      CHIRP_RX_SEG_1_GAIN_REDUCE, CHIRP_RX_SEG_1_ATTEN, CHIRP_RX_SEG_1_INT_EN );
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            /* Write complete meas config (measurement queue) to device */
            if ( !error_flag )
            {
                CH_LOG_APP_START( "  Writing meas queue... " );
                error_flag = ch_meas_write_config( dev_ptr );
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            /* Optimize measurement segments, if specified */
            if ( !error_flag && CHIRP_MEAS_OPTIMIZE )
            {
                CH_LOG_APP_START( "  Optimizing measurement segments... " );
                error_flag = ch_meas_optimize( dev_ptr, NULL, NULL );
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            if ( !error_flag )
            {
                /* Write algo config to sensor */
                error_flag = ch_set_algo_config( dev_ptr, &gpt_algo_instance[ dev_num ] );
            }
            /* Set sensing range based on sensor model - this can change the total
             * number of rx samples set during ch_meas_add_segment_rx() above.
             */
            if ( !error_flag )
            {
                uint16_t max_range   = 0;
                uint16_t part_number = ch_get_part_number( dev_ptr );

                if ( ICU30201_PART_NUMBER == part_number )
                {
                    max_range = CHIRP_ICU30201_MAX_RANGE_MM;
                }
                else if ( ICU10201_PART_NUMBER == part_number )
                {
                    max_range = CHIRP_ICU10201_MAX_RANGE_MM;
                }
                else
                {
                    max_range = CHIRP_ICU20201_MAX_RANGE_MM;
                }
                CH_LOG_APP_START( "  Setting max range to %u mm... ", max_range );
                error_flag = ch_meas_set_max_range( dev_ptr, CH_DEFAULT_MEAS_NUM, max_range );
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }
            /* Set static target rejection range, if specified */
            if ( !error_flag && ( 0 != CHIRP_STATIC_REJECT_SAMPLES ) )
            {
                CH_LOG_APP_START( "  Setting static target rejection (%u samples)... ", CHIRP_STATIC_REJECT_SAMPLES );
                error_flag = icu_gpt_set_static_filter( dev_ptr, CH_DEFAULT_MEAS_NUM, CHIRP_STATIC_REJECT_SAMPLES );
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            /* Set rx holdoff, if specified */
            if ( !error_flag && ( 0 != CHIRP_RX_HOLDOFF_SAMPLES ) )
            {
                CH_LOG_APP_START( "  Setting rx holdoff (%u samples)... ", CHIRP_RX_HOLDOFF_SAMPLES );
                error_flag = icu_gpt_set_rx_holdoff( dev_ptr, CH_DEFAULT_MEAS_NUM, CHIRP_RX_HOLDOFF_SAMPLES );
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            /* Enable target interrupt filtering, if specified */
            if ( !error_flag && CHIRP_TARGET_INT_FILTER )
            {
                CH_LOG_APP_START( "  Enabling target interrupt filtering... " );
                error_flag = ch_set_target_interrupt( dev_ptr, CH_TGT_INT_FILTER_ANY );
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            if ( !error_flag && ( CH_MODE_CONTINUOUS_RX == mode ) )
            {
                // pulsed interrupt mode required in continuous modes
                ch_set_interrupt_mode( dev_ptr, CH_INTERRUPT_MODE_PULSE );
            }

            /* Enable software triggering if selected */
            if ( !error_flag && ( CHIRP_TRIGGER_TYPE == CH_TRIGGER_TYPE_SW ) )
            {
                CH_LOG_APP_START( "  Enabling soft triggering... " );
                ch_set_trigger_type( dev_ptr, CH_TRIGGER_TYPE_SW );
                CH_LOG_APP_MSG( "OK" );
                CH_LOG_APP_END( );
            }

            if ( !error_flag )
            {
                /* If sensor will be free-running, set internal sample interval */
                if ( CH_MODE_FREERUN == mode )
                {
                    ch_set_freerun_interval(dev_ptr, MEASUREMENT_INTERVAL_MS);
                }
                else if ( CH_MODE_CONTINUOUS_RX == mode )
                {
                    // do nothing
                } 
                else
                {
                    ( *num_triggered_ptr )++;  // count one more triggered sensor
                }

                /* Set interrupt line(s) as input and enable, if not also used for triggering */
                if ( ( CH_MODE_FREERUN == mode ) || ( CHIRP_TRIGGER_TYPE == CH_TRIGGER_TYPE_SW ) ||
                     ( CHIRP_SENSOR_INT_PIN != CHIRP_SENSOR_TRIG_PIN ) )
                {
                    CH_LOG_APP_START( "  Setting INT line as input and enabling... " );
                    chdrv_int_group_set_dir_in( grp_ptr );        // set INT line as input
                    chdrv_int_group_interrupt_enable( grp_ptr );  // enable interrupt
                    CH_LOG_APP_MSG( "OK" );
                    CH_LOG_APP_END( );
                }
            }

            if ( !error_flag )
            {
                /* Init algo with new config */
                error_flag = ch_init_algo( dev_ptr );
            }

            if ( !error_flag )
            {
                /* Set sensor mode - must come last, because sensing will be enabled and may begin */
                CH_LOG_APP_START( "  Enabling in %s mode... ", mode_string );
                error_flag = ch_set_mode( dev_ptr, mode );
                CH_LOG_APP_MSG( "%s", error_flag ? "ERROR" : "OK" );
                CH_LOG_APP_END( );
            }

            /* Read back and display config settings */
            if ( !error_flag )
            {
                CH_LOG_APP( "Device %u: Configuration OK", dev_num );
#if IS_CH_LOG_USED
                ch_extra_display_config_info( dev_ptr );
                icu_gpt_display_algo_thresholds( dev_ptr );
#endif
            }
            else
            {
                CH_LOG_APP( "Device %u: ERROR during configuration", dev_num );
            }
        } /*  end if ch_sensor_is_connected() */
    } /*  end for dev_num < num_ports */

    /* Enable receive sensor rx pre-triggering for group, if specified */
    ch_set_rx_pretrigger( grp_ptr, CHIRP_RX_PRETRIGGER_ENABLE );

    return error_flag;
}

/*
 * handle_data_ready() - get and display data from a measurement
 *
 * This routine is called from the main() loop after all sensors have
 * interrupted. It shows how to read the sensor data once a measurement is
 * complete.  This routine always reads out the range and amplitude, and
 * optionally will read out the amplitude data or raw I/Q for all samples
 * in the measurement.
 *
 * See the comments in app_config.h for information about the amplitude data
 * and I/Q readout build options.
 */
static uint8_t handle_data_ready( ch_group_t *grp_ptr )
{
    uint8_t dev_num;
    uint16_t num_samples = 0;
    uint8_t ret_val      = 0;

    /* Read and display data from each connected sensor
     *   This loop will write the sensor data to this application's "chirp_data"
     *   array.  Each sensor has a separate chirp_data_t structure in that
     *   array, so the device number is used as an index.
     *
     *   Multiple detected targets will be displayed if DISPLAY_MULTI_TARGET is non-zero.
     *   Otherwise, only the closest detected target will be displayed.
     */

    for ( dev_num = 0; dev_num < ch_get_num_ports( grp_ptr ); dev_num++ )
    {
        ch_dev_t *dev_ptr = ch_get_dev_ptr( grp_ptr, dev_num );

        if ( ch_sensor_is_connected( dev_ptr ) )
        {
            CH_LOG_APP_START( "Dev %u:  ", dev_num );

            display_algo_output( dev_ptr, dev_num );
            CH_LOG_APP_END( );

            /* Store number of active samples in this measurement */
            num_samples                       = ch_meas_get_num_samples( dev_ptr, 0 );
            chirp_data[ dev_num ].num_samples = num_samples;
        }
    }

    return ret_val;
}

/*
 * sensor_int_callback() - sensor interrupt callback routine
 *
 * This function is called by the board support package's interrupt handler for
 * the sensor's INT line every time that the sensor interrupts.  The device
 * number parameter, dev_num, is used to identify the interrupting device
 * within the sensor group.  (Generally the device number is same as the port
 * number used in the BSP to manage I/O pins, etc.)
 *
 * Each time this function is called, a bit is set in the data_ready_devices
 * variable to identify the interrupting device.  When all active sensors have
 * interrupted (found by comparing with the active_devices variable), the
 * DATA_READY_FLAG is set.  That flag will be detected in the main() loop.
 *
 * This callback function is registered by the call to ch_io_int_callback_set()
 * in main().
 */
static void sensor_int_callback( ch_group_t *grp_ptr, uint8_t dev_num, ch_interrupt_type_t int_type )
{
    ch_dev_t *dev_ptr = ch_get_dev_ptr( grp_ptr, dev_num );

    if ( CH_INTERRUPT_TYPE_DATA_RDY != int_type )
    {
        /* Check soniclib.h CH_INTERRUPT_TYPE_* for values details */
        CH_LOG_ERR( "Sensor %u : Bad interrupt type : %04X", dev_num, int_type );
        return;
    }

    data_ready_devices |= ( 1 << dev_num );  // add to data-ready bit mask

    if ( data_ready_devices == active_devices )
    {
        /* All active sensors have interrupted after performing a measurement */
        data_ready_devices = 0;

        /* Set data-ready flag - it will be checked in main() loop */
        task_flags |= DATA_READY_FLAG;

        /* Disable interrupt for shared int/trig pin if in h/w triggered mode
        *   It will automatically be re-enabled by the next ch_group_trigger()
        */
        if ( ( CH_MODE_FREERUN != ch_get_mode( dev_ptr ) ) && ( CH_TRIGGER_TYPE_HW == ch_get_trigger_type( dev_ptr ) ) &&
             ( CHIRP_SENSOR_INT_PIN == CHIRP_SENSOR_TRIG_PIN ) )
        {
            chdrv_int_group_interrupt_disable( grp_ptr );
        }
        else
        {
            chdrv_int_set_dir_in( dev_ptr );  // set INT line as input and enable int
            chdrv_int_group_interrupt_enable( grp_ptr );
        }
    }
}

static void display_algo_output( ch_dev_t *dev_ptr, uint8_t dev_num )
{
    ch_range_t range_type;
    uint32_t range;
    uint16_t amplitude;
    uint8_t num_targets;

    /*  For sensors in transmit/receive mode, report one-way echo
     *   range.  For sensors in receive-only mode, report direct
     *   one-way range from transmitting sensor.
     */
    if ( CH_MODE_TRIGGERED_RX_ONLY == ch_get_mode( dev_ptr ) || CH_MODE_CONTINUOUS_RX == ch_get_mode( dev_ptr ) )
    {
        range_type = CH_RANGE_DIRECT;
    }
    else
    {
        range_type = CH_RANGE_ECHO_ONE_WAY;
    }

    /* Display detected targets (if any) */
    num_targets = icu_gpt_algo_get_num_targets( dev_ptr );
    if ( 0 == num_targets )
    {
        CH_LOG_APP_MSG( "        no target found  " );
        return;
    }

#if !defined( DISPLAY_MULTI_TARGET ) || ( 0 == DISPLAY_MULTI_TARGET )
    num_targets = 1;
#endif  // DISPLAY_MULTI_TARGET
    for ( uint8_t target_num = 0; target_num < num_targets; target_num++ )
    {
        range = icu_gpt_algo_get_target_range( dev_ptr, target_num, range_type );
        if ( CH_NO_TARGET == range )
        {
            CH_LOG_APP_MSG( "        no target found  " );
            continue;
        }

        amplitude = icu_gpt_algo_get_target_amplitude( dev_ptr, target_num );

        if ( 0 == target_num )
        {
            /* store first target values */
            chirp_data[ dev_num ].range     = range;
            chirp_data[ dev_num ].amplitude = amplitude;
        }

        CH_LOG_APP_MSG( "Tgt %d: %0.2f mm ", target_num, ( float ) range / 32.0f );

        if ( DISPLAY_SAMPLE_NUM )
        {
            uint16_t num_mm = ( range / 32 );

            /* ch_mm_to_samples() assumes num_mm is one-way (1/2 round-trip time-of-flight) */
            if ( CH_RANGE_ECHO_ONE_WAY != range_type )
            {
                num_mm /= 2;  // mm distance was entire time-of-flight, so convert
            }
            CH_LOG_APP_MSG( "(sample %u) ", ch_meas_mm_to_samples( dev_ptr, ch_meas_get_last_num( dev_ptr ), num_mm ) );
        }

        if ( DISPLAY_AMP_VALUE )
        {
            CH_LOG_APP_MSG( "amp=%5u ", amplitude );
        }
        CH_LOG_APP_MSG( "  " );
    }
}

// ------------------------------------------------------------------------- END
