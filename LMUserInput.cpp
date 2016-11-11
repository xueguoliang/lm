#include "LMUserInput.h"

LMUserInput::LMUserInput()
{

}

void LMUserInput::get()
{
#if 0
AGAIN:
    fgets(_buf, sizeof(_buf), stdin);
    if(strlen(_buf) == 1) // only \n
        goto AGAIN;
//        get();
#endif

    while(1)
    {
        fgets(_buf, sizeof(_buf), stdin);
        if(strlen(_buf) > 1)
            break;
    }

    // remove \n
    _buf[strlen(_buf)-1] = 0;
}


