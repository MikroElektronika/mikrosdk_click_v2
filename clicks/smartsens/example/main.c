/*!
 * @file main.c
 * @brief SmartSens Click example
 *
 * # Description
 * This example showcases the ability of the Smart Sens click board.
 * It has multiple examples that you can easily select with the 
 * defines at top of the main. There are 5 examples Euler, Quaternion,
 * and Vector examples for Accelerometer, Gyroscope, and Magnetometer.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules(SPI/I2C, UART) and additional 
 * pins(int_pin, rst). Then after going through reset sequence and checking
 * device and product IDs, interrupt mask, and host control is set to 0, so
 * every interrupt enabled. IF boot status is OK boot sequence is initiated,
 * depending on the defines from the library header it will use RAM or Flash type
 * of the boot. If RAM is selected firmware image first needs to be uploaded to RAM
 * and then it will be booted. If Flash example is selected it will try to boot
 * firmware first if it fails it will then write firmware image to flash and then
 * try to boot it again. When firmware boot is finished Kernel version and Feature
 * registers will be read to check if the firmware is loaded. Then all the callback function
 * will be registered(meta event callback and whatever type of example parser you set),
 * and driver will update its the list of virtual sensors present, and finally will configure
 * virtual sensor that will be used in the selected example.
 *
 * ## Application Task
 * Wait for an interrupt to occur. When occurred read wake-up, non-weak-up, and status FIFO.
 * Parse received that and run the callback parsers to show received data.
 *
 * @note
 * You need to select one of the examples to use this application. You can choose one of 3 
 * type of parsers: Eular, Quaternion, Vector. If Vector example is selected you need to 
 * choose one of the 3 sensors to show x,y,z values: Accelerometer, Gyroscope, or Magnetometer.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartsens.h"

/**
 * @brief Example parser selector.
 * @details Macros for selecting example and it's parser.
 */
#define EULAR           0
#define QUATERNION      0
#define VECTOR          1

/**
 * @brief Vector3 sensor selector.
 * @details Macros for selecting vector3's sensor.
 */
#define ACCELEROMETER   1
#define GYROSCOPE       0
#define MAGNOMETER      0

#define WORK_BUFFER_SIZE   2048
uint8_t work_buffer[ WORK_BUFFER_SIZE ] = { 0 };
uint16_t work_buffer_fill;
uint16_t cmd;
uint8_t status;
static uint8_t verbose;

#if EULAR
/**
 * @brief Eular data.
 * @details Struct for eular data of the Smart Sens Click example.
 */
struct smartsens_data_orientation
{
    int16_t heading;
    int16_t pitch;
    int16_t roll;
};

/**
 * @brief Euler callback prasing function.
 * @details Callback function to parse euler data.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_euler ( struct smartsens_fifo_parse_data_info *callback_info, 
                          void *callback_ref );

/**
 * @brief Parse FIFO frame data into orientation
 * @details Function to parse FIFO frame data into orientation
 * @param[in] data          : Reference to the data buffer storing data from the FIFO
 * @param[out] orientation  : Reference to the data buffer to store orientation
 */
static void smartsens_parse_orientation ( uint8_t *data_val, 
                                          struct smartsens_data_orientation *orientation );
#elif QUATERNION
/**
 * @brief Quaternion data.
 * @details Struct for quaternion data of the Smart Sens Click example.
 */
struct smartsens_data_quaternion
{
    int16_t x;
    int16_t y;
    int16_t z;
    int16_t w;
    uint16_t accuracy;
};

/**
 * @brief Quaternion callback prasing function.
 * @details Callback function to parse quaternion data.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void smartsens_parse_quaternion ( uint8_t *data_val, 
                                         struct smartsens_data_quaternion *quaternion );

/**
 * @brief Parse FIFO frame data into quaternion
 * @details Function to parse FIFO frame data into quaternion
 * @param[in] data          : Reference to the data buffer storing data from the FIFO
 * @param[out] quaternion   : Reference to the data buffer to store quaternion
 */
