\mainpage Main Page


---
# Accel 4 click

> Accel 4 Click is a compact add-on board that contains an acceleration sensor. This board features the FXLS8964AF, a 12-bit three-axis accelerometer from NXP Semiconductors. It allows selectable full-scale acceleration measurements in ranges of �2g, �4g, �8g, or �16g in three axes with a configurable host interface that supports both SPI and I2C serial communication. The FXLS8964AF supports both high-performance and low-power operating modes, allowing maximum flexibility to meet the resolution and power needs for various unique use cases.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-4-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel4 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example is a showcase of the ability of the device
to read 3 axis data in varity of 3 resolutions, ability 
to configure 2 interrput pins for user needs etc..

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
