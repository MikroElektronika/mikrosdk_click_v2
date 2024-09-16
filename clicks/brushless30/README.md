\mainpage Main Page

---
# Brushless 30 click

> Brushless 30 Click is a compact add-on board for precise and reliable control of brushless motors. This board features the TB9083FTG, a gate-driver IC from Toshiba Semiconductor, known for its robust performance in automotive environments. It also includes additional header pins for 6 PWM inputs , safety relays and current sense amplifiers. Comprehensive error detection capabilities, as required from automotive devices, are included. Brushless 30 Click is ideal for demanding automotive applications such as electric power steering (EPS), powered brakes, and automotive pumps where high-precision motor control is crucial.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless30_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-30-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the Brushless 30 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 30 Click driver.

#### Standard key functions :

- `brushless30_cfg_setup` Config Object Initialization function.
```c
void brushless30_cfg_setup ( brushless30_cfg_t *cfg );
```

- `brushless30_init` Initialization function.
```c
err_t brushless30_init ( brushless30_t *ctx, brushless30_cfg_t *cfg );
```

- `brushless30_default_cfg` Click Default Configuration function.
```c
err_t brushless30_default_cfg ( brushless30_t *ctx );
```

#### Example key functions :

- `brushless30_write_reg` This function writes a data word to the selected register by using SPI serial interface.
```c
err_t brushless30_write_reg ( brushless30_t *ctx, uint8_t reg, uint16_t data_in );
```

- `brushless30_read_reg` This function reads a data word from the selected register by using SPI serial interface.
```c
err_t brushless30_read_reg ( brushless30_t *ctx, uint8_t reg, uint16_t *data_out );
```

- `brushless30_get_diag_pin` This function returns the DIAG pin logic state.
```c
uint8_t brushless30_get_diag_pin ( brushless30_t *ctx );
```

## Example Description

> This example configures the Brushless 30 click board and makes it ready for the motor control over 6 PWM input signals.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless30_cfg_t brushless30_cfg;  /**< Click config object. */

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
    brushless30_cfg_setup( &brushless30_cfg );
    BRUSHLESS30_MAP_MIKROBUS( brushless30_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == brushless30_init( &brushless30, &brushless30_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS30_ERROR == brushless30_default_cfg ( &brushless30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, " Click is configured successfully.\r\n" );
    log_printf( &logger, " Apply a 6 PWM signals to UVW H/L pins to drive the motor.\r\n" );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Monitors the DIAG pin state, displays the STAT1 and STAT2 registers on the USB UART, and clears the set flags.

```c
void application_task ( void )
{
    uint16_t status = 0;
    if ( !brushless30_get_diag_pin ( &brushless30 ) )
    {
        if ( BRUSHLESS30_OK == brushless30_read_reg ( &brushless30, BRUSHLESS30_REG_STAT1, &status ) )
        {
            if ( status )
            {
                log_printf( &logger, " STAT1: 0x%.4X\r\n", status );
                if ( BRUSHLESS30_OK == brushless30_write_reg ( &brushless30, BRUSHLESS30_REG_STAT1, status ) )
                {
                    log_printf( &logger, " STAT1: cleared\r\n" );
                }
            }
        }
        
        if ( BRUSHLESS30_OK == brushless30_read_reg ( &brushless30, BRUSHLESS30_REG_STAT2, &status ) )
        {
            if ( status )
            {
                log_printf( &logger, " STAT2: 0x%.4X\r\n", status );
                if ( BRUSHLESS30_OK == brushless30_write_reg ( &brushless30, BRUSHLESS30_REG_STAT2, status ) )
                {
                    log_printf( &logger, " STAT2: cleared\r\n" );
                }
            }
        }
        
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless30

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