static void parse_quaternion ( struct smartsens_fifo_parse_data_info *callback_info, 
                               void *callback_ref );
#elif VECTOR
/**
 * @brief Vector3 data.
 * @details Struct for vector3 data of the Smart Sens Click example.
 */
struct smartsens_data_xyz
{
    int16_t x;
    int16_t y;
    int16_t z;
};

/**
 * @brief Parse reference.
 * @details Struct for parse reference data of the Smart Sens Click example.
 */
struct parse_ref
{
    struct
    {
        uint8_t accuracy;
        float scaling_factor;
    }
    sensor[ SMARTSENS_SENSOR_ID_MAX ];
    uint8_t *verbose;
};
struct parse_ref parse_table;

/**
 * @brief Vector3 callback prasing function.
 * @details Callback function to parse vector3 data.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_3axis_s16 ( struct smartsens_fifo_parse_data_info *callback_info, 
                              void *callback_ref );

/**
 * @brief Parse FIFO frame data into 3 axes vector
 * @details Function to parse FIFO frame data into 3 axes vector
 * @param[in] data      : Reference to the data buffer storing data from the FIFO
 * @param[out] vector   : Reference to the data buffer to store vector
 */
static void smartsens_parse_xyz ( uint8_t *data_val, struct smartsens_data_xyz *vector );
#else
    #error NO_EXAMPLE_DEFINED
#endif

static smartsens_t smartsens;
static log_t logger;
static uint8_t read_data = 0;
static uint8_t error_flag = 0;
static uint8_t int_flag = 0;
static uint8_t write_data = 0;
uint8_t accuracy; /* Accuracy is reported as a meta event. It is being printed alongside the data */

/**
 * @brief Meta event callback prasing function.
 * @details Callback function to parse meta event data.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_meta_event ( struct smartsens_fifo_parse_data_info *callback_info, 
                               void *callback_ref );

/**
 * @brief Get name of the virtual senosr by ID.
 * @details Function return name of the virutal senosr by it's ID.
 * @param[in] sensor_id       : Virutal sensor ID.
 * @return Virtual sensor name.
 */
static char* get_sensor_name ( uint8_t sensor_id );

/**
 * @brief Get real time from timestamp.
 * @details Function outputs time from timestamp.
 * @param[in] time_ticks    : Timestamp.
 * @param[out] s            : Seconds.
 * @param[out] ns           : Nano seconds.
 * @return Nothing
 */
static void time_to_s_ns ( uint32_t time_ticks, uint32_t *s, uint32_t *ns );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartsens_cfg_t smartsens_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    smartsens_cfg_setup( &smartsens_cfg );
    SMARTSENS_MAP_MIKROBUS( smartsens_cfg, MIKROBUS_1 );
    err_t init_flag  = smartsens_init( &smartsens, &smartsens_cfg );
    SMARTSENS_SET_DATA_SAMPLE_EDGE
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    /* It can take a few seconds to configure and boot device*/
    log_info( &logger, " Configuring device..." );
    if ( SMARTSENS_ERROR == smartsens_default_cfg ( &smartsens ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Setting callbacks..." );
    /*Set callbacks*/
    if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SYS_ID_META_EVENT,
                                                 parse_meta_event, (void*)&accuracy ) )
    {
        log_error( &logger, " FIFO sys meta event." );
        for( ; ; );
    }
    if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SYS_ID_META_EVENT_WU,
                                                 parse_meta_event, ( void* )&accuracy ) )
    {
        log_error( &logger, " FIFO sys meta event wu." );
        for( ; ; );
    }
#if EULAR
    if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_ORI_WU, 
                                                 parse_euler, ( void* )&accuracy ) )
#elif QUATERNION
    if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_RV_WU, 
                                                 parse_quaternion, NULL ) )
