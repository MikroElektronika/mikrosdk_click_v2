
---
# Ambient 5 Click

> [Ambient 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3320) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3320&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application calculates the ambiance light.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient5

### Example Key Functions

- `ambient5_cfg_setup` Config Object Initialization function. 
```c
void ambient5_cfg_setup ( ambient5_cfg_t *cfg );
``` 
 
- `ambient5_init` Initialization function. 
```c
err_t ambient5_init ( ambient5_t *ctx, ambient5_cfg_t *cfg );
```

- `ambient5_default_cfg` Click Default Configuration function. 
```c
void ambient5_default_cfg ( ambient5_t *ctx );
```

- `ambient5_set_register` This function writes the register value to the desired register. 
```c
void ambient5_set_register ( ambient5_t *ctx, uint8_t reg_addr, uint16_t reg_value );
```
 
- `ambient5_get_register` This function reads data from the desired register. 
```c
uint16_t ambient5_get_register ( ambient5_t *ctx, uint8_t reg );
```

- `ambient5_get_resolution` This function calculates resolution of output data in "high resolution" and "white channel" registers. 
```c
float ambient5_get_resolution ( ambient5_t* ctx );
```

### Application Init

> Initializes i2c driver, powers the device and calculates refresh time

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient5_cfg_t ambient_cfg;

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

    ambient5_cfg_setup( &ambient_cfg );
    AMBIENT5_MAP_MIKROBUS( ambient_cfg, MIKROBUS_1 );
    ambient5_init( &ambient5, &ambient_cfg );
    ambient5_default_cfg( &ambient5 );

	log_printf( &logger, "App init done\r\n" );
}
```

### Application Task

> Logs high resolution ambient light data after a period of time.

```c
void application_task ( void )
{
    r_time = ambient5_get_refresh_time( &ambient5 );
    
    for (i = 0; i < r_time; i++)
	{
		Delay_ms ( 1 );
	}

	high_res_light_level = ambient5_get_high_resolution_light_level( &ambient5 );

	log_printf( &logger, " Ambient Light Level : %.2f lx\r\n", high_res_light_level );
	    
    Delay_ms ( 500 );
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
