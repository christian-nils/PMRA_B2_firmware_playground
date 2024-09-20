#include "gd32f30x_gpio.h"
#include "pmra_b2.h"
#include "tx_api.h"

// int main()
// {
//   rcu_periph_clock_enable(RCU_GPIOF);
//   gpio_init(LED_STATUS_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_STATUS_PIN);
//   //   gd_eval_led_init(LED_STATUS);
//   //   systick_config();
//   while (1)
//   {
//     gpio_bit_reset(LED_STATUS_PORT, LED_STATUS_PIN);
//     gpio_bit_set(LED_STATUS_PORT, LED_STATUS_PIN);
//   }
// }

unsigned long my_thread_counter = 0;
TX_THREAD my_thread;

void my_thread_entry(ULONG thread_input)
{
  rcu_periph_clock_enable(RCU_GPIOF);
  gpio_init(LED_STATUS_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_STATUS_PIN);
  /* Enter into a forever loop. */
  while (1)
  {
    /* Increment thread counter. */
    my_thread_counter = !my_thread_counter;
    if (my_thread_counter == 0)
    {
      gpio_bit_reset(LED_STATUS_PORT, LED_STATUS_PIN);
    }
    else
    {
      gpio_bit_set(LED_STATUS_PORT, LED_STATUS_PIN);
    }
    /* Sleep for 1 tick. */
    tx_thread_sleep(1000);
  }
}

void tx_application_define(void *first_unused_memory)
{
  /* Create my_thread! */
  tx_thread_create(&my_thread, "My Thread",
                   my_thread_entry, 0x1234, first_unused_memory, 1024,
                   3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
}

int main()
{
  /* Enter the ThreadX kernel. */
  tx_kernel_enter();
  return 0;
}
