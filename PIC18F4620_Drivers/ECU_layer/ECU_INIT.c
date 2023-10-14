#include "ECU_INIT.h"

/*------Global Variables---------*/


/*-----Static functions---------*/




Std_ReturnType app_inisialize(void)
{
    Std_ReturnType ret = mcal_init();
    
    
  return ret;
}
