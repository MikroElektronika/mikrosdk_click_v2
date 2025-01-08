
---
# Accel3 Click

> [Accel 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2102) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2102&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> 
> This is an example which demonstrates the usage of Accel 3 Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel3

### Example Key Functions

- `accel3_cfg_setup` Config Object Initialization function. 
```c
void accel3_cfg_setup ( accel3_cfg_t *cfg );
``` 
 
- `accel3_init` Initialization function. 
```c
err_t accel3_init ( accel3_t *ctx, accel3_cfg_t *cfg );
```

- `accel3_default_cfg` Click Default Configuration function. 
```c
void accel3_default_cfg ( accel3_t *ctx );
```

- `accel3_default_cfg` This function select communication mode and executes start initialization. 
```c
void accel3_default_cfg ( accel3_t *ctx, accel3_cfg_t *cfg );
```
 
- `accel3_read_data` This function reads Accel data ( X, Y and Z axis ) from the desired Accel registers of the H3LIS331DL module. 
```c
void accel3_read_data ( accel3_t *ctx, accel3_data_t *accel3_data );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accel3_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    accel3_cfg_setup( &cfg );
    ACCEL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel3_init( &accel3, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " -----  Accel 3 Click  -----\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    accel3_default_cfg ( &accel3, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, " -- Initialization  done. --\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> Measured coordinates (X,Y,Z) are being sent to the UART where you can 
> track their changes. All data logs on USB UART for every 1 sec.
> 

```c
void application_task ( void )
{
    accel3_read_data( &accel3, &accel3_data );
    Delay_ms ( 100 );
    
    log_printf( &logger, "        Accelerometer       \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "        X = %d \r\n", accel3_data.x );
    log_printf( &logger, "        Y = %d \r\n", accel3_data.y );
    log_printf( &logger, "        Z = %d \r\n", accel3_data.z );
    log_printf( &logger, "----------------------------\r\n" );
    
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
