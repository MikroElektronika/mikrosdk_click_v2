
---
# UART to I2C click

> UART to I2C Click is a compact add-on board allowing connections to UART controllers and I2C targets for protocol conversion. This board features the SC18IM704, a bridge between the standard UART host interface and a serial I2C bus from NXP Semiconductors. The SC18IM704 provides a high-speed UART interface with a baud rate of up to 460.8 kbit/s and 256-byte FIFO for the transfer/receive data process, alongside several user-configurable GPIO pins. The host MCU communicates with the SC18IM704 with ASCII messages protocol, allowing it to control all the specific I2C-bus sequences, protocol, arbitration, and timing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uarttoi2c_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uart-to-i2c-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : UART type


# Software Support

We provide a library for the UART to I2C Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UART to I2C Click driver.

#### Standard key functions :

- `uarttoi2c_cfg_setup` Config Object Initialization function.
```c
void uarttoi2c_cfg_setup ( uarttoi2c_cfg_t *cfg );
```

- `uarttoi2c_init` Initialization function.
```c
err_t uarttoi2c_init ( uarttoi2c_t *ctx, uarttoi2c_cfg_t *cfg );
```

- `uarttoi2c_default_cfg` Click Default Configuration function.
```c
err_t uarttoi2c_default_cfg ( uarttoi2c_t *ctx );
```

#### Example key functions :

- `uarttoi2c_gpio_write` This function writes a desired data to the gpio port.
```c
void uarttoi2c_gpio_write ( uarttoi2c_t *ctx, uint8_t gpio_data );
```

- `uarttoi2c_gpio_read` This function reads data from the gpio port.
```c
err_t uarttoi2c_gpio_read ( uarttoi2c_t *ctx, uint8_t *gpio_data );
```

- `uarttoi2c_i2c_write_then_read` This function performs a write then read with a repeated start to the I2C target device.
```c
err_t uarttoi2c_i2c_write_then_read ( uarttoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );
```

## Example Description

> This example demonstrates the use of USB to I2C click board by reading the device ID of a 3D Hall 11 click board connected to the I2C port and controlling the GPIO pins.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default config which resets the device and sets the GPIO pins 0-3 as push-pull output and others as input.
After that, reads and displays the chip firmware version.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uarttoi2c_cfg_t uarttoi2c_cfg;  /**< Click config object. */

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
    uarttoi2c_cfg_setup( &uarttoi2c_cfg );
    UARTTOI2C_MAP_MIKROBUS( uarttoi2c_cfg, MIKROBUS_1 );
    if ( UART_ERROR == uarttoi2c_init( &uarttoi2c, &uarttoi2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UARTTOI2C_ERROR == uarttoi2c_default_cfg ( &uarttoi2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t version[ 16 ] = { 0 };
    if ( UARTTOI2C_OK == uarttoi2c_read_version ( &uarttoi2c, version ) )
    {
        log_printf( &logger, " Firmware version: %s\r\n", version );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the device ID of a 3D Hall 11 click board connected to the I2C port, toggles the output pins and displays the GPIO port state.
The results will be displayed on the USB UART approximately once per second.

```c
void application_task ( void )
{
    static uint8_t gpio_state = UARTTOI2C_NO_PIN_MASK;
    uint8_t slave_address = DEVICE_SLAVE_ADDRESS;
    uint8_t reg_addr = DEVICE_REG_ID;
    uint8_t device_id;
    if ( UARTTOI2C_OK == uarttoi2c_i2c_write_then_read ( &uarttoi2c, slave_address, 
                                                         &reg_addr, 1, &device_id, 1 ) )
    {
        log_printf( &logger, " %s - Device ID read: %s\r\n", ( char * ) DEVICE_NAME,
                    ( char * ) ( ( DEVICE_ID == device_id ) ? "Success" : "Fail" ) );
    }
    uarttoi2c_gpio_write ( &uarttoi2c, gpio_state );
    if ( UARTTOI2C_OK == uarttoi2c_gpio_read ( &uarttoi2c, &gpio_state ) )
    {
        log_printf( &logger, " GPIO state: 0x%.2X\r\n\n", ( uint16_t ) gpio_state );
        gpio_state = ~gpio_state;
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UARTtoI2C

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
