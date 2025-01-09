
---
# Thermostat 4 Click

> [Thermostat 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4194) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4194&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> Thermostat 4 Click reads alert on the warm and hot channel, using standard SPI communication.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat4

### Example Key Functions

- `thermostat4_cfg_setup` Config Object Initialization function.
```c
void thermostat4_cfg_setup ( thermostat4_cfg_t *cfg ); 
```

- `thermostat4_init` Initialization function.
```c
err_t thermostat4_init ( thermostat4_t *ctx, thermostat4_cfg_t *cfg );
```

- `thermostat4_hot_alert_state` This function read state from OA pin
```c
uint8_t thermostat4_hot_alert_state ( thermostat4_t *ctx );
```
 
- `thermostat4_relay_ctrl` This function write desired state on RLY pin
```c
void thermostat4_relay_ctrl ( thermostat4_t *ctx, uint8_t state );
```

- `thermostat4_set_warm_hysteresis` This function write hysteresis data.
```c
void thermostat4_set_warm_hysteresis ( thermostat4_t *ctx, uint8_t hyst_data );
```

### Application Init

> Initializes Driver init, Relay test and
> sets hysteresis on the WARM channel ( channel B ), after that starts uploading new data.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat4_cfg_t thermostat4_cfg;

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
    thermostat4_cfg_setup( &thermostat4_cfg );
    THERMOSTAT4_MAP_MIKROBUS( thermostat4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermostat4_init( &thermostat4, &thermostat4_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_printf( &logger, " RELAY ON\r\n" );
    thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    Delay_ms ( 1000 );
    log_printf( &logger, " RELAY OFF\r\n" );
    thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_OFF );
    Delay_ms ( 500 );
    
    thermostat4_set_warm_hysteresis( &thermostat4, 0 );
    thermostat4_new_cfg_upload( &thermostat4 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads Alert on the WARM and HOT channel. 

```c
void application_task ( void )
{
    if ( THERMOSTAT4_HOT_ALERT == thermostat4_hot_alert_state( &thermostat4 ) ) 
    {
        log_printf( &logger, " HOT ALERT\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    } 
    else if ( THERMOSTAT4_WARM_ALERT == thermostat4_warm_alert_state( &thermostat4 ) ) 
    {
        log_printf( &logger, " WARM ALERT\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    } 
    else 
    { 
        log_printf( &logger, " TEMPERATURE OK\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_OFF );
    }  
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> The user has the option of adjusting the hysteresis for channel B via the SPI module 
> while for channel A it is adjusted via the potentiometer. 

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