#elif VECTOR
    
        
    #if ACCELEROMETER
        parse_table.sensor[SMARTSENS_SENSOR_ID_ACC].scaling_factor = 1.0f / 4096.0f;
        if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_ACC, 
                                                    parse_3axis_s16, &parse_table ) )
    #elif GYROSCOPE
        parse_table.sensor[SMARTSENS_SENSOR_ID_GYRO].scaling_factor = 1.0f;
        if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_GYRO, 
                                                    parse_3axis_s16, &parse_table ) )
    #elif MAGNOMETER
        parse_table.sensor[SMARTSENS_SENSOR_ID_MAG].scaling_factor = 1.0f;
        if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_MAG, 
                                                    parse_3axis_s16, &parse_table ) )
    #else
        #error NO_VECTOR_EXAMPLE_DEFINED
    #endif
#else
    #error NO_EXAMPLE_DEFINED
#endif
    {
        log_error( &logger, " FIFO sensor id." );
        for( ; ; );
    }
    /*Go through fifo process*/
    if ( smartsens_get_and_process_fifo( &smartsens, work_buffer, WORK_BUFFER_SIZE ) )
    {
        log_error( &logger, " FIFO get and process." );
        for( ; ; );
    }
    /*Update virtual sensor list in context object*/
    if ( smartsens_update_virtual_sensor_list( &smartsens ) )
    {
        log_error( &logger, " Update virtual sensor list." );
        for( ; ; );
    }
    /*Set virtual sensor configuration*/
    float sample_rate = 100.0; /* Read out data measured at 100Hz */
    uint32_t report_latency_ms = 0; /* Report immediately */
#if EULAR
    if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_ORI_WU, 
                                        sample_rate, report_latency_ms ) )
#elif QUATERNION
    if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_RV_WU, 
                                    sample_rate, report_latency_ms ) )
#elif VECTOR
    #if ACCELEROMETER
        if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_ACC, 
                                    sample_rate, report_latency_ms ) )
    #elif GYROSCOPE
        if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_GYRO, 
                                    sample_rate, report_latency_ms ) )
    #elif MAGNOMETER
        if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_MAG, 
                                    sample_rate, report_latency_ms ) )
    #else
        #error NO_VECTOR_EXAMPLE_DEFINED
    #endif
#else
    #error NO_EXAMPLE_DEFINED
