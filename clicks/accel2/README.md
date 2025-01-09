
---
# Accel 2 Click

> [Accel 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1905) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1905&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application is three-axis accelerometer which embeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel2

### Example Key Functions

- `accel2_cfg_setup` Config Object Initialization function. 
```c
void accel2_cfg_setup ( accel2_cfg_t *cfg );
``` 
 
- `accel2_init` Initialization function. 
```c
err_t accel2_init ( accel2_t *ctx, accel2_cfg_t *cfg );
```

- `accel2_generic_write` Generic write function. 
```c
void accel2_generic_write ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `accel2_check_id` Check Accel 2 ID. 
```c
uint8_t accel2_check_id ( accel2_t *ctx );
```
 
- `accel2_read_xaxis` Function read X axis. 
```c
uint16_t accel2_read_xaxis ( accel2_t *ctx );
```

- `accel2_read_yaxis` Function read Y axis. 
```c
uint16_t accel2_read_yaxis ( accel2_t *ctx );
```

### Application Init

> Initialization device. Check sensor ID and initialize Accel 2 Click.

```c
void application_init ( void )
{
   log_cfg_t log_cfg;
   accel2_cfg_t cfg;

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

   accel2_cfg_setup( &cfg );
   ACCEL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
   accel2_init( &accel2, &cfg );
}
```

### Application Task

> This is a example which demonstrates the use of Accel 2 Click board.
   Measured coordinates (X,Y,Z) are being sent to the UART where you can track their changes.

```c
void application_task ( void )
{
   int16_t value_x;
   int16_t value_y;
   int16_t value_z;
   uint8_t txt_x[ 15 ];
   uint8_t txt_y[ 15 ];
   uint8_t txt_z[ 15 ];

   value_x = accel2_read_xaxis( &accel2 );
   value_y = accel2_read_yaxis( &accel2 );
   value_z = accel2_read_zaxis( &accel2 );

   log_printf( &logger, "Axis X: %d\r\n", txt_x );

   log_printf( &logger, "Axis Y: %d\r\n", txt_y );

   log_printf( &logger, "Axis Z: %d\r\n", txt_z );
   
   log_printf( &logger, "-------------------------------" );

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
