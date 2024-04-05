/*!
 * @file main.c
 * @brief BLE TINY Click Example.
 *
 * # Description
 * This example reads and processes data from BLE TINY clicks.
 * Application waits for connection with Click board with phone.
 * Then checks its Coadless FW version and checks connected device.
 * Then waits for command to be stored in it's memory on 0 slot.
 * After that depending on the command stored it executes that type of example.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and resets device and seds Disconnect and Reset IO commands.
 * Then it waits for the connection to device. When connected it sends commands to
 * check Coadless FW, connected device, its BLE address and signal quality of
 * connection. In the end it waits for command from its memory. After valid
 * command is stored in memory on 0 slot it contines to Application Task.
 *
 * ## Application Task
 * Executes one of thre application task selected in Application Init:I2C, SPI, APP.
 * I2C example uses EEPROM Click board to write and read data of its memory.
 * SPI example uses EEPROM 2 Click board to write and read data of its memory.
 * APP example just reads UART data and logs it to UART Terminal.
 *
 * ## Additional Function
 * - static void bletiny_clear_app_buf ( void )
 * - static err_t bletiny_process ( void )
 * - static void bletiny_error_check( err_t error_flag );
 * - static void bletiny_log_app_buf ( void );
 * - static err_t bletiny_rsp_check ( void );
 * - static void bletiny_example_init ( void );
 * - static void bletiny_application_example ( void );
 * - static void bletiny_i2c_example ( void );
 * - static void bletiny_spi_example ( void );
 *
 * @note
 * For this application you need to install Dialog's mobile application SmartConsole.
 * This application I2C example is created using EEPROM Click board, and for SPI
 * example EEPROM 2 Click board is used.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bletiny.h"
#include "conversions.h"

/**
 * @brief Application receiver buffer size
 * @details Specified size of application receiver buffer.
 */
#define PROCESS_BUFFER_SIZE 200

/**
 * @brief Application example type.
 * @details Specified application example type.
 */
typedef enum
{
    BLETINY_APP_CTRL,
    BLETINY_I2C_EXAMPLE,
    BLETINY_SPI_EXAMPLE
}bletiny_example_type_t;

/**
 * @brief Application example state.
 * @details Specified application example state.
 */
typedef enum
{
    BLETINY_CONFIGURE_MASTER,
    BLETINY_CONFIGURE_SLAVE,
    BLETINY_EXAMPLE
}bletiny_example_state_t;

static bletiny_t bletiny;
static log_t logger;

/**
 * @brief Application @b app_buf and its @b app_buf_cnt and @b app_buf_len.
 * @details Application receiver buffer and its counter and current length.
 */
static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief Application example type and state.
 * @details Application example type and state variables.
 */
static bletiny_example_type_t example_type;
static bletiny_example_state_t example_state;

/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 */
static void bletiny_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t bletiny_process ( void );

/**
 * @brief Parse errors.
 * @details This function checks for different types of errors and logs them on UART.
 */
static void bletiny_error_check( err_t error_flag );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void bletiny_log_app_buf ( void );

/**
 * @brief Response check.
 * @details This function checks for response and returns the status of response.
 *
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t bletiny_rsp_check ( void );

/**
 * @brief Selecting application task.
 * @details This function selects application task that will be executed.
 * @note Select task by sending command for sending string in memory(0 slot)
 * with phone application. Example of command: AT+MEM=0,I2C. If memory is
 * not empty the string detected will be shown on UART Terminal.
 */
static void bletiny_example_init ( void );

/**
 * @brief Application example.
 * @details This function executes task for using phone application.
 * @note Example logs if any data is read from Click board. This example
 * should be selected if you want to control device with phone application.
 */
static void bletiny_application_example ( void );

/**
 * @brief I2C example.
 * @details This function executes task for using EEPROM Click board.
 * @note Example configures IO pins for I2C communication and configures I2C.
 * Then writes "MikroE" to memory of EEPROM Click board and then reads it
 * back and logs it to UART Terminal.
 */
