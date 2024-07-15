#include "gd32f30x_gpio.h"
#include "pmra_b2.h"

int main()
{
  rcu_periph_clock_enable(RCU_GPIOF);
  gpio_init(LED_STATUS_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_STATUS_PIN);
  //   gd_eval_led_init(LED_STATUS);
  //   systick_config();
  while (1)
  {
    gpio_bit_reset(LED_STATUS_PORT, LED_STATUS_PIN);
    gpio_bit_set(LED_STATUS_PORT, LED_STATUS_PIN);
  }
}
