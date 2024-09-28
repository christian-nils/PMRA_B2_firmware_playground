#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <microros_transports.h>

#define UART0_TX_PIN GPIO_PIN_9
#define UART0_RX_PIN GPIO_PIN_10
#define UART0_PORT GPIOA

bool serial_transport_open(struct uxrCustomTransport *transport)
{
  serial_transport_args *args = (serial_transport_args *)transport->args;

  /* enable GPIO clock */
  rcu_periph_clock_enable(RCU_GPIOA);

  /* enable UART clock */
  rcu_periph_clock_enable(RCU_USART0);

  /* connect port to UARTx_Tx */
  gpio_init(UART0_PORT, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, UART0_TX_PIN);

  /* connect port to UARTx_Rx */
  gpio_init(UART0_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, UART0_RX_PIN);

  /* UART configure */
  usart_deinit(USART0);

  usart_baudrate_set(USART0, args->baud_rate);
  usart_word_length_set(USART0, args->word_length);
  usart_parity_config(USART0, args->parity);
  usart_stop_bit_set(USART0, args->stop_bits);
  usart_receive_config(USART0, USART_RECEIVE_ENABLE);
  usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);

  usart_enable(USART0);

  return true;
};

bool serial_transport_close(struct uxrCustomTransport *transport)
{
  usart_disable(USART0);

  return true;
};

size_t serial_transport_write(struct uxrCustomTransport *transport, const uint8_t *buf, size_t len, uint8_t *err)
{
  int write_counter = 0;
  while (write_counter < len)
  {
    while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
    {
    }
    usart_data_transmit(USART0, buf[write_counter++]);
    /* wait until end of transmit */
    while (RESET == usart_flag_get(USART0, USART_FLAG_TC))
    {
    }
  }

  return write_counter;
};

size_t serial_transport_read(struct uxrCustomTransport *transport, uint8_t *buf, size_t len, int timeout, uint8_t *err)
{
  int read_counter = 0;
  usart_data_receive(USART0);

  while (read_counter < len)
  {
    /* wait until end of transmit */
    while (RESET == usart_flag_get(USART0, USART_FLAG_TC))
    {
    }
    /* wait the byte is entirely received by USART0 */
    while (RESET == usart_flag_get(USART0, USART_FLAG_RBNE))
    {
    }
    /* store the received byte in the rxbuffer1 */
    buf[read_counter++] = usart_data_receive(USART0);
  }

  return read_counter;
};