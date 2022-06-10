/*!
 * @file main.c
 * @brief SmartSens2 Click example
 *
 * # Description
 * This example showcases the ability of the Smart Sens 2 click board.
 * It has multiple examples that you can easily select with the 
 * defines at the top of the main. There are 9 examples: Euler, Quaternion,
 * Vector (Accelerometer, Gyroscope, Magnetometer), and 
 * Environmental (Temperature, Barometer, Humidity, Gas).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules (SPI/I2C) and additional 
 * pins(int_pin, rst). After that going through reset sequence and checking
 * device and product IDs, interrupt mask, and host control is set to 0, so
 * every interrupt enabled. If boot status is OK boot sequence is initiated,
 * depending on the defines from the library header it will use RAM or Flash type
 * of the boot. If RAM is selected firmware image first needs to be uploaded to RAM
 * and then it will be booted. If Flash example is selected it will try to boot
 * firmware first if it fails it will then write firmware image to flash and then
 * try to boot it again. When firmware boot is finished Kernel version and Feature
 * registers will be read to check if the firmware is loaded. Then all the callback function
 * will be registered(meta event callback and whatever type of example parser you set),
 * and driver will update the list of virtual sensors present, and finally will configure
 * virtual sensor that will be used in the selected example.
 *
 * ## Application Task
 * Wait for an interrupt to occur, then read wake-up, non-weak-up, and status FIFO.
 * Parse received data and run the callback parsers to show data on the USB UART.
 *
 * @note
 * Select one of the examples with macros at the top of the main file. Euler example is selected by default. 
 * You can choose one of 4 type of parsers: Euler, Quaternion, Vector, Environmental. If Vector example is selected 
 * you choose one of the 3 sensors to show X, Y, and Z values: Accelerometer, Gyroscope, or Magnetometer.
 * If Environmental example is selected you choose one of the 4 sensors: Temperature, Barometer, Humidity, or Gas.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartsens2.h"

/**
 * @brief Example parser selector.
 * @details Macros for selecting example and its parser.
 */
#define EULER                   1
#define QUATERNION              0
#define VECTOR                  0
#define ENVIRONMENTAL           0

/**
 * @brief Vector sensor selector.
 * @details Macros for selecting vector's sensor.
 */
#define ACCELEROMETER           1
#define GYROSCOPE               0
#define MAGNETOMETER            0

/**
 * @brief Environmental sensor selector.
 * @details Macros for selecting environmental sensor.
 */
#define TEMPERATURE             1
#define BAROMETER               0
#define HUMIDITY                0
#define GAS                     0

#define WORK_BUFFER_SIZE        2048
uint8_t work_buffer[ WORK_BUFFER_SIZE ] = { 0 };
static smartsens2_t smartsens2;
static log_t logger;
uint8_t accuracy; /* Accuracy is reported as a meta event. It is being printed alongside the data */

#if EULER
/**
 * @brief Euler data.
 * @details Struct for euler data of the Smart Sens 2 Click example.
 */
struct smartsens2_data_orientation
{
    int16_t heading;
    int16_t pitch;
    int16_t roll;
};

/**
 * @brief Euler callback parsing function.
 * @details Callback function to parse euler data.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_euler ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref );
#elif QUATERNION
/**
 * @brief Quaternion data.
 * @details Struct for quaternion data of the Smart Sens 2 Click example.
 */
struct smartsens2_data_quaternion
{
    int16_t x;
    int16_t y;
    int16_t z;
    int16_t w;
    uint16_t accuracy;
};

/**
 * @brief Parse FIFO frame data into quaternion
 * @details Function to parse FIFO frame data into quaternion
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 */
static void parse_quaternion ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref );
#elif VECTOR
/**
 * @brief Vector data.
 * @details Struct for vector data of the Smart Sens 2 Click example.
 */
struct smartsens2_data_xyz
{
    int16_t x;
    int16_t y;
    int16_t z;
};

/**
 * @brief Parse reference.
 * @details Struct for parse reference data of the Smart Sens 2 Click example.
 */
