#include "em_device.h"
#include "em_chip.h"

//extern void Start(void);

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  /* Infinite loop */
  while (1) {
	  //Start();
  }
}
