
---
# EZO Carrier EC Click

> [EZO Carrier EC Click](https://www.mikroe.com/?pid_product=MIKROE-6011) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6011&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of EZO Carrier EC Click board by processing
  the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EZOCarrierEC

### Example Key Functions

- `ezocarrierec_cfg_setup` Config Object Initialization function.
```c
void ezocarrierec_cfg_setup ( ezocarrierec_cfg_t *cfg );
```

- `ezocarrierec_init` Initialization function.
```c
err_t ezocarrierec_init ( ezocarrierec_t *ctx, ezocarrierec_cfg_t *cfg );
```

- `ezocarrierec_send_cmd` Send command function.
```c
void ezocarrierec_send_cmd ( ezocarrierec_t *ctx, uint8_t *cmd );
```

- `ezocarrierec_send_cmd_with_par` Send command function with parameter.
```c
void ezocarrierec_send_cmd_with_par ( ezocarrierec_t *ctx, uint8_t *cmd, uint8_t *param_buf );
```

- `ezocarrierec_send_cmd_check` Check the sent command.
```c
void ezocarrierec_send_cmd_check ( ezocarrierec_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver, performs the Click default factory reset, and single point calibration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ezocarrierec_cfg_t ezocarrierec_cfg;  /**< Click config object. */

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
    ezocarrierec_cfg_setup( &ezocarrierec_cfg );
    EZOCARRIEREC_MAP_MIKROBUS( ezocarrierec_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ezocarrierec_init( &ezocarrierec, &ezocarrierec_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, "Device status \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_STATUS );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    log_printf( &logger, "Factory reset \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_FACTORY );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_READY );
    ezocarrierec_error_check( error_flag );

    #define PROBE_TYPE   "1.0"
    log_printf( &logger, "Seting Probe type \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_SET_PROBE_TYPE, PROBE_TYPE );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    log_printf( &logger, "Device info \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_DEV_INFO );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    #define DRY_CALIBRATION   "dry"
    log_printf( &logger, "Dry calibration \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_CAL, DRY_CALIBRATION );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    uint8_t n_cnt = 0;
    uint8_t last_reading[ APP_BUFFER_SIZE ] = { 0 };
    ezocarrierec_clear_app_buf( );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_SINGLE_READ );
    ezocarrierec_process ( &ezocarrierec );
    strcpy( last_reading, app_buf );
    log_printf( &logger, "Single point calibration \r\n" );
    log_printf( &logger, "Waiting for stable readings \r\n" );
    while ( n_cnt <= 5 )
    {
        if ( EZOCARRIEREC_OK == ezocarrierec_process ( &ezocarrierec ) )
        {  
            if ( 0 == strstr( app_buf, last_reading ) )
            {
                n_cnt++;
            }
            else
            {
                strcpy( last_reading, app_buf );
                n_cnt = 0;
            }
        }
        log_printf( &logger, "- " );
        Delay_ms ( 1000 );
        ezocarrierec_clear_app_buf( );
    }
    #define CALIBRATION_VALUE   "80"
    log_printf( &logger, "Calibration \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_CAL, CALIBRATION_VALUE );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    #define DISABLE_CONT_READ   "0"
    log_printf( &logger, "Disable continuous reading mode \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_CONT_READ, DISABLE_CONT_READ );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and processes all incoming conductivity data from the probe, and displays them on the USB UART in uS.

```c
void application_task ( void ) 
{
    log_printf( &logger, "Reading... \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_SINGLE_READ );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

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