struct parse_ref
{
    struct
    {
        uint8_t accuracy;
        float scaling_factor;
    }
    sensor[ SMARTSENS2_SENSOR_ID_MAX ];
    uint8_t *verbose;
};
struct parse_ref parse_table;

/**
 * @brief Vector callback parsing function.
 * @details Callback function to parse vector data.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_vector_s16 ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref );
#elif ENVIRONMENTAL
/**
 * @brief Temperature callback parsing function.
 * @details Callback function to parse temperature data.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_temperature ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref );

/**
 * @brief Barometer callback parsing function.
 * @details Callback function to parse barometer data.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_barometer ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref );

/**
 * @brief Humidity callback parsing function.
 * @details Callback function to parse humidity data.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_humidity ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref );

/**
 * @brief Gas callback parsing function.
 * @details Callback function to parse gas data.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_gas ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref );
#else
    #error NO_EXAMPLE_DEFINED
#endif

/**
 * @brief Meta event callback parsing function.
 * @details Callback function to parse meta event data.
 * @param[in] callback_info      : Callback data.
 * @param[in] callback_ref       : Callback reference.
 * @return Nothing
 */
static void parse_meta_event ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref );

/**
 * @brief Get name of the virtual sensor by ID.
 * @details Function return name of the virutal sensor by its ID.
 * @param[in] sensor_id       : Virtual sensor ID.
 * @return Virtual sensor name.
 */
