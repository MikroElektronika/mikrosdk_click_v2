
---
# Accel 4 Click

> [Accel 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4780) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4780&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example is a showcase of the ability of the device
to read 3 axis data in varity of 3 resolutions, ability 
to configure 2 interrput pins for user needs etc..

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel4

### Example Key Functions

- `accel4_cfg_setup` Config Object Initialization function.
```c
void accel4_cfg_setup ( accel4_cfg_t *cfg );
```

- `accel4_init` Initialization function.
```c
err_t accel4_init ( accel4_t *ctx, accel4_cfg_t *cfg );
```

- `accel4_default_cfg` Click Default Configuration function.
```c
err_t accel4_default_cfg ( accel4_t *ctx );
```

- `accel4_get_int1` Get interrupt 1 pin state.
```c
uint8_t accel4_get_int1 ( accel4_t *ctx );
```

- `accel4_axes_get_resolution` Reads current resolution of output data.
```c
float accel4_axes_get_resolution ( accel4_t *ctx );
```

- `accel4_get_axes_data` Accel data reading.
```c
err_t accel4_get_axes_data ( accel4_t *ctx, accel4_axes_t *axes );
```

### Application Init

> Initializion of communication modules (I2C/SPI, UART) and 
additional interrupt pins. Reading status register in loop
until power up bit is set to 1. Then reads device ID and checks
if it's valid, and in the end configures device to get interrupt 
on new data received, set device in active mode and sets currently 
configured resolution to context object.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel4_cfg_t accel4_cfg;  /**< Click config object. */

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
    accel4_cfg_setup( &accel4_cfg );
    ACCEL4_MAP_MIKROBUS( accel4_cfg, MIKROBUS_1 );
    err_t init_flag  = accel4_init( &accel4, &accel4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t temp_data = 0;
    
    // Wait for the powerup status
    do {
        accel4_generic_read( &accel4, ACCEL4_REG_INT_STATUS, &temp_data, 1 );
        Delay_ms ( 1 );
    }while ( ( temp_data & 1 ) != 1 );
    
    //Read device ID
    accel4_generic_read( &accel4, ACCEL4_REG_WHO_AM_I, &temp_data, 1 );
    log_printf( &logger, " > WHO AM I: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( ACCEL4_DEVICE_ID != temp_data )
    {
        log_error( &logger, " ID" );
        for( ; ; );
    }
    
    accel4_default_cfg ( &accel4 );
    
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads data of all 3 axes whenever interrupt is received and logs it.

```c
void application_task ( void )
{
    if ( accel4_get_int1( &accel4 ) )
    {
        accel4_axes_t axes;
        accel4_get_axes_data( &accel4, &axes );
        
        log_printf( &logger, " > X: %.2f\r\n", axes.x );
        log_printf( &logger, " > Y: %.2f\r\n", axes.y );
        log_printf( &logger, " > Z: %.2f\r\n", axes.z );
        log_printf( &logger, "*****************************************\r\n" );
        Delay_ms ( 300 );
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
