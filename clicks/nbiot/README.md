
---
# NB IoT Click

> [NB IoT Click](https://www.mikroe.com/?pid_product=MIKROE-3294) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3294&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from NB IoT Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NbIot

### Example Key Functions

- `nbiot_cfg_setup` NB IoT configuration object setup function. 
```c
void nbiot_cfg_setup ( nbiot_cfg_t *cfg );
``` 
 
- `nbiot_init` NB IoT initialization function. 
```c
err_t nbiot_init ( nbiot_t *ctx, nbiot_cfg_t *cfg );
```

- `nbiot_send_cmd` Send command function. 
```c
void nbiot_send_cmd ( nbiot_t *ctx, char *cmd );
```
 
- `nbiot_power_on` NB IoT module power on. 
```c
void nbiot_power_on ( nbiot_t *ctx );
```

- `nbiot_generic_write` NB IoT data writing function. 
```c
err_t nbiot_generic_write ( nbiot_t *ctx, char *data_buf, uint16_t len );
```

### Application Init

> Initializes driver, wake-up module and sets default configuration for connecting device to network.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot_cfg_t nbiot_cfg;  /**< Click config object. */

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
    Delay_ms ( 1000 );
    
    // Click initialization.
    nbiot_cfg_setup( &nbiot_cfg );
    NBIOT_MAP_MIKROBUS( nbiot_cfg, MIKROBUS_1 );
    err_t init_flag  = nbiot_init( &nbiot, &nbiot_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power on device... " );
    nbiot_power_on( &nbiot );
    // dummy read
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    
    // AT
    nbiot_send_cmd( &nbiot, NBIOT_CMD_AT );
    app_error_flag = nbiot_rsp_check( );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // ATI - product information
    nbiot_send_cmd( &nbiot, NBIOT_CMD_ATI );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    nbiot_send_cmd( &nbiot, NBIOT_CMD_CGMR );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
    
    // COPS - deregister from network
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_COPS, "2" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
     
    // CFUN - full funtionality
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_CFUN, "1" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_COPS, "0" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CEREG - network registration status
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_CEREG, "2" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CIMI - request IMSI
    nbiot_send_cmd( &nbiot, NBIOT_CMD_CIMI );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
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

> Waits for device to connect to network and then checks the signal quality 
> every 5 seconds. All data is being logged on USB UART where you can track their changes.

```c
void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        // CGATT - request IMSI
        nbiot_send_cmd_check( &nbiot, NBIOT_CMD_CGATT );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CEREG - network registration status
        nbiot_send_cmd_check( &nbiot, NBIOT_CMD_CEREG );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        nbiot_send_cmd( &nbiot, NBIOT_CMD_CSQ );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        log_info( &logger, "CHECKING SIGNAL QUALITY" );
        nbiot_send_cmd( &nbiot, NBIOT_CMD_CSQ );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

### Note

> In order for the example to work, a valid SIM card needs to be entered.

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
