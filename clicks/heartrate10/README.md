
---
# Heart Rate 10 Click

> [Heart Rate 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4724) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4724&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases ability for device to read Heart Rate with 4 different diodes.
There is IR, Red, Green and Blue. You can control every one of them individualy, and 
change theirs sequence in FIFO register. All leds data is read from FIFO register, 
it's 19bit data for every led.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate10

### Example Key Functions

- `heartrate10_cfg_setup` Config Object Initialization function.
```c
void heartrate10_cfg_setup ( heartrate10_cfg_t *cfg );
```

- `heartrate10_init` Initialization function.
```c
err_t heartrate10_init ( heartrate10_t *ctx, heartrate10_cfg_t *cfg );
```

- `heartrate10_default_cfg` Click Default Configuration function.
```c
void heartrate10_default_cfg ( heartrate10_t *ctx );
```

- `heartrate10_generic_write` Writing function.
```c
err_t heartrate10_generic_write ( heartrate10_t *ctx, uint8_t reg, uint8_t tx_data )
```

- `heartrate10_reset` Reset device.
```c
void heartrate10_reset ( heartrate10_t *ctx )
```

- `heartrate10_read_complete_fifo_data` Read all led samples.
```c
err_t heartrate10_read_complete_fifo_data ( heartrate10_t *ctx, uint32_t *led1, uint32_t *led2, uint32_t *led3, uint32_t *led4 );
```

### Application Init

> Initialization of host communication periphrials and interrupt pin. Configures default
configuration to device where device is reset, checks Part ID and enables all 4 leds 
and sets sequence as IR-Red-Green-Blue. Sets their power to maximum, and enables 
interrupt on new data ready.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate10_cfg_t heartrate10_cfg;  /**< Click config object. */

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

    // Click initialization.
    heartrate10_cfg_setup( &heartrate10_cfg );
    HEARTRATE10_MAP_MIKROBUS( heartrate10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate10_init( &heartrate10, &heartrate10_cfg ) ) 
    {
        log_error( &logger, " Initializtion." );
        log_info( &logger, " Please, run example again... " );

        for ( ; ; );
    }
    
    if ( HEARTRATE10_ERROR == heartrate10_default_cfg ( &heartrate10 ) ) 
    {
        log_error( &logger, " Configuration." );
        log_info( &logger, " Please, run example again... " );

        for ( ; ; );
    }


```

### Application Task

> Reads FIFO data for all 4 didoes and logs them with separation character ','.

```c
void application_task ( void ) 
{   
    uint8_t rd_dat = 0;
    heartrate10_generic_read( &heartrate10, HEARTRATE10_REG_INT_STATUS, &rd_dat );
    if ( ( rd_dat & 0x40 ) )
    {        
        uint32_t ir, red, green, blue = 0;
        heartrate10_read_complete_fifo_data( &heartrate10, &ir, &red, &green, &blue );
        log_printf( &logger, "%lu,%lu,%lu,%lu\r\n", ir, red, green, blue );
    }
    Delay_ms ( 3 );
}
```

### Note

> For testing this example application SerialPlot was used. 
There you can see heart rate graphicly shown.

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