static void bletiny_i2c_example ( void );

/**
 * @brief SPI example.
 * @details This function executes task for using EEPROM 2 Click board.
 * @note Example configures IO pins for SPI communication and configures SPI.
 * When configured, it sends command for enableing write to Click board memory.
 * Then writes "MikroE" to memory of EEPROM 2 Click board and then reads it
 * back and logs it to UART Terminal.
 */
static void bletiny_spi_example ( void );

/**
 * @brief Clear every @b chr from @b str.
 * @details This function clears every occurance of @b chr from @b str.
 */
static void bletiny_clear_char( uint8_t *str, char chr );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bletiny_cfg_t bletiny_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\nApplication Init\r\n" );
    Delay_ms ( 1000 );

    // Click initialization.
    bletiny_cfg_setup( &bletiny_cfg );
    BLETINY_MAP_MIKROBUS( bletiny_cfg, MIKROBUS_1 );
    err_t init_flag  = bletiny_init( &bletiny, &bletiny_cfg );

    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    bletiny_default_cfg ( &bletiny );

    bletiny_send_cmd( &bletiny, BLETINY_CMD_ATR );
    bletiny_send_cmd( &bletiny, BLETINY_CMD_ATZ );
    bletiny_send_cmd( &bletiny, BLETINY_CMD_GAPDISCONNECT );
    bletiny_process( );
    bletiny_clear_app_buf( );

    app_buf_len = 0;
    app_buf_cnt = 0;

    //wait for connection
    log_printf( &logger, " Waiting for phone to connect\r\n" );
    while ( 0 == strstr( app_buf, BLETINY_CONNECTED ) )
    {
        bletiny_process( );
    }
    log_printf( &logger, " Connected\r\n" );
    bletiny_clear_app_buf( );
    //send ATI command to check Codless FW
    bletiny_send_cmd( &bletiny, BLETINY_CMD_ATI );
    volatile err_t app_error_flag = bletiny_rsp_check();
    if ( BLETINY_OK == app_error_flag )
    {
        bletiny_log_app_buf();
        log_printf( &logger, "-----------------------------------\r\n" );
    }
    else
    {
        bletiny_error_check( app_error_flag );
    }
    Delay_ms ( 1000 );
    //send command to check ble address
    bletiny_send_cmd( &bletiny, BLETINY_CMD_BDADDR );
    app_error_flag = bletiny_rsp_check();
    if ( BLETINY_OK == app_error_flag )
    {
        bletiny_log_app_buf();
        log_printf( &logger, "-----------------------------------\r\n" );
    }
    else
    {
        bletiny_error_check( app_error_flag );
    }
    Delay_ms ( 1000 );
    //send ATrI command to check remote connected device
    bletiny_send_cmd( &bletiny, BLETINY_CMD_ATRI );
    app_error_flag = bletiny_rsp_check();
    if ( BLETINY_OK == app_error_flag )
    {
        bletiny_log_app_buf();
        log_printf( &logger, "-----------------------------------\r\n" );
    }
    else
    {
        bletiny_error_check( app_error_flag );
    }
    Delay_ms ( 1000 );
    //send RSSI command to check signal quality
    bletiny_send_cmd( &bletiny, BLETINY_CMD_RSSI );
    app_error_flag = bletiny_rsp_check();
    if ( BLETINY_OK == app_error_flag )
    {
        bletiny_log_app_buf();
        log_printf( &logger, "-----------------------------------\r\n" );
    }
    else
    {
        bletiny_error_check( app_error_flag );
    }
    //select example to execute
    bletiny_example_init( );

    bletiny_clear_app_buf( );
    log_printf( &logger, " Application Task \r\n" );
}

