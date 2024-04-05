
---
# Gaussmeter click

Gaussmeter click is a device that is used for measuring the magnetic field in X, Y and Z axes. This Click board™ features the MLX90393, a micropower magnetometer based on the proprietary Triaxis® technology, from Melexis.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gaussmeter_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gaussmeter-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C/SPI type

# Software Support

We provide a library for the Gaussmeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gaussmeter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gaussmeter_cfg_setup ( gaussmeter_cfg_t *cfg ); 
 
- Initialization function.
> GAUSSMETER_RETVAL gaussmeter_init ( gaussmeter_t *ctx, gaussmeter_cfg_t *cfg );

- Click Default Configuration function.
> void gaussmeter_default_cfg ( gaussmeter_t *ctx );

#### Example key functions :

- This function writes 16-bit data to the specified register address.
> uint8_t gaussmeter_write_reg ( gaussmeter_t *ctx, uint8_t reg_addr, uint16_t transfer_data );
 
- This function reads the temperature and axis data from the chip.
> uint8_t gaussmeter_get_data( gaussmeter_t *ctx, float *output_data );

- This function reads the digital input signal from the INT pin.
> uint8_t gaussmeter_digital_read_int ( gaussmeter_t *ctx );

## Examples Description

> This example showcases how to configure and use the Gaussmeter click. This click measures
> magnetic fields around the device using a 3 axis measurement system. Alongside the magnetometer,
> the click contains an integrated temperature sensor which provides data for the thermal compensation.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. 
> Additional configuring is done in the default_cfg(...) function.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    gaussmeter_cfg_t cfg;

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

    gaussmeter_cfg_setup( &cfg );
    GAUSSMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gaussmeter_init( &gaussmeter, &cfg );
    Delay_ms ( 100 );
    gaussmeter_default_cfg( &gaussmeter );
    Delay_ms ( 500 );
}
  
```

### Application Task

> This function reads data from the magnetometer and the temperature sensor and displays that
> data using the UART console every 400 milliseconds.

```c

void application_task ( )
{
    float temp_buf[ 4 ] = { 0 };
    uint8_t error_bit;
    uint8_t axis_check;
    uint8_t cnt;

    error_bit = gaussmeter_get_data( &gaussmeter, temp_buf );

    if ( !error_bit )
    {
        axis_check = 1;
        buf_idx = 0;
    }

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        switch ( gaussmeter.aux.command_byte_low & axis_check )
        {
            case 1:
            {
                log_printf( &logger, " * Temperature: %.2f C\r\n", temp_buf[ buf_idx++ ] );
                break;
            }
            case 2:
            {
                log_printf( &logger, " * X-axis: %.2f microT\r\n", temp_buf[ buf_idx++ ] );
                break;
            }
            case 4:
            {
                log_printf( &logger, " * Y-axis: %.2f microT\r\n", temp_buf[ buf_idx++ ] );
                break;
            }
            case 8:
            {
                log_printf( &logger, " * Z-axis: %.2f microT\r\n", temp_buf[ buf_idx++ ] );
            }
        }
        axis_check <<= 1;
    }
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms ( 400 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gaussmeter

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
