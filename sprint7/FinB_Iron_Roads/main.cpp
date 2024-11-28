#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
//#include "api.h"

void init() {
  printf("Press run code to see this in the console!\n");
  // You can initiate and calculate things here
}


//High-SNR packed format

double high_snr_decode(int snr1) {
  uint16_t snr = snr1;
  int16_t new_snr = 0;
  uint16_t div_exponent = 0;
  int sign = 0;
  double new_snr_double = 0;

  printf ("New test\n\n");

  if ( ((snr & (1UL << 12)) ? 0 : 1) &&
       ((snr & (1UL << 13)) ? 0 : 1) &&
       ((snr & (1UL << 14)) ? 0 : 1) &&
       ((snr & (1UL << 15)) ? 0 : 1)
     )
  {
    //---------------------------------------------------------------------------------
    //zero

    if ((snr & (1UL << 11)) ? 1 : 0)
    {
      new_snr = -1 * (((int)~snr & (0x07FF) ) + 1);
    } else {
      new_snr = snr;
    }
    new_snr_double = (double)new_snr / pow(2.0, 24.0);


  } else {
    //---------------------------------------------------------------------------------

    //non-zero

    new_snr = snr & 0x07FF; //copy mantissa
    div_exponent = snr >> 12;

    if (snr & (1UL << 11)) //
    {
      // 1

      printf ("----snr 0x%x\n", snr);
      new_snr = -1 * (((int)~new_snr & (0x0FFF) ) + 1);
      //printf ("snr 0x%x\n", snr);
      printf ("new_snr exponent %x, %x, %x, %d\n", new_snr, (int)~snr, (((int)~snr & (0x07FF) ) + 1), (((int)~snr & (0x07FF) ) + 1));
      new_snr = new_snr & 0xFFFF;
      printf ("new_snr %d, %x, %d\n", new_snr, new_snr, div_exponent);

    } else {
      // 0
      new_snr |= (1 << 11);

    }

    new_snr_double = (double)new_snr / pow(2.0, 25.0 - (double)div_exponent);

    printf ("new_snr_double %f, %f\n", new_snr_double, (double)new_snr);
  }
  // Write your code here
  return new_snr_double;
}