#endif
    {
        log_error( &logger, " Set virtual sensor configuration." );
        for( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    /*Check interrupt and get and process fifo buffer*/
    if ( smartsens_get_interrupt( &smartsens ) )
    {
        /* Data from the FIFO is read and the relevant callbacks if registered are called */
        if ( smartsens_get_and_process_fifo( &smartsens, work_buffer, WORK_BUFFER_SIZE ) )
        {
            log_error( &logger, " Get and process fifo." );
            for( ; ; );
        }
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

static void parse_meta_event ( struct smartsens_fifo_parse_data_info *callback_info, 
                               void *callback_ref )
{
    ( void )callback_ref;
    uint8_t meta_event_type = callback_info->data_ptr[ 0 ];
    uint8_t byte1 = callback_info->data_ptr[ 1 ];
    uint8_t byte2 = callback_info->data_ptr[ 2 ];
    uint8_t *accuracy = ( uint8_t* )callback_ref;
    char *event_text;

    if ( callback_info->sensor_id == SMARTSENS_SYS_ID_META_EVENT )
    {
        event_text = "[META EVENT]";
    }
    else if ( callback_info->sensor_id == SMARTSENS_SYS_ID_META_EVENT_WU )
    {
        event_text = "[META EVENT WAKE UP]";
    }
    else
    {
        return;
    }

    switch ( meta_event_type )
    {
        case SMARTSENS_META_EVENT_FLUSH_COMPLETE:
        {
            log_printf( &logger, "%s Flush complete for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS_META_EVENT_SAMPLE_RATE_CHANGED:
        {
            log_printf( &logger, "%s Sample rate changed for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS_META_EVENT_POWER_MODE_CHANGED:
        {
            log_printf( &logger, "%s Power mode changed for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS_META_EVENT_ALGORITHM_EVENTS:
        {
            log_printf( &logger, "%s Algorithm event\r\n", event_text );
            break;
        }
        case SMARTSENS_META_EVENT_SENSOR_STATUS:
        {
            log_printf( &logger, "%s Accuracy for sensor id %s changed to %s\r\n", 
                        event_text, get_sensor_name( byte1 ), get_sensor_name( byte2 ) );
            if ( accuracy )
            {
                *accuracy = byte2;
            }
            break;
        }
        case SMARTSENS_META_EVENT_BSX_DO_STEPS_MAIN:
        {
            log_printf( &logger, "%s BSX event (do steps main)\r\n", event_text );
            break;
        }
        case SMARTSENS_META_EVENT_BSX_DO_STEPS_CALIB:
        {
            log_printf( &logger, "%s BSX event (do steps calib)\r\n", event_text );
            break;
        }
        case SMARTSENS_META_EVENT_BSX_GET_OUTPUT_SIGNAL:
        {
            log_printf( &logger, "%s BSX event (get output signal)\r\n", event_text );
            break;
        }
        case SMARTSENS_META_EVENT_SENSOR_ERROR:
        {
            log_printf( &logger, "%s Sensor id %u reported error 0x%02X\r\n", 
                        event_text, byte1, byte2 );
            break;
        }
        case SMARTSENS_META_EVENT_FIFO_OVERFLOW:
        {
            log_printf( &logger, "%s FIFO overflow\r\n", event_text );
            break;
        }
        case SMARTSENS_META_EVENT_DYNAMIC_RANGE_CHANGED:
        {
            log_printf( &logger, "%s Dynamic range changed for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS_META_EVENT_FIFO_WATERMARK:
        {
            log_printf( &logger, "%s FIFO watermark reached\r\n", event_text );
            break;
        }
        case SMARTSENS_META_EVENT_INITIALIZED:
        {
            log_printf( &logger, "%s Firmware initialized. Firmware version %u\r\n", 
                        event_text, ( ( uint16_t )byte2 << 8 ) | byte1 );
            break;
        }
        case SMARTSENS_META_TRANSFER_CAUSE:
        {
            log_printf( &logger, "%s Transfer cause for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS_META_EVENT_SENSOR_FRAMEWORK:
        {
            log_printf( &logger, "%s Sensor framework event for sensor id %s\r\n", 
                        event_text, byte1 );
            break;
        }
        case SMARTSENS_META_EVENT_RESET:
        {
            log_printf( &logger, "%s Reset event\r\n", event_text );
            break;
        }
        case SMARTSENS_META_EVENT_SPACER:
        {
            break;
        }
        default:
        {
            log_printf( &logger, "%s Unknown meta event with id: %u\r\n", 
                        event_text, meta_event_type );
            break;
        }
    }
}

static char* get_sensor_name ( uint8_t sensor_id )
{
    char *ret;

    switch ( sensor_id )
    {
        case SMARTSENS_SENSOR_ID_ACC_PASS:
        {
            ret = "Accelerometer passthrough";
            break;
        }
        case SMARTSENS_SENSOR_ID_ACC_RAW:
        {
            ret = "Accelerometer uncalibrated";
            break;
        }
        case SMARTSENS_SENSOR_ID_ACC:
            ret = "Accelerometer corrected";
            break;
        case SMARTSENS_SENSOR_ID_ACC_BIAS:
        {
            ret = "Accelerometer offset";
            break;
        }
        case SMARTSENS_SENSOR_ID_ACC_WU:
        {
            ret = "Accelerometer corrected wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_ACC_RAW_WU:
        {
            ret = "Accelerometer uncalibrated wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_GYRO_PASS:
        {
            ret = "Gyroscope passthrough";
            break;
        }
        case SMARTSENS_SENSOR_ID_GYRO_RAW:
        {
            ret = "Gyroscope uncalibrated";
            break;
        }
        case SMARTSENS_SENSOR_ID_GYRO:
        {
            ret = "Gyroscope corrected";
            break;
        }
        case SMARTSENS_SENSOR_ID_GYRO_BIAS:
        {
            ret = "Gyroscope offset";
            break;
        }
        case SMARTSENS_SENSOR_ID_GYRO_WU:
        {
            ret = "Gyroscope wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_GYRO_RAW_WU:
        {
            ret = "Gyroscope uncalibrated wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_MAG_PASS:
        {
            ret = "Magnetometer passthrough";
            break;
        }
        case SMARTSENS_SENSOR_ID_MAG_RAW:
        {
            ret = "Magnetometer uncalibrated";
            break;
        }
        case SMARTSENS_SENSOR_ID_MAG:
        {
            ret = "Magnetometer corrected";
            break;
        }
        case SMARTSENS_SENSOR_ID_MAG_BIAS:
        {
            ret = "Magnetometer offset";
            break;
        }
        case SMARTSENS_SENSOR_ID_MAG_WU:
        {
            ret = "Magnetometer wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_MAG_RAW_WU:
        {
            ret = "Magnetometer uncalibrated wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_GRA:
        {
            ret = "Gravity vector";
            break;
        }
        case SMARTSENS_SENSOR_ID_GRA_WU:
        {
            ret = "Gravity vector wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_LACC:
        {
            ret = "Linear acceleration";
            break;
        }
        case SMARTSENS_SENSOR_ID_LACC_WU:
        {
            ret = "Linear acceleration wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_RV:
        {
            ret = "Rotation vector";
            break;
        }
        case SMARTSENS_SENSOR_ID_RV_WU:
        {
            ret = "Rotation vector wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_GAMERV:
        {
            ret = "Game rotation vector";
            break;
        }
        case SMARTSENS_SENSOR_ID_GAMERV_WU:
        {
            ret = "Game rotation vector wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_GEORV:
        {
            ret = "Geo-magnetic rotation vector";
            break;
        }
        case SMARTSENS_SENSOR_ID_GEORV_WU:
        {
            ret = "Geo-magnetic rotation vector wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_ORI:
        {
            ret = "Orientation";
            break;
        }
        case SMARTSENS_SENSOR_ID_ORI_WU:
        {
            ret = "Orientation wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_TILT_DETECTOR:
        {
            ret = "Tilt detector";
            break;
        }
        case SMARTSENS_SENSOR_ID_STD:
        {
            ret = "Step detector";
            break;
        }
        case SMARTSENS_SENSOR_ID_STC:
        {

        }
        case SMARTSENS_SENSOR_ID_STC_WU:
        {
            ret = "Step counter wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_SIG:
        {
            ret = "Significant motion";
            break;
        }
        case SMARTSENS_SENSOR_ID_WAKE_GESTURE:
        {
            ret = "Wake gesture";
            break;
        }
        case SMARTSENS_SENSOR_ID_GLANCE_GESTURE:
        {
            ret = "Glance gesture";
            break;
        }
        case SMARTSENS_SENSOR_ID_PICKUP_GESTURE:
        {
            ret = "Pickup gesture";
            break;
        }
        case SMARTSENS_SENSOR_ID_AR:
        {
            ret = "Activity recognition";
            break;
        }
        case SMARTSENS_SENSOR_ID_WRIST_TILT_GESTURE:
        {
            ret = "Wrist tilt gesture";
            break;
        }
        case SMARTSENS_SENSOR_ID_DEVICE_ORI:
        {
            ret = "Device orientation";
            break;
        }
        case SMARTSENS_SENSOR_ID_DEVICE_ORI_WU:
        {
            ret = "Device orientation wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_STATIONARY_DET:
        {
            ret = "Stationary detect";
            break;
        }
        case SMARTSENS_SENSOR_ID_MOTION_DET:
        {
            ret = "Motion detect";
            break;
        }
        case SMARTSENS_SENSOR_ID_ACC_BIAS_WU:
        {
            ret = "Accelerometer offset wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_GYRO_BIAS_WU:
        {
            ret = "Gyroscope offset wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_MAG_BIAS_WU:
        {
            ret = "Magnetometer offset wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_STD_WU:
        {
            ret = "Step detector wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_TEMP:
        {
            ret = "Temperature";
            break;
        }
        case SMARTSENS_SENSOR_ID_BARO:
        {
            ret = "Barometer";
            break;
        }
        case SMARTSENS_SENSOR_ID_HUM:
        {
            ret = "Humidity";
            break;
        }
        case SMARTSENS_SENSOR_ID_GAS:
        {
            ret = "Gas";
            break;
        }
        case SMARTSENS_SENSOR_ID_TEMP_WU:
        {
            ret = "Temperature wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_BARO_WU:
        {
            ret = "Barometer wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_HUM_WU:
        {
            ret = "Humidity wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_GAS_WU:
        {
            ret = "Gas wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_STC_HW:
        {
            ret = "Hardware Step counter";
            break;
        }
        case SMARTSENS_SENSOR_ID_STD_HW:
        {
            ret = "Hardware Step detector";
            break;
        }
        case SMARTSENS_SENSOR_ID_SIG_HW:
        {
            ret = "Hardware Significant motion";
            break;
        }
        case SMARTSENS_SENSOR_ID_STC_HW_WU:
        {
            ret = "Hardware Step counter wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_STD_HW_WU:
        {
            ret = "Hardware Step detector wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_SIG_HW_WU:
        {
            ret = "Hardware Significant motion wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_ANY_MOTION:
        {
            ret = "Any motion";
            break;
        }
        case SMARTSENS_SENSOR_ID_ANY_MOTION_WU:
        {
            ret = "Any motion wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_EXCAMERA:
        {
            ret = "External camera trigger";
            break;
        }
        case SMARTSENS_SENSOR_ID_GPS:
        {
            ret = "GPS";
            break;
        }
        case SMARTSENS_SENSOR_ID_LIGHT:
        {
            ret = "Light";
            break;
        }
        case SMARTSENS_SENSOR_ID_PROX:
        {
            ret = "Proximity";
            break;
        }
        case SMARTSENS_SENSOR_ID_LIGHT_WU:
        {
            ret = "Light wake up";
            break;
        }
        case SMARTSENS_SENSOR_ID_PROX_WU:
        {
            ret = "Proximity wake up";
            break;
        }
        default:
        {
            if ( ( sensor_id >= SMARTSENS_SENSOR_ID_CUSTOM_START ) && ( sensor_id <= SMARTSENS_SENSOR_ID_CUSTOM_END ) )
            {
                ret = "Custom sensor ID ";
            }
            else
            {
                ret = "Undefined sensor ID ";
            }
        }
    }

    return ret;
}

static void time_to_s_ns ( uint32_t time_ticks, uint32_t *s, uint32_t *ns )
{
    uint32_t timestamp = time_ticks; /* Store the last timestamp */

    timestamp = timestamp * 15625; /* timestamp is now in nanoseconds */
    *s = ( uint32_t )( timestamp / UINT32_C( 1000000000 ) );
    *ns = ( uint32_t )( timestamp - ( ( *s ) * UINT32_C( 1000000000 ) ) );
}

#if EULAR
static void parse_euler ( struct smartsens_fifo_parse_data_info *callback_info, 
                          void *callback_ref )
{
    ( void )callback_ref;
    struct smartsens_data_orientation data_val;
    uint32_t s, ns;
    uint8_t *accuracy = ( uint8_t* )callback_ref;
    if ( callback_info->data_size != 7 ) /* Check for a valid payload size. Includes sensor ID */
    {
        return;
    }

    smartsens_parse_orientation( callback_info->data_ptr, &data_val );
    time_to_s_ns( *callback_info->time_stamp, &s, &ns );

    if ( accuracy )
    {
        log_printf( &logger, "SID: %s; T: %u; h: %f, p: %f, r: %f; acc: %u\r\n",
                    get_sensor_name( callback_info->sensor_id ),
                    s,
                    data_val.heading * 360.0f / 32768.0f,
                    data_val.pitch * 360.0f / 32768.0f,
                    data_val.roll * 360.0f / 32768.0f,
                    *accuracy );
    }
    else
    {
        log_printf( &logger, "SID: %s; T: %u; h: %f, p: %f, r: %f\r\n",
                    get_sensor_name( callback_info->sensor_id ),
                    s,
                    data_val.heading * 360.0f / 32768.0f,
                    data_val.pitch * 360.0f / 32768.0f,
                    data_val.roll * 360.0f / 32768.0f );
    }
}

static void smartsens_parse_orientation ( uint8_t *data_val, struct smartsens_data_orientation *orientation )
{
    orientation->heading = SMARTSENS_LE2S16( data_val );
    orientation->pitch = SMARTSENS_LE2S16( data_val + 2 );
    orientation->roll = SMARTSENS_LE2S16( data_val + 4 );
}
#elif QUATERNION
static void parse_quaternion ( struct smartsens_fifo_parse_data_info *callback_info, void *callback_ref )
{
    ( void )callback_ref;
    struct smartsens_data_quaternion data_val;
    uint32_t s, ns;
    if ( callback_info->data_size != 11 ) /* Check for a valid payload size. Includes sensor ID */
    {
        return;
    }

    smartsens_parse_quaternion(callback_info->data_ptr, &data_val);
    time_to_s_ns( *callback_info->time_stamp, &s, &ns );

    log_printf( &logger, "SID: %s; T: %u; x: %f, y: %f, z: %f, w: %f; acc: %.2f\r\n",
                get_sensor_name( callback_info->sensor_id ),
                s,
                data_val.x / 16384.0f,
                data_val.y / 16384.0f,
                data_val.z / 16384.0f,
                data_val.w / 16384.0f,
                ( ( data_val.accuracy * 180.0f ) / 16384.0f ) / 3.141592653589793f );
}

static void smartsens_parse_quaternion ( uint8_t *data_val, struct smartsens_data_quaternion *quaternion )
{
    quaternion->x = SMARTSENS_LE2S16( data_val );
    quaternion->y = SMARTSENS_LE2S16( data_val + 2 );
    quaternion->z = SMARTSENS_LE2S16( data_val + 4 );
    quaternion->w = SMARTSENS_LE2S16( data_val + 6 );
    quaternion->accuracy = SMARTSENS_LE2S16( data_val + 8 );
}
#elif VECTOR
static void parse_3axis_s16 ( struct smartsens_fifo_parse_data_info *callback_info, void *callback_ref )
{
    struct smartsens_data_xyz data_value;
    uint32_t s, ns;

    if ( callback_ref )
    {
        struct parse_ref *parse_table = (struct parse_ref*)callback_ref;
        verbose = *(parse_table->verbose);
        float scaling_factor;

        scaling_factor = parse_table->sensor[ callback_info->sensor_id ].scaling_factor;

        smartsens_parse_xyz( callback_info->data_ptr, &data_value );
        time_to_s_ns( *callback_info->time_stamp, &s, &ns );

        log_printf( &logger, "SID: %s; T: %u; x: %f, y: %f, z: %f; acc: %u\r\n",
                    get_sensor_name( callback_info->sensor_id ),
                    s,
                    data_value.x * scaling_factor,
                    data_value.y * scaling_factor,
                    data_value.z * scaling_factor,
                    parse_table->sensor[callback_info->sensor_id].accuracy);
    }
    else
    {
        log_error( &logger, "Null reference" );
    }
}

static void smartsens_parse_xyz ( uint8_t *data_val, struct smartsens_data_xyz *vector )
{
    vector->x = SMARTSENS_LE2S16( data_val );
    vector->y = SMARTSENS_LE2S16( data_val + 2 );
    vector->z = SMARTSENS_LE2S16( data_val + 4 );
}
#else
    #error NO_EXAMPLE_DEFINED
#endif

// ------------------------------------------------------------------------ END