void application_task ( void )
{
    static uint8_t info = 0;
    switch ( example_type )
    {
        case BLETINY_I2C_EXAMPLE:
        {
            if (!info)
            {
                info++;
                log_printf( &logger, " I2C example\r\n" );
                bletiny_process( );
                bletiny_clear_app_buf( );
            }
            bletiny_i2c_example( );
            break;
        }
        case BLETINY_SPI_EXAMPLE:
        {
            if (!info)
            {
                info++;
                log_printf( &logger, " SPI example\r\n" );
                bletiny_process( );
                bletiny_clear_app_buf( );
            }
            bletiny_spi_example( );
            break;
        }
        case BLETINY_APP_CTRL:
        {
            if (!info)
            {
                info++;
                log_printf( &logger, " Application example\r\n" );
                bletiny_process( );
                bletiny_clear_app_buf( );
            }
            bletiny_application_example( );
            break;
        }
        default:
        {
            break;
        }
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void bletiny_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t bletiny_process ( void )
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = bletiny_generic_read( &bletiny, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
           bletiny_clear_app_buf(  );
            return BLETINY_ERROR;
        }
        else
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ )
        {
            if ( rx_buff[ rx_cnt ] != 0 )
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }

        }
        return BLETINY_OK;
    }
    return BLETINY_ERROR;
}

static err_t bletiny_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 10000;

    err_t error_flag = bletiny_process(  );
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }

    while ( ( strstr( app_buf, BLETINY_RSP_OK ) == 0 ) &&
            ( strstr( app_buf, BLETINY_RSP_ERROR ) == 0 ) )
    {
        error_flag = bletiny_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }

        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            bletiny_clear_app_buf(  );
            return BLETINY_ERROR_TIMEOUT;
        }

        Delay_ms ( 1 );
    }

    if ( strstr( app_buf, BLETINY_RSP_OK ) )
        return BLETINY_OK;
    else if ( strstr( app_buf, BLETINY_RSP_ERROR ) )
        return BLETINY_ERROR_RETURN;
    else
        return BLETINY_ERROR_UNKNOWN;
}

static void bletiny_error_check( err_t error_flag )
{
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        switch ( error_flag )
        {
            case -2:
                log_error( &logger, " Overflow!" );
                break;
            case -3:
                log_error( &logger, " Timeout!" );
                break;
            default:
                break;
        }
    }
}

static void bletiny_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    bletiny_clear_app_buf(  );
}

static void bletiny_example_init ( void )
{
    #define EXAMPLE_CMD_LEN 6
    char EXAMPLE_CMD[ EXAMPLE_CMD_LEN ][ 4 ] = { "I2C", "i2c", "SPI", "spi", "APP", "app" };
    log_info( &logger, " Send value to 0 memory index via phone app to select example type." );
    log_info( &logger, " Example of command is: AT+MEM=0,I2C" );
    log_info( &logger, " Types:\r\n > SPI\r\n > I2C \r\n > APP" );

    for ( ; ; )
    {
        bletiny_send_cmd( &bletiny, BLETINY_CMD_CHECK_MEM );

        if ( BLETINY_OK == bletiny_rsp_check() )
        {
            bletiny_clear_char(app_buf, 13);
            bletiny_clear_char(app_buf, 10);

            volatile char *__generic_ptr ok_rsp = strstr( app_buf, BLETINY_RSP_OK );

            if ( ok_rsp )
            {
                for ( uint8_t index = 0; index < EXAMPLE_CMD_LEN; index++ )
                {
                    if ( 0 != strstr(app_buf, EXAMPLE_CMD[ index ]) )
                    {
                        log_printf( &logger, " cmd foud: %s\r\n", EXAMPLE_CMD[ index ] );
                        bletiny_clear_app_buf( );
                        bletiny_send_cmd( &bletiny, BLETINY_CMD_CLEAR_MEM );
                        Delay_ms ( 500 );
                        bletiny_process( );
                        bletiny_clear_app_buf( );
                        if ( index < 2 )
                        {
                            example_type = BLETINY_I2C_EXAMPLE;
                            example_state = BLETINY_CONFIGURE_MASTER;
                            return;
                        }
                        else if ( index < 4 )
                        {
                            example_type = BLETINY_SPI_EXAMPLE;
                            example_state = BLETINY_CONFIGURE_MASTER;
                            return;
                        }
                        else
                        {
                            example_type = BLETINY_APP_CTRL;
                            return;
                        }
                    }
                }
                char *__generic_ptr echo_rsp = strstr( app_buf, BLETINY_CMD_CHECK_MEM );

                if (echo_rsp)
                {
                    echo_rsp += sizeof(BLETINY_CMD_CHECK_MEM);
                }
                else
                {
                    echo_rsp = app_buf;
                }

                if ( strcmp(echo_rsp, ok_rsp) )
                {
                    log_printf( &logger, " cmd not found but found: " );
                    while (echo_rsp != ok_rsp)
                    {
                        log_printf( &logger, "%c", *echo_rsp );
                        echo_rsp++;
                    }
                    log_printf( &logger, "\r\n" );
                }
            }
            bletiny_clear_app_buf(  );
        }

        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }

    Delay_ms ( 1000 );
}

