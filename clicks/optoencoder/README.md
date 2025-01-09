
---
# Opto Encoder Click

> [Opto Encoder Click](https://www.mikroe.com/?pid_product=MIKROE-2549) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2549&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application is used to encode motion or rotation.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder

### Example Key Functions

- `optoencoder_cfg_setup` Config Object Initialization function. 
```c
void optoencoder_cfg_setup ( optoencoder_cfg_t *cfg );
``` 
 
- `optoencoder_init` Initialization function. 
```c
err_t optoencoder_init ( optoencoder_t *ctx, optoencoder_cfg_t *cfg );
```

- `optoencoder_getO1` Function for reading O1 state. 
```c
uint8_t optoencoder_getO1 ( optoencoder_t *ctx );
```
 
- `optoencoder_init_dev` Initialization function. 
```c
void optoencoder_init_dev ( optoencoder_t *ctx );
```

- `optoencoder_get_position` Function for reading the position of the encoder. 
```c
int16_t optoencoder_get_position ( optoencoder_t *ctx );
```

### Application Init

> Initializes driver and opto encoder.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    optoencoder_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    optoencoder_cfg_setup( &cfg );
    OPTOENCODER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    optoencoder_init( &optoencoder, &cfg );

    optoencoder_init_dev( &optoencoder );
}
```

### Application Task

> Depending on the direction of the movement it increments/decrements the step counter.

```c
void application_task ( )
{
    int16_t new_step;
    new_step = optoencoder_get_position( &optoencoder );
    if ( old_step != new_step)
    {
        log_printf( &logger, "Step: %d \r\n", new_step );
        old_step = new_step;
    }
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