static char* get_sensor_name ( uint8_t sensor_id );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartsens2_cfg_t smartsens2_cfg;  /**< Click config object. */

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
    smartsens2_cfg_setup( &smartsens2_cfg );
    SMARTSENS2_MAP_MIKROBUS( smartsens2_cfg, MIKROBUS_1 );
    err_t init_flag = smartsens2_init( &smartsens2, &smartsens2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    /* It can take a few seconds to configure and boot device */
    log_info( &logger, " Configuring device..." );
    if ( SMARTSENS2_ERROR == smartsens2_default_cfg ( &smartsens2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Setting callbacks..." );
    /* Set callbacks */
    if ( smartsens2_register_fifo_parse_callback( &smartsens2, SMARTSENS2_SYS_ID_META_EVENT,
                                                  parse_meta_event, &accuracy ) )
    {
        log_error( &logger, " FIFO sys meta event." );
        for ( ; ; );
    }
    if ( smartsens2_register_fifo_parse_callback( &smartsens2, SMARTSENS2_SYS_ID_META_EVENT_WU,
                                                  parse_meta_event, &accuracy ) )
    {
        log_error( &logger, " FIFO sys meta event wu." );
        for ( ; ; );
    }
    uint8_t sensor_id;
    smartsens2_fifo_parse_callback_t callback;
    void *callback_ref;
#if EULER
    sensor_id = SMARTSENS2_SENSOR_ID_ORI;
    callback = parse_euler;
    callback_ref = &accuracy;
#elif QUATERNION
    sensor_id = SMARTSENS2_SENSOR_ID_RV;
    callback = parse_quaternion;
    callback_ref = NULL;
#elif VECTOR
    #if ACCELEROMETER
        parse_table.sensor[ SMARTSENS2_SENSOR_ID_ACC ].scaling_factor = 1.0f / 4096.0f;
        sensor_id = SMARTSENS2_SENSOR_ID_ACC;
    #elif GYROSCOPE
        parse_table.sensor[ SMARTSENS2_SENSOR_ID_GYRO ].scaling_factor = 1.0f;
        sensor_id = SMARTSENS2_SENSOR_ID_GYRO;
    #elif MAGNETOMETER
        parse_table.sensor[ SMARTSENS2_SENSOR_ID_MAG ].scaling_factor = 1.0f;
        sensor_id = SMARTSENS2_SENSOR_ID_MAG;
    #else
        #error NO_VECTOR_EXAMPLE_DEFINED
    #endif
    callback = parse_vector_s16;
    callback_ref = &parse_table;
#elif ENVIRONMENTAL
    #if TEMPERATURE
        sensor_id = SMARTSENS2_SENSOR_ID_TEMP;
        callback = parse_temperature;
    #elif BAROMETER
        sensor_id = SMARTSENS2_SENSOR_ID_BARO;
        callback = parse_barometer;
    #elif HUMIDITY
        sensor_id = SMARTSENS2_SENSOR_ID_HUM;
        callback = parse_humidity;
    #elif GAS
        sensor_id = SMARTSENS2_SENSOR_ID_GAS;
        callback = parse_gas;
    #else
        #error NO_ENVIRONMENTAL_EXAMPLE_DEFINED
    #endif
    callback_ref = NULL;
#else
    #error NO_EXAMPLE_DEFINED
#endif
    if ( smartsens2_register_fifo_parse_callback( &smartsens2, sensor_id, callback, callback_ref ) )
    {
        log_error( &logger, " FIFO sensor id." );
        for ( ; ; );
    }
    /* Go through fifo process */
    if ( smartsens2_get_and_process_fifo( &smartsens2, work_buffer, WORK_BUFFER_SIZE ) )
    {
        log_error( &logger, " FIFO get and process." );
        for ( ; ; );
    }
    /* Update virtual sensor list in context object */
    if ( smartsens2_update_virtual_sensor_list( &smartsens2 ) )
    {
        log_error( &logger, " Update virtual sensor list." );
        for ( ; ; );
    }
    /* Set virtual sensor configuration */
    float sample_rate = 10.0; /* Read out data at 10Hz */
    uint32_t report_latency_ms = 0; /* Report immediately */
    if ( smartsens2_set_virt_sensor_cfg( &smartsens2, sensor_id, sample_rate, report_latency_ms ) )
    {
        log_error( &logger, " Set virtual sensor configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    /* Check interrupt and get and process fifo buffer */
    if ( smartsens2_get_interrupt( &smartsens2 ) )
    {
        /* Data from the FIFO is read and the relevant callbacks if registered are called */
        if ( smartsens2_get_and_process_fifo( &smartsens2, work_buffer, WORK_BUFFER_SIZE ) )
        {
            log_error( &logger, " Get and process fifo." );
            for ( ; ; );
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

#if EULER
static void parse_euler ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref )
{
    struct smartsens2_data_orientation data_val;
    uint8_t *accuracy = ( uint8_t* ) callback_ref;
    if ( callback_info->data_size != 7 ) /* Check for a valid payload size. Includes sensor ID */
    {
        return;
    }
    data_val.heading = SMARTSENS2_LE2S16( callback_info->data_ptr );
    data_val.pitch = SMARTSENS2_LE2S16( callback_info->data_ptr + 2 );
    data_val.roll = SMARTSENS2_LE2S16( callback_info->data_ptr + 4 );
    if ( accuracy )
    {
        log_printf( &logger, "SID: %s; H: %.3f, P: %.3f, R: %.3f; acc: %u; Time: %lus\r\n",
                    get_sensor_name( callback_info->sensor_id ),
                    ( float ) ( data_val.heading * 360.0f / 32768.0f ),
                    ( float ) ( data_val.pitch * 360.0f / 32768.0f ),
                    ( float ) ( data_val.roll * 360.0f / 32768.0f ),
                    ( uint16_t ) ( *accuracy ),
                    SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
    }
    else
    {
        log_printf( &logger, "SID: %s; H: %.3f, P: %.3f, R: %.3f; Time: %lus\r\n",
                    get_sensor_name( callback_info->sensor_id ),
                    ( float ) ( data_val.heading * 360.0f / 32768.0f ),
                    ( float ) ( data_val.pitch * 360.0f / 32768.0f ),
                    ( float ) ( data_val.roll * 360.0f / 32768.0f ),
                    SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
    }
}
#elif QUATERNION
static void parse_quaternion ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref )
{
    struct smartsens2_data_quaternion data_val;
    if ( callback_info->data_size != 11 ) /* Check for a valid payload size. Includes sensor ID */
    {
        return;
    }
    data_val.x = SMARTSENS2_LE2S16( callback_info->data_ptr );
    data_val.y = SMARTSENS2_LE2S16( callback_info->data_ptr + 2 );
    data_val.z = SMARTSENS2_LE2S16( callback_info->data_ptr + 4 );
    data_val.w = SMARTSENS2_LE2S16( callback_info->data_ptr + 6 );
    data_val.accuracy = SMARTSENS2_LE2U16( callback_info->data_ptr + 8 );
    log_printf( &logger, "SID: %s; X: %.3f, Y: %.3f, Z: %.3f, W: %.3f; acc: %.2f; Time: %lus\r\n",
                get_sensor_name( callback_info->sensor_id ),
                ( float ) ( data_val.x / 16384.0f ),
                ( float ) ( data_val.y / 16384.0f ),
                ( float ) ( data_val.z / 16384.0f ),
                ( float ) ( data_val.w / 16384.0f ),
                ( float ) ( ( ( data_val.accuracy * 180.0f ) / 16384.0f ) / 3.141592653589793f ),
                SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
}
#elif VECTOR
static void parse_vector_s16 ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref )
{
    struct smartsens2_data_xyz data_value;
    if ( callback_ref )
    {
        struct parse_ref *parse_table = ( struct parse_ref* ) callback_ref;
        float scaling_factor = parse_table->sensor[ callback_info->sensor_id ].scaling_factor;
        data_value.x = SMARTSENS2_LE2S16( callback_info->data_ptr );
        data_value.y = SMARTSENS2_LE2S16( callback_info->data_ptr + 2 );
        data_value.z = SMARTSENS2_LE2S16( callback_info->data_ptr + 4 );
    #if ACCELEROMETER
        log_printf( &logger, "SID: %s; X: %.3f, Y: %.3f, Z: %.3f; acc: %u; Time: %lus\r\n",
                    get_sensor_name( callback_info->sensor_id ),
                    ( float ) ( data_value.x * scaling_factor ),
                    ( float ) ( data_value.y * scaling_factor ),
                    ( float ) ( data_value.z * scaling_factor ),
                    ( uint16_t ) parse_table->sensor[ callback_info->sensor_id ].accuracy, 
                    SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
    #elif GYROSCOPE
        log_printf( &logger, "SID: %s; X: %d, Y: %d, Z: %d; acc: %u; Time: %lus\r\n",
                    get_sensor_name( callback_info->sensor_id ),
                    ( int16_t ) ( data_value.x * scaling_factor ),
                    ( int16_t ) ( data_value.y * scaling_factor ),
                    ( int16_t ) ( data_value.z * scaling_factor ),
                    ( uint16_t ) parse_table->sensor[ callback_info->sensor_id ].accuracy, 
                    SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
    #elif MAGNETOMETER
        log_printf( &logger, "SID: %s; X: %d, Y: %d, Z: %d; acc: %u; Time: %lus\r\n",
                    get_sensor_name( callback_info->sensor_id ),
                    ( int16_t ) ( data_value.x * scaling_factor ),
                    ( int16_t ) ( data_value.y * scaling_factor ),
                    ( int16_t ) ( data_value.z * scaling_factor ),
                    ( uint16_t ) parse_table->sensor[ callback_info->sensor_id ].accuracy, 
                    SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
    #else
        #error NO_VECTOR_EXAMPLE_DEFINED
    #endif
    }
    else
    {
        log_error( &logger, "Null reference" );
    }
}
#elif ENVIRONMENTAL
static void parse_temperature ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref )
{
    if ( callback_info->data_size != 5 ) /* Check for a valid payload size. Includes sensor ID */
    {
        return;
    }
    log_printf( &logger, "SID: %s; T: %.2f C; Time: %lus\r\n",
                get_sensor_name( callback_info->sensor_id ),
                ( SMARTSENS2_LE2S16( callback_info->data_ptr ) / 100.0 ), 
                SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
}

static void parse_barometer ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref )
{
    if ( callback_info->data_size != 4 ) /* Check for a valid payload size. Includes sensor ID */
    {
        return;
    }
    log_printf( &logger, "SID: %s; P: %.1f mBar; Time: %lus\r\n",
                get_sensor_name( callback_info->sensor_id ),
                ( SMARTSENS2_LE2U24( callback_info->data_ptr ) / 128.0 ), 
                SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
}

static void parse_humidity ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref )
{
    if ( callback_info->data_size != 2 ) /* Check for a valid payload size. Includes sensor ID */
    {
        return;
    }
    log_printf( &logger, "SID: %s; H: %u %%; Time: %lus\r\n",
                get_sensor_name( callback_info->sensor_id ),
                ( uint16_t ) callback_info->data_ptr[ 0 ], 
                SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
}

static void parse_gas ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref )
{
    if ( callback_info->data_size != 5 ) /* Check for a valid payload size. Includes sensor ID */
    {
        return;
    }
    log_printf( &logger, "SID: %s; G: %lu Ohms; Time: %lus\r\n",
                get_sensor_name( callback_info->sensor_id ),
                SMARTSENS2_LE2U32( callback_info->data_ptr ), 
                SMARTSENS2_TIMESTAMP_TO_SEC( *callback_info->time_stamp ) );
}
#else
    #error NO_EXAMPLE_DEFINED
#endif

static void parse_meta_event ( struct smartsens2_fifo_parse_data_info *callback_info, void *callback_ref )
{
    uint8_t meta_event_type = callback_info->data_ptr[ 0 ];
    uint8_t byte1 = callback_info->data_ptr[ 1 ];
    uint8_t byte2 = callback_info->data_ptr[ 2 ];
    uint8_t *accuracy = ( uint8_t* ) callback_ref;
    char *event_text;

    if ( SMARTSENS2_SYS_ID_META_EVENT == callback_info->sensor_id )
    {
        event_text = "[META EVENT]";
    }
    else if ( SMARTSENS2_SYS_ID_META_EVENT_WU == callback_info->sensor_id )
    {
        event_text = "[META EVENT WAKE UP]";
    }
    else
    {
        return;
    }

    switch ( meta_event_type )
    {
        case SMARTSENS2_META_EVENT_FLUSH_COMPLETE:
        {
            log_printf( &logger, "%s Flush complete for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS2_META_EVENT_SAMPLE_RATE_CHANGED:
        {
            log_printf( &logger, "%s Sample rate changed for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS2_META_EVENT_POWER_MODE_CHANGED:
        {
            log_printf( &logger, "%s Power mode changed for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS2_META_EVENT_ALGORITHM_EVENTS:
        {
            log_printf( &logger, "%s Algorithm event\r\n", event_text );
            break;
        }
        case SMARTSENS2_META_EVENT_SENSOR_STATUS:
        {
            log_printf( &logger, "%s Accuracy for sensor id %s changed to %s\r\n", 
                        event_text, get_sensor_name( byte1 ), get_sensor_name( byte2 ) );
            if ( accuracy )
            {
                *accuracy = byte2;
            }
            break;
        }
        case SMARTSENS2_META_EVENT_BSX_DO_STEPS_MAIN:
        {
            log_printf( &logger, "%s BSX event (do steps main)\r\n", event_text );
            break;
        }
        case SMARTSENS2_META_EVENT_BSX_DO_STEPS_CALIB:
        {
            log_printf( &logger, "%s BSX event (do steps calib)\r\n", event_text );
            break;
        }
        case SMARTSENS2_META_EVENT_BSX_GET_OUTPUT_SIGNAL:
        {
            log_printf( &logger, "%s BSX event (get output signal)\r\n", event_text );
            break;
        }
        case SMARTSENS2_META_EVENT_SENSOR_ERROR:
        {
            log_printf( &logger, "%s Sensor id %u reported error 0x%02X\r\n", 
                        event_text, byte1, byte2 );
            break;
        }
        case SMARTSENS2_META_EVENT_FIFO_OVERFLOW:
        {
            log_printf( &logger, "%s FIFO overflow\r\n", event_text );
            break;
        }
        case SMARTSENS2_META_EVENT_DYNAMIC_RANGE_CHANGED:
        {
            log_printf( &logger, "%s Dynamic range changed for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS2_META_EVENT_FIFO_WATERMARK:
        {
            log_printf( &logger, "%s FIFO watermark reached\r\n", event_text );
            break;
        }
        case SMARTSENS2_META_EVENT_INITIALIZED:
        {
            log_printf( &logger, "%s Firmware initialized. Firmware version %u\r\n", 
                        event_text, ( ( uint16_t )byte2 << 8 ) | byte1 );
            break;
        }
        case SMARTSENS2_META_TRANSFER_CAUSE:
        {
            log_printf( &logger, "%s Transfer cause for sensor id %s\r\n", 
                        event_text, get_sensor_name( byte1 ) );
            break;
        }
        case SMARTSENS2_META_EVENT_SENSOR_FRAMEWORK:
        {
            log_printf( &logger, "%s Sensor framework event for sensor id %s\r\n", 
                        event_text, byte1 );
            break;
        }
        case SMARTSENS2_META_EVENT_RESET:
        {
            log_printf( &logger, "%s Reset event\r\n", event_text );
            break;
        }
        case SMARTSENS2_META_EVENT_SPACER:
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
        case SMARTSENS2_SENSOR_ID_ACC_PASS:
        {
            ret = "Accelerometer passthrough";
            break;
        }
        case SMARTSENS2_SENSOR_ID_ACC_RAW:
        {
            ret = "Accelerometer uncalibrated";
            break;
        }
        case SMARTSENS2_SENSOR_ID_ACC:
            ret = "Accelerometer corrected";
            break;
        case SMARTSENS2_SENSOR_ID_ACC_BIAS:
        {
            ret = "Accelerometer offset";
            break;
        }
        case SMARTSENS2_SENSOR_ID_ACC_WU:
        {
            ret = "Accelerometer corrected wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_ACC_RAW_WU:
        {
            ret = "Accelerometer uncalibrated wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GYRO_PASS:
        {
            ret = "Gyroscope passthrough";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GYRO_RAW:
        {
            ret = "Gyroscope uncalibrated";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GYRO:
        {
            ret = "Gyroscope corrected";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GYRO_BIAS:
        {
            ret = "Gyroscope offset";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GYRO_WU:
        {
            ret = "Gyroscope wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GYRO_RAW_WU:
        {
            ret = "Gyroscope uncalibrated wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_MAG_PASS:
        {
            ret = "Magnetometer passthrough";
            break;
        }
        case SMARTSENS2_SENSOR_ID_MAG_RAW:
        {
            ret = "Magnetometer uncalibrated";
            break;
        }
        case SMARTSENS2_SENSOR_ID_MAG:
        {
            ret = "Magnetometer corrected";
            break;
        }
        case SMARTSENS2_SENSOR_ID_MAG_BIAS:
        {
            ret = "Magnetometer offset";
            break;
        }
        case SMARTSENS2_SENSOR_ID_MAG_WU:
        {
            ret = "Magnetometer wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_MAG_RAW_WU:
        {
            ret = "Magnetometer uncalibrated wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GRA:
        {
            ret = "Gravity vector";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GRA_WU:
        {
            ret = "Gravity vector wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_LACC:
        {
            ret = "Linear acceleration";
            break;
        }
        case SMARTSENS2_SENSOR_ID_LACC_WU:
        {
            ret = "Linear acceleration wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_RV:
        {
            ret = "Rotation vector";
            break;
        }
        case SMARTSENS2_SENSOR_ID_RV_WU:
        {
            ret = "Rotation vector wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GAMERV:
        {
            ret = "Game rotation vector";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GAMERV_WU:
        {
            ret = "Game rotation vector wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GEORV:
        {
            ret = "Geo-magnetic rotation vector";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GEORV_WU:
        {
            ret = "Geo-magnetic rotation vector wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_ORI:
        {
            ret = "Orientation";
            break;
        }
        case SMARTSENS2_SENSOR_ID_ORI_WU:
        {
            ret = "Orientation wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_TILT_DETECTOR:
        {
            ret = "Tilt detector";
            break;
        }
        case SMARTSENS2_SENSOR_ID_STD:
        {
            ret = "Step detector";
            break;
        }
        case SMARTSENS2_SENSOR_ID_STC:
        {
            ret = "Step counter";
            break;
        }
        case SMARTSENS2_SENSOR_ID_STC_WU:
        {
            ret = "Step counter wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_SIG:
        {
            ret = "Significant motion";
            break;
        }
        case SMARTSENS2_SENSOR_ID_WAKE_GESTURE:
        {
            ret = "Wake gesture";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GLANCE_GESTURE:
        {
            ret = "Glance gesture";
            break;
        }
        case SMARTSENS2_SENSOR_ID_PICKUP_GESTURE:
        {
            ret = "Pickup gesture";
            break;
        }
        case SMARTSENS2_SENSOR_ID_AR:
        {
            ret = "Activity recognition";
            break;
        }
        case SMARTSENS2_SENSOR_ID_WRIST_TILT_GESTURE:
        {
            ret = "Wrist tilt gesture";
            break;
        }
        case SMARTSENS2_SENSOR_ID_DEVICE_ORI:
        {
            ret = "Device orientation";
            break;
        }
        case SMARTSENS2_SENSOR_ID_DEVICE_ORI_WU:
        {
            ret = "Device orientation wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_STATIONARY_DET:
        {
            ret = "Stationary detect";
            break;
        }
        case SMARTSENS2_SENSOR_ID_MOTION_DET:
        {
            ret = "Motion detect";
            break;
        }
        case SMARTSENS2_SENSOR_ID_ACC_BIAS_WU:
        {
            ret = "Accelerometer offset wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GYRO_BIAS_WU:
        {
            ret = "Gyroscope offset wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_MAG_BIAS_WU:
        {
            ret = "Magnetometer offset wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_STD_WU:
        {
            ret = "Step detector wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_TEMP:
        {
            ret = "Temperature";
            break;
        }
        case SMARTSENS2_SENSOR_ID_BARO:
        {
            ret = "Barometer";
            break;
        }
        case SMARTSENS2_SENSOR_ID_HUM:
        {
            ret = "Humidity";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GAS:
        {
            ret = "Gas";
            break;
        }
        case SMARTSENS2_SENSOR_ID_TEMP_WU:
        {
            ret = "Temperature wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_BARO_WU:
        {
            ret = "Barometer wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_HUM_WU:
        {
            ret = "Humidity wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GAS_WU:
        {
            ret = "Gas wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_STC_HW:
        {
            ret = "Hardware Step counter";
            break;
        }
        case SMARTSENS2_SENSOR_ID_STD_HW:
        {
            ret = "Hardware Step detector";
            break;
        }
        case SMARTSENS2_SENSOR_ID_SIG_HW:
        {
            ret = "Hardware Significant motion";
            break;
        }
        case SMARTSENS2_SENSOR_ID_STC_HW_WU:
        {
            ret = "Hardware Step counter wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_STD_HW_WU:
        {
            ret = "Hardware Step detector wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_SIG_HW_WU:
        {
            ret = "Hardware Significant motion wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_ANY_MOTION:
        {
            ret = "Any motion";
            break;
        }
        case SMARTSENS2_SENSOR_ID_ANY_MOTION_WU:
        {
            ret = "Any motion wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_EXCAMERA:
        {
            ret = "External camera trigger";
            break;
        }
        case SMARTSENS2_SENSOR_ID_GPS:
        {
            ret = "GPS";
            break;
        }
        case SMARTSENS2_SENSOR_ID_LIGHT:
        {
            ret = "Light";
            break;
        }
        case SMARTSENS2_SENSOR_ID_PROX:
        {
            ret = "Proximity";
            break;
        }
        case SMARTSENS2_SENSOR_ID_LIGHT_WU:
        {
            ret = "Light wake up";
            break;
        }
        case SMARTSENS2_SENSOR_ID_PROX_WU:
        {
            ret = "Proximity wake up";
            break;
        }
        default:
        {
            if ( ( sensor_id >= SMARTSENS2_SENSOR_ID_CUSTOM_START ) && ( sensor_id <= SMARTSENS2_SENSOR_ID_CUSTOM_END ) )
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

// ------------------------------------------------------------------------ END
