/*!
 * \file 
 * \brief SmartDof Click example
 * 
 * # Description
 * This click integrates a triaxial accelerometer, triaxial gyroscope and magnetometer.
 * It can provide very accurate and precise 3D acceleration, magnetic, and angular velocity data, in real-time. 
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and Smart DOF device
 *  
 * ## Application Task  
 * Executes one of 'smartdof_xxx_task()' additional functions
 * 
 * *note:* 
 * <pre>
 * Additional Functions :
 * - accelerometer_task() - initializes accelerometer reports in 100000 micro second intervals, receives, parses and logs report data
 * - gyroscope_task() - initializes gyroscope calibrated reports in 100000 micro second intervals, receives, parses and logs report data
 * - magnetometer_task() - initializes magnetometer calibrated reports in 100000 micro second intervals, receives, parses and logs report data
 * </pre>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "smartdof.h"

// ------------------------------------------------------------------ VARIABLES

static smartdof_t smartdof;
static smartdof_rr_t smartdof_rr;
static smartdof_sfc_t smartdof_sfc;
static smartdof_pir_t smartdof_pir;
static log_t logger;

static uint8_t sensor_status;
static uint8_t aux_error_flag;
static uint8_t int_pin_flag;

static int16_t x_axis_i;
static int16_t y_axis_i;
static int16_t z_axis_i;
static float x_axis_f;
static float y_axis_f;
static float z_axis_f;

static uint8_t data_header[ 4 ];
static uint8_t data_buffer[ 300 ];
static uint16_t data_length;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void check_sensor_status ( )
{
    switch ( sensor_status )
    {
        case 0 :
        {
            log_printf( &logger, "unreliable\r\n" );
            break;
        }
        case 1 :
        {
            log_printf( &logger, "low\r\n" );
            break;
        }
        case 2 :
        {
            log_printf( &logger, "medium\r\n" );
            break;
        }
        case 3 :
        {
            log_printf( &logger, "high\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
}

void accelerometer_task ( smartdof_t *ctx, smartdof_sfc_t *sfc )
{
    sfc->feature_report_id = SMARTDOF_FEAT_REP_ID_ACCEL;
    sfc->feature_flags = 0x00; 
    sfc->change_sensitivity = 0x0000;
    sfc->report_interval = 100000;
    sfc->batch_interval = 0; 
    sfc->sensor_specific_config = 0;
     
    smartdof_set_feature_command( ctx, sfc );
    Delay_ms( 500 );
    aux_error_flag = smartdof_get_feature_response( ctx, sfc );
    if ( aux_error_flag != 0)
    {
        log_printf( &logger, "> Error setting feature\r\n" );
        for ( ; ; );
    }
    else
    {
        Delay_ms( 10 );
    }

    for ( ; ; )
    {
        aux_error_flag = smartdof_receive_packet( ctx, 10000000 );
        if ( aux_error_flag == 0 )
        {
            smartdof_get_data( ctx, &data_header[ 0 ], &data_length, &data_buffer[ 0 ] );
            if ( ( data_buffer[ 0 ] == SMARTDOF_FEAT_REP_ID_BASE_TIMESTAMP ) && ( data_buffer[ 5 ] == SMARTDOF_FEAT_REP_ID_ACCEL ) )
            {
                sensor_status = data_buffer[ 7 ];
                
                x_axis_i = 0;
                y_axis_i = 0;
                z_axis_i = 0;
                x_axis_i |= data_buffer[ 10 ];
                x_axis_i <<= 8;
                x_axis_i |= data_buffer[ 9 ];
                y_axis_i |= data_buffer[ 12 ];
                y_axis_i <<= 8;
                y_axis_i |= data_buffer[ 11 ];
                z_axis_i |= data_buffer[ 14 ];
                z_axis_i <<= 8;
                z_axis_i |= data_buffer[ 13 ];
                x_axis_f = smartdof_q_point_to_float( x_axis_i, SMARTDOF_QPOINT_ACCEL );
                y_axis_f = smartdof_q_point_to_float( y_axis_i, SMARTDOF_QPOINT_ACCEL );
                z_axis_f = smartdof_q_point_to_float( z_axis_i, SMARTDOF_QPOINT_ACCEL );

                log_printf( &logger, "\r\n" );
                log_printf( &logger, "Sensor type     : accelerometer\r\n" );
                log_printf( &logger, "Sensor accuracy : " );

                check_sensor_status( );

                log_printf( &logger, "X-Axis : %.2f m/s^2\r\n", x_axis_f );
                log_printf( &logger, "Y-Axis : %.2f m/s^2\r\n", y_axis_f );
                log_printf( &logger, "Z-Axis : %.2f m/s^2\r\n", z_axis_f );
            }
        }
        Delay_ms( 1 );
    }
}

void magnetometer_task ( smartdof_t *ctx, smartdof_sfc_t *sfc )
{
    sfc->feature_report_id      = SMARTDOF_FEAT_REP_ID_MAGNET;
    sfc->feature_flags          = 0x00; 
    sfc->change_sensitivity     = 0x0000;
    sfc->report_interval        = 100000;
    sfc->batch_interval         = 0; 
    sfc->sensor_specific_config = 0;
    smartdof_set_feature_command( ctx, sfc);
    Delay_ms( 500 );
    aux_error_flag = smartdof_get_feature_response( &smartdof, &smartdof_sfc );
    if ( aux_error_flag != 0 )
    {
        log_printf( &logger, "> Error setting feature\r\n" );
        for ( ; ; );
    }
    else
    {
        Delay_ms( 10 );
    }

    for ( ; ; )
    {
        aux_error_flag = smartdof_receive_packet( &smartdof, 10000000 );
        if ( aux_error_flag == 0 )
        {
            smartdof_get_data( ctx, &data_header[ 0 ], &data_length, &data_buffer[ 0 ] );
            if ( ( data_buffer[ 0 ] == SMARTDOF_FEAT_REP_ID_BASE_TIMESTAMP ) && ( data_buffer[ 5 ] == SMARTDOF_FEAT_REP_ID_MAGNET ) )
            {
                sensor_status = data_buffer[ 7 ];

                x_axis_i = 0;
                y_axis_i = 0;
                z_axis_i = 0;
                x_axis_i |= data_buffer[ 10 ];
                x_axis_i <<= 8;
                x_axis_i |= data_buffer[ 9 ];
                y_axis_i |= data_buffer[ 12 ];
                y_axis_i <<= 8;
                y_axis_i |= data_buffer[ 11 ];
                z_axis_i |= data_buffer[ 14 ];
                z_axis_i <<= 8;
                z_axis_i |= data_buffer[ 13 ];
                x_axis_f = smartdof_q_point_to_float( x_axis_i, SMARTDOF_QPOINT_MAGNET_CALIB );
                y_axis_f = smartdof_q_point_to_float( y_axis_i, SMARTDOF_QPOINT_MAGNET_CALIB );
                z_axis_f = smartdof_q_point_to_float( z_axis_i, SMARTDOF_QPOINT_MAGNET_CALIB );

                log_printf( &logger, "Sensor type     : magnetometer\r\n" );
                log_printf( &logger, "Sensor accuracy : " );

                check_sensor_status( );

                log_printf( &logger, "X-Axis : %.2f uTesla\r\n", x_axis_f );
                log_printf( &logger, "Y-Axis : %.2f uTesla\r\n", y_axis_f );
                log_printf( &logger, "Z-Axis : %.2f uTesla\r\n", z_axis_f );
            }
        }
        Delay_ms( 1 );
    }
}

void gyroscope_task ( smartdof_t *ctx, smartdof_sfc_t *sfc )
{
    sfc->feature_report_id      = SMARTDOF_FEAT_REP_ID_GYRO;
    sfc->feature_flags          = 0x00; 
    sfc->change_sensitivity     = 0x0000;
    sfc->report_interval        = 100000;
    sfc->batch_interval         = 0; 
    sfc->sensor_specific_config = 0;
    smartdof_set_feature_command( ctx, sfc );
    Delay_ms( 500 );
    aux_error_flag = smartdof_get_feature_response( ctx, sfc );
    if ( aux_error_flag != 0)
    {
        log_printf( &logger, "> Error setting feature\r\n" );
        for ( ; ; );
    }
    else
    {
        Delay_ms( 10 );
    }

    for ( ; ; )
    {
        aux_error_flag = smartdof_receive_packet( &smartdof, 10000000 );
        if ( aux_error_flag == 0 )
        {
            smartdof_get_data( ctx, &data_header[ 0 ], &data_length, &data_buffer[ 0 ] );
            if ( ( data_buffer[ 0 ] == SMARTDOF_FEAT_REP_ID_BASE_TIMESTAMP ) && ( data_buffer[ 5 ] == SMARTDOF_FEAT_REP_ID_GYRO ) )
            {
                sensor_status = data_buffer[ 7 ];

                x_axis_i = 0;
                y_axis_i = 0;
                z_axis_i = 0;
                x_axis_i |= data_buffer[ 10 ];
                x_axis_i <<= 8;
                x_axis_i |= data_buffer[ 9 ];
                y_axis_i |= data_buffer[ 12 ];
                y_axis_i <<= 8;
                y_axis_i |= data_buffer[ 11 ];
                z_axis_i |= data_buffer[ 14 ];
                z_axis_i <<= 8;
                z_axis_i |= data_buffer[ 13 ];
                x_axis_f = smartdof_q_point_to_float( x_axis_i, SMARTDOF_QPOINT_GYRO_CALIB );
                y_axis_f = smartdof_q_point_to_float( y_axis_i, SMARTDOF_QPOINT_GYRO_CALIB );
                z_axis_f = smartdof_q_point_to_float( z_axis_i, SMARTDOF_QPOINT_GYRO_CALIB );

                log_printf( &logger, " \r\n" );
                log_printf( &logger, "Sensor type     : gyroscope\r\n" );
                log_printf( &logger, "Sensor accuracy : " );

                check_sensor_status( );

                log_printf( &logger, "X-Axis : %f rad/s\r\n", x_axis_f );
                log_printf( &logger, "Y-Axis : %f rad/s\r\n", y_axis_f );
                log_printf( &logger, "Z-Axis : %f rad/s\r\n", z_axis_f );
            }
        }
        Delay_ms( 1 );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    uint8_t p;
    log_cfg_t log_cfg;
    smartdof_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    smartdof_cfg_setup( &cfg );
    SMARTDOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smartdof_init( &smartdof, &cfg );

    if ( smartdof_default_cfg ( &smartdof ) !=0 )
    {
        log_info( &logger, "Error during default configuration" );
    }
}

void application_task ( void )
{
    magnetometer_task( &smartdof, &smartdof_sfc );
    //accelerometer_task( &smartdof, &smartdof_sfc );
    //gyroscope_task( &smartdof, &smartdof_sfc );  
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