static void bletiny_application_example ( void )
{
    bletiny_process( );
    if ( app_buf_len > 0 )
    {
        log_printf( &logger, "%s", app_buf );
        bletiny_clear_app_buf(  );
    }
}

static void bletiny_i2c_example ( void )
{
    switch ( example_state )
    {
        case BLETINY_CONFIGURE_MASTER:
        {
            log_printf( &logger, " Configure master for I2C communication\r\n" );
            bletiny_i2c_config( &bletiny, BLETINY_I2C_CFG_SPEED_100KHZ, BLETINY_I2C_CFG_REG_LEN_1BYTE );
            example_state = BLETINY_EXAMPLE;
            break;
        }
        case BLETINY_EXAMPLE:
        {
            char mem_value[ 16 ] = "MikroE";
            log_printf ( &logger, "Writing Mikroe to EEPROM click\r\n" );
            for ( uint8_t cnt = 0; cnt < 6; cnt++ )
            {
                bletiny_i2c_write( &bletiny, 0x50, cnt + 1, mem_value[ cnt ] );
                Delay_ms ( 100 );
            }

            if ( BLETINY_OK == bletiny_i2c_read ( &bletiny, 0x50, 0x01 , mem_value, 6 ) )
            {
                log_printf ( &logger, "Data read: %s\r\n", mem_value );
            }

            break;
        }
        default:
        {
            break;
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

static void bletiny_spi_example ( void )
{
    switch ( example_state )
    {
        case BLETINY_CONFIGURE_MASTER:
        {
            log_printf( &logger, " Configure master for SPI communication\r\n" );

            bletiny_spi_config( &bletiny, BLETINY_SPI_CFG_SPEED_2MHZ, BLETINY_SPI_CFG_MODE0 );

            example_state = BLETINY_CONFIGURE_SLAVE;
            break;
        }
        case BLETINY_CONFIGURE_SLAVE:
        {
            uint8_t write_enable = 0x06;
            bletiny_spi_write( &bletiny, &write_enable, 1 );

            example_state = BLETINY_EXAMPLE;
            break;
        }
        case BLETINY_EXAMPLE:
        {
            uint8_t buf[ 10 ] = { 0x02, 0x00, 0x00, 0x01, 'M', 'i', 'k', 'r', 'o', 'E' };
            bletiny_spi_write ( &bletiny, buf, 10 );
            log_printf ( &logger, "Writing Mikroe to EEPROM 2 click\r\n" );
            Delay_ms ( 1000 );

            uint8_t data_in[ 4 ] = { 0x03, 0x00, 0x00, 0x01 };
            uint8_t read_data[ 7 ] = { 0 };
            bletiny_spi_write_then_read( &bletiny, data_in, 4, read_data, 6 );
            log_printf ( &logger, "Data read: %s\r\n", read_data );
            break;
        }
        default:
        {
            break;
        }
    }
    Delay_ms ( 1000 );
}

static void bletiny_clear_char( uint8_t *str, char chr )
{
    while ( 0 != strchr( str, chr ) )
    {
        str_cut_chr( str, chr );
    }
}

// ------------------------------------------------------------------------ END
