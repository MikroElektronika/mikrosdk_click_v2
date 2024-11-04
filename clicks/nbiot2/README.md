\mainpage Main Page

---
# NB IoT 2 Click

> NB IoT 2 Click is a compact add-on board that contains a compact LTE Cat NB2 module with ultra-low power consumption. This board features the BC66-NA, a high-performance, multi-band LTE Cat NB2 module with extremely low power consumption from Quectel Wireless Solutions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nb_iot_2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nb-iot-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : UART type


# Software Support

We provide a library for the NB IoT 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NB IoT 2 Click driver.

#### Standard key functions :

- `nbiot2_cfg_setup` Config Object Initialization function.
```c
void nbiot2_cfg_setup ( nbiot2_cfg_t *cfg );
```

- `nbiot2_init` Initialization function.
```c
err_t nbiot2_init ( nbiot2_t *ctx, nbiot2_cfg_t *cfg );
```

#### Example key functions :

- `nbiot2_set_rst_pin_state` This function sets RST pin state.
```c
void nbiot2_set_rst_pin_state ( nbiot2_t *ctx, uint8_t state );
```

- `nbiot2_hw_reset` NB IoT 2 hardware reset function.
```c
void nbiot2_hw_reset ( nbiot2_t *ctx );
```

- `nbiot2_send_cmd` NB IoT 2 send command function.
```c
void nbiot2_send_cmd ( nbiot2_t *ctx, char *cmd );
```

## Example Description

> This example reads and processes data from NB IoT 2 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver, wake-up module and sets default configuration for connecting device to network.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot2_cfg_t nbiot2_cfg;  /**< Click config object. */

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
    nbiot2_cfg_setup( &nbiot2_cfg );
    NBIOT2_MAP_MIKROBUS( nbiot2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nbiot2_init( &nbiot2, &nbiot2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " - Reseting device... \r\n" );
    nbiot2_hw_reset( &nbiot2 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    app_error_flag = nbiot2_process( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd( &nbiot2, NBIOT2_CMD_AT );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd( &nbiot2, NBIOT2_CMD_ATI );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CFUN, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QSPCHSC, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CPSMS, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_set_apn( &nbiot2, SIM_APN );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );   
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QRST, "1" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    app_error_flag = nbiot2_process( );
    nbiot2_error_check( app_error_flag );  
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QBAND, "1,20" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );      
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CEREG, "2" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );   
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CSCON, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QNBIOTEVENT, "1,1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_SM, "LOCK" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QSCLK, "0" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    log_info( &logger, " Application Task " );
    
    app_connection_status = CONFIGURATION_FOR_EXAMPLE;
    
    app_buf_len = 0;
    app_buf_cnt = 0;
}

```

### Application Task

> This application is split into two examples:
 - TCP/UDP example - connecting to echo server and writing and reading data.
 - SMS example - Sending SMS message to desired number using TEXT or PDU mode. 

```c
void application_task ( void ) 
{   
    switch( app_connection_status )
    {
        case CONFIGURATION_FOR_EXAMPLE:
        {
            nbiot2_config_device_for_example( );
            break;
        }
        case EXAMPLE:
        {
            #if defined( NBIOT2_TCP_UDP_EXAMPLE )
                nbiot2_tcp_udp_example( );
            #endif   
            #if defined( NBIOT2_SMS_EXAMPLE )
                nbiot2_send_sms( );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
            #endif
            break;
        }
        default:
        {
            log_error( &logger, "Application status error!" );
            app_connection_status = CONFIGURATION_FOR_EXAMPLE;
            Delay_ms ( 1000 );
            break;
        }
    }
}
```

## Note

> In order for the examples to work, user needs to set the APN and SMSC (SMS PDU mode only) 
of entered SIM card as well as the phone number to which he wants to send an SMS.
Enter valid values for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
> > Example: 
> > - SIM_APN "internet"
> > - SIM_SMSC "+381610401"
> > - PHONE_NUMBER_TO_MESSAGE "+381659999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NBIoT2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
