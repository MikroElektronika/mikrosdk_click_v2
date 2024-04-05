\mainpage Main Page

---
# Expand 13 click

> Expand 13 Click is a compact add-on board that contains a multi-port I/O expander. This board features the PI4IOE5V96248, a 48-bit general-purpose I/O expander providing remote I/O expansion for most MCU’s families from Diodes Incorporated. The PI4IOE5V96248 comes in a 6-channel configuration and allows easy addition of I/O through a standard I2C serial interface. It has a built-in level shifting feature that makes it highly flexible in power supply systems where communication between incompatible I/O voltages is required.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/expand-13-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand13 Click driver.

#### Standard key functions :

- `expand13_cfg_setup` Config Object Initialization function.
```c
void expand13_cfg_setup ( expand13_cfg_t *cfg );
```

- `expand13_init` Initialization function.
```c
err_t expand13_init ( expand13_t *ctx, expand13_cfg_t *cfg );
```

#### Example key functions :

- `expand13_enable_device` This function enables the device by setting the RST pin to high logic state.
```c
void expand13_enable_device ( expand13_t *ctx );
```

- `expand13_write_all_ports` This function writes a desired data to all 6 ports.
```c
err_t expand13_write_all_ports ( expand13_t *ctx, uint8_t *ports );
```

- `expand13_read_all_ports` This function reads the state of all 6 ports.
```c
err_t expand13_read_all_ports ( expand13_t *ctx, uint8_t *ports );
```

## Example Description

> This example demonstrates the use of Expand 13 click board, by writing data to all six ports and then reading back the status of the ports. 

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand13_cfg_t expand13_cfg;  /**< Click config object. */

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
    expand13_cfg_setup( &expand13_cfg );
    EXPAND13_MAP_MIKROBUS( expand13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand13_init( &expand13, &expand13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    expand13_enable_device ( &expand13 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sets the pins of all ports and then reads and displays their status on the USB UART approximately once per second.

```c

void application_task ( void )
{
    uint8_t port_value[ 6 ] = { 0 };
    uint16_t pin_num = 0;
  
    for ( pin_num = EXPAND13_PIN_0_MASK; pin_num <= EXPAND13_PIN_7_MASK; pin_num <<= 1 )
    {
        if ( !expand13_get_int_pin ( &expand13 ) )
        {
            log_printf( &logger, " External input has occurred.\r\n" );
        }
        
        memset ( port_value, pin_num, 6 );
        expand13_write_all_ports( &expand13, port_value );
        
        expand13_read_all_ports( &expand13, port_value );
        for ( uint8_t cnt = EXPAND13_PORT_0; cnt <= EXPAND13_PORT_5; cnt++ )
        {
            log_printf( &logger, " Status port %d : 0x%.2X\r\n", ( uint16_t ) cnt, ( uint16_t ) port_value[ cnt ] );
        }
        log_printf( &logger, "\n" );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
