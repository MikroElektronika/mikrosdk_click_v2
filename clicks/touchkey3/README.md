
---
# TouchKey 3 Click

> [TouchKey 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2891) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2891&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This Click uses 7 capacitive sensing channels, with the #CHANGE pin routed to the INT pin of the mikroBUS&trade;, so that an interrupt can be triggered if any of the sensors detect a touch event. This can be used to trigger an SPI read cycle only when the key is actually pressed, avoiding the need for constant polling of the sensor registers.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchKey3

### Example Key Functions

- `touchkey3_cfg_setup` Config Object Initialization function. 
```c
void touchkey3_cfg_setup ( touchkey3_cfg_t *cfg );
``` 
 
- `touchkey3_init` Initialization function. 
```c
err_t touchkey3_init ( touchkey3_t *ctx, touchkey3_cfg_t *cfg );
```

- `touchkey3_default_cfg` Click Default Configuration function. 
```c
void touchkey3_default_cfg ( touchkey3_t *ctx );
```

- `touchkey3_send_command` Function executes one of the possible commands. 
```c
uint8_t touchkey3_send_command ( touchkey3_t *ctx, uint8_t command );
```
 
- `touchkey3_send_request` Function sends a request command, and returns the response. 
```c
uint8_t touchkey3_send_request ( touchkey3_t *ctx, uint8_t request, uint8_t * p_response );
```

- `touchkey3_get_data` Function reads from a selected configuration register. 
```c
uint8_t touchkey3_get_data ( uint8_t data_address, uint8_t * read_data );
```

### Application Init

> Initializes Click driver and performs a soft reset of the Click.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey3_cfg_t cfg;

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

    touchkey3_cfg_setup( &cfg );
    TOUCHKEY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey3_init( &touchkey3, &cfg );

    touchkey3_send_command( &touchkey3, TOUCHKEY3_CMD_RESET );
}
```

### Application Task

> Reads the status of the keys, and outputs a message if a key is touched.

```c
void application_task ( void )
{ 
    touchkey3_send_request( &touchkey3, TOUCHKEY3_REQ_ALL_KEYS, &return_data );

    for ( counter = 0; counter < 7; counter++ )
    {
        if ( ( return_data[ 1 ] >> counter ) & 0x01 )
        {
            log_info( &logger, "Touch detected on key " );
            //Converts the key index into ascii character ( 0 - 7 -> '1' - '7')
            temp = counter + 49;
            log_info( &logger, "%d\r\n", temp );
            Delay_ms ( 1000 );
        }
    }
    Delay_ms ( 200 );
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
