
---
# 4G LTE-NA  Click

> [4G LTE-NA Click](https://www.mikroe.com/?pid_product=MIKROE-2535) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2535&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from 4G LTE NA Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.4GLTENA

### Example Key Functions

- `c4gltena_cfg_setup` Config Object Initialization function.
```c
void c4gltena_cfg_setup ( c4gltena_cfg_t *cfg );
```

- `c4gltena_init` Initialization function.
```c
err_t c4gltena_init ( c4gltena_t *ctx, c4gltena_cfg_t *cfg );
```

- `c4gltena_module_power_on` This function powers ON the module.
```c
void c4gltena_module_power_on ( c4gltena_t *ctx );
```

- `c4gltena_send_cmd_with_parameter` This function sends a command with specified parameter to the Click module.
```c
void c4gltena_send_cmd_with_parameter ( c4gltena_t *ctx, char *at_cmd_buf, char *param_buf );
```

- `c4gltena_send_cmd_parameter_check` This function checks the command that is sent.
```c
void c4gltena_send_cmd_parameter_check ( c4gltena_t *ctx, char *at_cmd_buf );
```

### Application Init

> Initializes the driver and powers up the module, then sets default configuration for connecting the device to network.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4gltena_cfg_t c4gltena_cfg;  /**< Click config object. */

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

    c4gltena_cfg_setup( &c4gltena_cfg );
    C4GLTENA_MAP_MIKROBUS( c4gltena_cfg, MIKROBUS_1 );
    c4gltena_init( &c4gltena, &c4gltena_cfg );
    
    c4gltena_module_power_on( &c4gltena );
    
    // dummy read
    c4gltena_process( );
    c4gltena_clear_app_buf( );
    
    // AT
    c4gltena_send_cmd( &c4gltena, C4GLTENA_CMD_AT );
    app_error_flag = c4gltena_rsp_check( );
    c4gltena_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // ATI - product information
    c4gltena_send_cmd( &c4gltena, C4GLTENA_CMD_ATI );
    app_error_flag = c4gltena_rsp_check(  );
    c4gltena_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    c4gltena_send_cmd( &c4gltena, C4GLTENA_CMD_CGMR );
    app_error_flag = c4gltena_rsp_check(  );
    c4gltena_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CMEE - Report Mobile Equipment Error
    c4gltena_send_cmd_with_parameter( &c4gltena, C4GLTENA_CMD_CMEE, "2" );
    app_error_flag = c4gltena_rsp_check(  );
    c4gltena_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - deregister from network
    c4gltena_send_cmd_with_parameter( &c4gltena, C4GLTENA_CMD_COPS, "2" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    app_error_flag = c4gltena_rsp_check(  );
    c4gltena_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGDCONT - set sim apn
    c4gltena_set_sim_apn( &c4gltena, SIM_APN );
    app_error_flag = c4gltena_rsp_check(  );
    c4gltena_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CFUN - full funtionality
    c4gltena_send_cmd_with_parameter( &c4gltena, C4GLTENA_CMD_CFUN, "1" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    app_error_flag = c4gltena_rsp_check(  );
    c4gltena_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    c4gltena_send_cmd_with_parameter( &c4gltena, C4GLTENA_CMD_COPS, "0" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    app_error_flag = c4gltena_rsp_check(  );
    c4gltena_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CREG - network registration status
    c4gltena_send_cmd_with_parameter( &c4gltena, C4GLTENA_CMD_CREG, "1" );
    app_error_flag = c4gltena_rsp_check(  );
    c4gltena_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Waits for device to connect to network and then sends a desired SMS to the selected phone number approximately every 30 seconds.

```c
void application_task ( void ) 
{
    if ( app_connection_status == WAIT_FOR_CONNECTION ) {
        // CREG - network registration status
        c4gltena_send_cmd_check( &c4gltena, C4GLTENA_CMD_CREG );
        app_error_flag = c4gltena_rsp_check(  );
        c4gltena_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        c4gltena_send_cmd( &c4gltena, C4GLTENA_CMD_CSQ );
        app_error_flag = c4gltena_rsp_check(  );
        c4gltena_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    } else {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        c4gltena_send_cmd_with_parameter( &c4gltena, C4GLTENA_CMD_CMGF, "0" );
        app_error_flag = c4gltena_rsp_check(  );
        c4gltena_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        for( ; ; ) {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            c4gltena_send_sms_pdu ( &c4gltena, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = c4gltena_rsp_check(  );
            c4gltena_error_check( app_error_flag );
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
        }
    }
}
```

### Note

> In order for the example to work, user needs to set the phone number to which he wants 
> to send an SMS, and also will need to set an APN and SMSC (required for PDU mode only) of entered SIM card.
> Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
>> E.g. 
   >> * SIM_APN "vipmobile"
   >> * SIM_SMSC "+381610401"
   >> * PHONE_NUMBER_TO_MESSAGE "+381659999999"

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
