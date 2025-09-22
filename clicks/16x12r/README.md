
---
# 16x12 R Click

> [16x12 R Click](https://www.mikroe.com/?pid_product=MIKROE-6669) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6669&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the usage of the 16x12 R Click board which features a high-brightness
red LED matrix display. It displays characters, rotates them in different orientations,
prints a scrolling string, and renders a graphical image (MIKROE logo).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.16x12R

### Example Key Functions

- `c16x12r_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void c16x12r_cfg_setup ( c16x12r_cfg_t *cfg );
```

- `c16x12r_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t c16x12r_init ( c16x12r_t *ctx, c16x12r_cfg_t *cfg );
```

- `c16x12r_default_cfg` This function executes a default configuration of 16x12 R Click board.
```c
err_t c16x12r_default_cfg ( c16x12r_t *ctx );
```

- `c16x12r_write_char` This function writes a single ASCII character to the display.
```c
err_t c16x12r_write_char ( c16x12r_t *ctx, uint8_t data_in );
```

- `c16x12r_write_string` This function scrolls a null-terminated ASCII string across the display.
```c
err_t c16x12r_write_string ( c16x12r_t *ctx, uint8_t *data_in, uint16_t speed_ms );
```

- `c16x12r_draw_picture` This function draws a picture on the display from a 12-column buffer.
```c
err_t c16x12r_draw_picture ( c16x12r_t *ctx, const uint16_t *image );
```

### Application Init

> Initializes the logger and the Click board and sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c16x12r_cfg_t c16x12r_cfg;  /**< Click config object. */

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
    c16x12r_cfg_setup( &c16x12r_cfg );
    C16X12R_MAP_MIKROBUS( c16x12r_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c16x12r_init( &c16x12r, &c16x12r_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C16X12R_ERROR == c16x12r_default_cfg ( &c16x12r ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Displays single characters and a string in multiple rotations, followed by drawing and inverting the MIKROE logo image.

```c
void application_task ( void )
{
    log_printf( &logger, " Writing digits\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_H_0;
    for ( uint8_t digit = '0'; digit <= '9'; digit++ )
    {
        c16x12r_write_char ( &c16x12r, digit );
        Delay_ms ( 500 );
    }

    log_printf( &logger, " Rotating char\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_H_0;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );
    c16x12r.text_rotation = C16X12R_ROTATION_H_180;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );
    c16x12r.text_rotation = C16X12R_ROTATION_V_0;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );
    c16x12r.text_rotation = C16X12R_ROTATION_V_180;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );
    c16x12r.text_rotation = C16X12R_ROTATION_H_0;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );

    log_printf( &logger, " Writing text\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_H_0;
    c16x12r_write_string ( &c16x12r, "MIKROE - 16x12 R Click", 50 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Writing text\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_H_180;
    c16x12r_write_string ( &c16x12r, "MIKROE - 16x12 R Click", 50 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Writing text\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_V_0;
    c16x12r_write_string ( &c16x12r, "MIKROE - 16x12 R Click", 50 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Writing text\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_V_180;
    c16x12r_write_string ( &c16x12r, "MIKROE - 16x12 R Click", 50 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing MIKROE logo\r\n\n" );
    c16x12r_draw_picture ( &c16x12r, c16x12r_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing inverted MIKROE logo\r\n\n" );
    c16x12r_draw_picture ( &c16x12r, c16x12r_img_mikroe_inv );
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
