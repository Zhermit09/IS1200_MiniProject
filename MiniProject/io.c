#include "pic32mx.h"
#include "io.h"
//#include <stdio.h>

int delayAmount = 0;

uint8_t canvas[32][128];/*{
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,1,_,_,_,_,_,_,1,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,1,1,1,_,_,1,_,1,_,_,1,1,1,_,_,1,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,1,_,_,_,_,1,1,1,_,_,_,1,_,_,_,1,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,1,_,_,_,1,_,1,_,_,_,1,_,_,_,1,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,1,_,_,1,_,1,_,_,_,1,_,_,_,1,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,1,1,1,_,_,1,_,1,_,_,1,1,1,_,_,1,1,1,_,_,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,1,1,1,1,1,1,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,1,_,_,_,_,_,_,1,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_}
};*/

/*uint8_t font[95][7][5] =
{
	{
		{_,_,_,_,_},
		{_,_,_,_,_},
		{_,_,_,_,_},
		{_,_,_,_,_},
		{_,_,_,_,_}
	},

	{
		{1},
		{1},
		{1},
		{_},
		{1}
	},

	{
		{1,_,1},
		{1,_,1},
		{_,_,_},
		{_,_,_},
		{_,_,_}
	},

	{
		{_,1,_,1,_},
		{1,1,1,1,1},
		{_,1,_,1,_},
		{1,1,1,1,1},
		{_,1,_,1,_}
	},

	{
		{_,1,1,1,_},
		{1,_,1,_,_},
		{_,1,1,1,_},
		{_,_,1,_,1},
		{_,1,1,1,_}
	},

	{
		{1,1,_,_,1},
		{1,1,_,1,_},
		{_,_,1,_,_},
		{_,1,_,1,1},
		{1,_,_,1,1}
	},

	{
		{_,1,1,_,_},
		{1,_,_,1,_},
		{_,1,1,_,_},
		{1,_,_,1,_},
		{_,1,1,_,1}
	},

	{
		{1},
		{1},
		{_},
		{_},
		{_}
	},

	{
		{_,1},
		{1,_},
		{1,_},
		{1,_},
		{_,1}
	},

	{
		{1,_},
		{_,1},
		{_,1},
		{_,1},
		{1,_}
	},

	{
		{_,_,_},
		{1,_,1},
		{_,1,_},
		{1,_,1},
		{_,_,_}
	},

	{
		{_,_,_},
		{_,1,_},
		{1,1,1},
		{_,1,_},
		{_,_,_}
	},

	{
		{_,_},
		{_,_},
		{_,_},
		{_,_},
		{_,1},
		{1,_}
	},

	{
		{_,_,_},
		{_,_,_},
		{1,1,1},
		{_,_,_},
		{_,_,_}
	},

	{
		{_},
		{_},
		{_},
		{_},
		{1}
	},

	{
		{_,_,_,_,1},
		{_,_,_,1,_},
		{_,_,1,_,_},
		{_,1,_,_,_},
		{1,_,_,_,_}
	},

	{
		{_,1,_},
		{1,_,1},
		{1,_,1},
		{1,_,1},
		{_,1,_}
	},
	{
		{_,1,_},
		{1,1,_},
		{_,1,_},
		{_,1,_},
		{1,1,1}
	},

	{
		{1,1,1},
		{_,_,1},
		{1,1,1},
		{1,_,_},
		{1,1,1}
	},

	{
		{1,1,_},
		{_,_,1},
		{1,1,_},
		{_,_,1},
		{1,1,_}
	},

	{
		{1,_,1},
		{1,_,1},
		{1,1,1},
		{_,_,1},
		{_,_,1}
	},

	{
		{1,1,1},
		{1,_,_},
		{1,1,1},
		{_,_,1},
		{1,1,1}
	},

	{
		{1,1,1},
		{1,_,_},
		{1,1,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{1,1,1},
		{1,_,1},
		{_,_,1},
		{_,1,_},
		{_,1,_}
	},

	{
		{1,1,1},
		{1,_,1},
		{1,1,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{1,1,1},
		{1,_,1},
		{1,1,1},
		{_,_,1},
		{1,1,1}
	},

	{
		{_},
		{_},
		{1},
		{_},
		{1}
	},

	{
		{_,_},
		{_,_},
		{_,1},
		{_,_},
		{_,1},
		{1,_}
	},

	{
		{_,_,1},
		{_,1,_},
		{1,_,_},
		{_,1,_},
		{_,_,1}
	},

	{
		{_,_,_},
		{1,1,1},
		{_,_,_},
		{1,1,1},
		{_,_,_}
	},

	{
		{1,_,_},
		{_,1,_},
		{_,_,1},
		{_,1,_},
		{1,_,_}
	},

	{
		{1,1,1},
		{_,_,1},
		{_,1,_},
		{_,_,_},
		{_,1,_}
	},

	{
		{_,1,1,_},
		{1,_,_,1},
		{1,_,1,1},
		{1,_,_,_},
		{_,1,1,1}
	},

	{
		{_,1,1,_},
		{1,_,_,1},
		{1,1,1,1},
		{1,_,_,1},
		{1,_,_,1}
	},

	{
		{1,1,1,_},
		{1,_,_,1},
		{1,1,1,_},
		{1,_,_,1},
		{1,1,1,_}
	},

	{
		{_,1,1,_},
		{1,_,_,1},
		{1,_,_,_},
		{1,_,_,1},
		{_,1,1,_}
	},

	{
		{1,1,1,_},
		{1,_,_,1},
		{1,_,_,1},
		{1,_,_,1},
		{1,1,1,_}
	},

	{
		{1,1,1,1},
		{1,_,_,_},
		{1,1,1,_},
		{1,_,_,_},
		{1,1,1,1}
	},

	{
		{1,1,1,1},
		{1,_,_,_},
		{1,1,1,_},
		{1,_,_,_},
		{1,_,_,_}
	},

	{
		{_,1,1,1},
		{1,_,_,_},
		{1,_,1,1},
		{1,_,_,1},
		{_,1,1,1}
	},

	{
		{1,_,_,1},
		{1,_,_,1},
		{1,1,1,1},
		{1,_,_,1},
		{1,_,_,1}
	},

	{
		{1,1,1,1},
		{_,1,1,_},
		{_,1,1,_},
		{_,1,1,_},
		{1,1,1,1}
	},

	{
		{1,1,1,1},
		{_,1,1,_},
		{_,1,1,_},
		{_,1,1,_},
		{1,1,_,_}
	},

	{
		{1,_,_,1},
		{1,_,1,_},
		{1,1,_,_},
		{1,_,1,_},
		{1,_,_,1}
	},

	{
		{1,_,_,_},
		{1,_,_,_},
		{1,_,_,_},
		{1,_,_,_},
		{1,1,1,1}
	},

	{
		{1,_,_,_,1},
		{1,1,_,1,1},
		{1,_,1,_,1},
		{1,_,_,_,1},
		{1,_,_,_,1}
	},

	{
		{1,_,_,1},
		{1,1,_,1},
		{1,1,1,1},
		{1,_,1,1},
		{1,_,_,1}
	},

	{
		{_,1,1,_},
		{1,_,_,1},
		{1,_,_,1},
		{1,_,_,1},
		{_,1,1,_}
	},

	{
		{1,1,1,_},
		{1,_,_,1},
		{1,1,1,_},
		{1,_,_,_},
		{1,_,_,_}
	},

	{
		{_,1,_,_},
		{1,_,1,_},
		{1,_,1,_},
		{1,_,1,_},
		{_,1,_,1}
	},

	{
		{1,1,1,_},
		{1,_,_,1},
		{1,1,1,_},
		{1,_,1,1},
		{1,_,_,1}
	},

	{
		{_,1,1,1},
		{1,_,_,_},
		{_,1,1,_},
		{_,_,_,1},
		{1,1,1,_}
	},

	{
		{1,1,1,1},
		{_,1,1,_},
		{_,1,1,_},
		{_,1,1,_},
		{_,1,1,_}
	},

	{
		{1,_,_,1},
		{1,_,_,1},
		{1,_,_,1},
		{1,_,_,1},
		{_,1,1,_}
	},

	{
		{1,_,_,_,1},
		{1,_,_,_,1},
		{1,_,_,_,1},
		{_,1,_,1,_},
		{_,_,1,_,_}
	},

	{
		{1,_,_,_,1},
		{1,_,_,_,1},
		{1,_,1,_,1},
		{1,1,_,1,1},
		{1,_,_,_,1}
	},

	{
		{1,_,_,1},
		{1,_,_,1},
		{_,1,1,_},
		{1,_,_,1},
		{1,_,_,1}
	},

	{
		{1,_,_,1},
		{1,_,_,1},
		{_,1,1,_},
		{_,1,1,_},
		{_,1,1,_}
	},

	{
		{1,1,1,1},
		{_,_,1,1},
		{_,1,1,_},
		{1,1,_,_},
		{1,1,1,1}
	},

	{
		{1,1},
		{1,_},
		{1,_},
		{1,_},
		{1,1}
	},

	{
		{1,_,_,_,_},
		{_,1,_,_,_},
		{_,_,1,_,_},
		{_,_,_,1,_},
		{_,_,_,_,1}
	},

	{
		{1,1},
		{_,1},
		{_,1},
		{_,1},
		{1,1}
	},

	{
		{_,_,1,_,_},
		{_,1,_,1,_},
		{1,_,_,_,1},
		{_,_,_,_,_},
		{_,_,_,_,_}
	},

	{
		{_,_,_},
		{_,_,_},
		{_,_,_},
		{_,_,_},
		{1,1,1}
	},

	{
		{1,_},
		{_,1},
		{_,_},
		{_,_},
		{_,_}
	},

	{
		{1,1,_},
		{_,_,1},
		{1,1,1},
		{1,1,1}
	},

	{
		{1,_,_},
		{1,_,_},
		{1,1,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{1,1,1},
		{1,_,_},
		{1,_,_},
		{1,1,1}
	},

	{
		{_,_,1},
		{_,_,1},
		{1,1,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{1,1,1},
		{1,1,1},
		{1,_,_},
		{1,1,1}
	},

	{
		{_,_,_},
		{_,1,1},
		{_,1,_},
		{1,1,1},
		{_,1,_},
		{_,1,_}
	},

	{
		{_,_,_},
		{_,1,1},
		{1,_,1},
		{1,1,1},
		{_,_,1},
		{1,1,_}
	},

	{
		{1,_,_},
		{1,_,_},
		{1,1,_},
		{1,_,1},
		{1,_,1}
	},

	{
		{_,1,_},
		{_,_,_},
		{_,1,_},
		{_,1,_},
		{_,1,_}
	},

	{
		{_,_,_},
		{_,1,_},
		{_,_,_},
		{_,1,_},
		{_,1,_},
		{_,1,_},
		{1,_,_}
	},

	{
		{1,_,_},
		{1,_,_},
		{1,_,1},
		{1,1,_},
		{1,_,1}
	},

	{
		{1,1},
		{1,1},
		{1,1},
		{1,1},
		{1,1}
	},

	{
		{_,1,_,1,_},
		{1,_,1,_,1},
		{1,_,_,_,1},
		{1,_,_,_,1}
	},

	{
		{1,1,_},
		{1,_,1},
		{1,_,1},
		{1,_,1}
	},

	{
		{_,1,_},
		{1,_,1},
		{1,_,1},
		{_,1,_}
	},

	{
		{_,_,_},
		{1,1,_},
		{1,_,1},
		{1,1,_},
		{1,_,_},
		{1,_,_}
	},

	{
		{_,_,_},
		{_,1,1},
		{1,_,1},
		{1,1,1},
		{_,_,1},
		{_,_,1}
	},

	{
		{_,1,1},
		{1,_,_},
		{1,_,_},
		{1,_,_}
	},

	{
		{_,1,1},
		{1,1,_},
		{_,_,1},
		{1,1,}
	},

	{
		{_,1,_},
		{1,1,1},
		{_,1,_},
		{_,1,_},
		{_,1,1}
	},

	{
		{1,_,1},
		{1,_,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{1,_,1},
		{1,_,1},
		{1,_,1},
		{_,1,_}
	},

	{
		{1,_,_,_,1},
		{1,_,1,_,1},
		{1,1,_,1,1},
		{_,1,_,1,_}
	},

	{
		{1,_,1},
		{_,1,_},
		{1,_,1},
		{1,_,1}
	},

	{
		{1,_,1},
		{1,_,1},
		{_,1,_},
		{_,1,_}
	},

	{
		{1,1,1},
		{_,1,_},
		{1,_,_},
		{1,1,1}
	},

	{
		{_,1,1},
		{_,1,_},
		{1,1,_},
		{_,1,_},
		{_,1,1}
	},

	{
		{1},
		{1},
		{1},
		{1},
		{1}
	},

	{
		{1,1,_},
		{_,1,_},
		{_,1,1},
		{_,1,_},
		{1,1,_}
	},

	{
		{_,_,_,_},
		{_,_,_,_},
		{1,_,1,_},
		{_,1,_,1},
		{_,_,_,_}
	}

};
*/

struct Sprite fontz[95];

uint8_t f6x3[][6][3] =
{
	{
		{_,_,_},
		{_,1,1},
		{_,1,_},
		{1,1,1},
		{_,1,_},
		{_,1,_}
	},

	{
		{_,_,_},
		{_,1,1},
		{1,_,1},
		{1,1,1},
		{_,_,1},
		{1,1,_}
	},

	{
		{_,_,_},
		{1,1,_},
		{1,_,1},
		{1,1,_},
		{1,_,_},
		{1,_,_}
	},

	{
		{_,_,_},
		{_,1,1},
		{1,_,1},
		{1,1,1},
		{_,_,1},
		{_,_,1}
	}
};

uint8_t f6x2[][6][2] = 
{
	{
		{_,_},
		{_,_},
		{_,_},
		{_,_},
		{_,1},
		{1,_}
	},

	{
		{_,_},
		{_,1},
		{_,_},
		{_,_},
		{_,1},
		{1,_}
	},

	{
		{_,1},
		{_,_},
		{_,1},
		{_,1},
		{_,1},
		{1,_}
	}
};

uint8_t f6x1[][6][1] = 
{
	{
		{1},
		{1},
		{1},
		{1},
		{1},
		{1}
	}
};

uint8_t f5x5[][5][5] =
{
	{
		{_,_,_,_,_},
		{_,_,_,_,_},
		{_,_,_,_,_},
		{_,_,_,_,_},
		{_,_,_,_,_}
	},

	{
		{_,1,_,1,_},
		{1,1,1,1,1},
		{_,1,_,1,_},
		{1,1,1,1,1},
		{_,1,_,1,_}
	},

	{
		{_,1,1,1,_},
		{1,_,1,_,_},
		{_,1,1,1,_},
		{_,_,1,_,1},
		{_,1,1,1,_}
	},

	{
		{1,1,_,_,1},
		{1,1,_,1,_},
		{_,_,1,_,_},
		{_,1,_,1,1},
		{1,_,_,1,1}
	},

	{
		{_,1,1,_,_},
		{1,_,_,1,_},
		{_,1,1,_,_},
		{1,_,_,1,_},
		{_,1,1,_,1}
	},

	{
		{_,_,_,_,1},
		{_,_,_,1,_},
		{_,_,1,_,_},
		{_,1,_,_,_},
		{1,_,_,_,_}
	},

	{
		{1,_,_,_,1},
		{1,1,_,1,1},
		{1,_,1,_,1},
		{1,_,_,_,1},
		{1,_,_,_,1}
	},

	{
		{1,_,_,_,1},
		{1,_,_,_,1},
		{1,_,_,_,1},
		{_,1,_,1,_},
		{_,_,1,_,_}
	},

	{
		{1,_,_,_,1},
		{1,_,_,_,1},
		{1,_,1,_,1},
		{1,1,_,1,1},
		{1,_,_,_,1}
	},

	{
		{1,_,_,_,_},
		{_,1,_,_,_},
		{_,_,1,_,_},
		{_,_,_,1,_},
		{_,_,_,_,1}
	},

	{
		{_,_,1,_,_},
		{_,1,_,1,_},
		{1,_,_,_,1},
		{_,_,_,_,_},
		{_,_,_,_,_}
	}
};

uint8_t f5x4[][5][4] =
{
	{
		{_,1,1,_},
		{1,_,_,1},
		{1,_,1,1},
		{1,_,_,_},
		{_,1,1,1}
	},

	{
		{_,1,1,_},
		{1,_,_,1},
		{1,1,1,1},
		{1,_,_,1},
		{1,_,_,1}
	},

	{
		{1,1,1,_},
		{1,_,_,1},
		{1,1,1,_},
		{1,_,_,1},
		{1,1,1,_}
	},

	{
		{_,1,1,_},
		{1,_,_,1},
		{1,_,_,_},
		{1,_,_,1},
		{_,1,1,_}
	},

	{
		{1,1,1,_},
		{1,_,_,1},
		{1,_,_,1},
		{1,_,_,1},
		{1,1,1,_}
	},

	{
		{1,1,1,1},
		{1,_,_,_},
		{1,1,1,_},
		{1,_,_,_},
		{1,1,1,1}
	},

	{
		{1,1,1,1},
		{1,_,_,_},
		{1,1,1,_},
		{1,_,_,_},
		{1,_,_,_}
	},

	{
		{_,1,1,1},
		{1,_,_,_},
		{1,_,1,1},
		{1,_,_,1},
		{_,1,1,1}
	},

	{
		{1,_,_,1},
		{1,_,_,1},
		{1,1,1,1},
		{1,_,_,1},
		{1,_,_,1}
	},



	{
		{1,_,_,1},
		{1,_,1,_},
		{1,1,_,_},
		{1,_,1,_},
		{1,_,_,1}
	},

	{
		{1,_,_,1},
		{1,1,_,1},
		{1,1,1,1},
		{1,_,1,1},
		{1,_,_,1}
	},

	{
		{_,1,1,_},
		{1,_,_,1},
		{1,_,_,1},
		{1,_,_,1},
		{_,1,1,_}
	},

	{
		{1,1,1,_},
		{1,_,_,1},
		{1,1,1,_},
		{1,_,_,_},
		{1,_,_,_}
	},

	{
		{_,1,_,_},
		{1,_,1,_},
		{1,_,1,_},
		{1,_,1,_},
		{_,1,_,1}
	},

	{
		{1,1,1,_},
		{1,_,_,1},
		{1,1,1,_},
		{1,_,1,1},
		{1,_,_,1}
	},

	{
		{_,1,1,1},
		{1,_,_,_},
		{_,1,1,_},
		{_,_,_,1},
		{1,1,1,_}
	},

	{
		{1,_,_,1},
		{1,_,_,1},
		{1,_,_,1},
		{1,_,_,1},
		{_,1,1,_}
	},

	{
		{1,_,_,1},
		{1,_,_,1},
		{_,1,1,_},
		{1,_,_,1},
		{1,_,_,1}
	},

	{
		{1,1,1,1},
		{_,_,1,_},
		{_,1,_,_},
		{1,_,_,_},
		{1,1,1,1}
	},

	{
		{_,_,_,_},
		{_,_,_,_},
		{1,_,1,_},
		{_,1,_,1},
		{_,_,_,_}
	}
};

uint8_t f5x3[][5][3] = 
{
	{
		{1,_,1},
		{1,_,1},
		{_,_,_},
		{_,_,_},
		{_,_,_}
	},

	{
		{_,_,_},
		{1,_,1},
		{_,1,_},
		{1,_,1},
		{_,_,_}
	},

	{
		{_,_,_},
		{_,1,_},
		{1,1,1},
		{_,1,_},
		{_,_,_}
	},

	{
		{_,_,_},
		{_,_,_},
		{1,1,1},
		{_,_,_},
		{_,_,_}
	},

	{
		{_,1,_},
		{1,_,1},
		{1,_,1},
		{1,_,1},
		{_,1,_}
	},

	{
		{_,1,_},
		{1,1,_},
		{_,1,_},
		{_,1,_},
		{1,1,1}
	},

	{
		{1,1,1},
		{_,_,1},
		{1,1,1},
		{1,_,_},
		{1,1,1}
	},

	{
		{1,1,1},
		{_,_,1},
		{1,1,1},
		{_,_,1},
		{1,1,1}
	},

	{
		{1,_,1},
		{1,_,1},
		{1,1,1},
		{_,_,1},
		{_,_,1}
	},

	{
		{1,1,1},
		{1,_,_},
		{1,1,1},
		{_,_,1},
		{1,1,1}
	},

	{
		{1,1,1},
		{1,_,_},
		{1,1,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{1,1,1},
		{1,_,1},
		{_,_,1},
		{_,1,_},
		{_,1,_}
	},

	{
		{1,1,1},
		{1,_,1},
		{1,1,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{1,1,1},
		{1,_,1},
		{1,1,1},
		{_,_,1},
		{1,1,1}
	},

	{
		{_,_,1},
		{_,1,_},
		{1,_,_},
		{_,1,_},
		{_,_,1}
	},

	{
		{_,_,_},
		{1,1,1},
		{_,_,_},
		{1,1,1},
		{_,_,_}
	},

	{
		{1,_,_},
		{_,1,_},
		{_,_,1},
		{_,1,_},
		{1,_,_}
	},

	{
		{1,1,1},
		{_,_,1},
		{_,1,_},
		{_,_,_},
		{_,1,_}
	},

	{
		{1,1,1},
		{_,1,_},
		{_,1,_},
		{_,1,_},
		{1,1,1}
	},

	{
		{1,1,1},
		{_,1,_},
		{_,1,_},
		{_,1,_},
		{1,_,_}
	},

	{
		{_,_,_},
		{_,_,_},
		{_,_,_},
		{_,_,_},
		{1,1,1}
	},

	{
		{1,_,_},
		{1,_,_},
		{1,1,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{_,_,1},
		{_,_,1},
		{1,1,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{1,_,_},
		{1,_,_},
		{1,1,_},
		{1,_,1},
		{1,_,1}
	},

	{
		{1,_,_},
		{1,_,_},
		{1,_,1},
		{1,1,_},
		{1,_,1}
	},

	{
		{_,1,_},
		{1,1,1},
		{_,1,_},
		{_,1,_},
		{_,1,1}
	},

	{
		{_,1,1},
		{_,1,_},
		{1,1,_},
		{_,1,_},
		{_,1,1}
	},

	{
		{1,1,_},
		{_,1,_},
		{_,1,1},
		{_,1,_},
		{1,1,_}
	},

	{
		{1,_,_},
		{1,_,_},
		{1,_,_},
		{1,_,_},
		{1,1,1}
	},

	{
		{1,1,1},
		{_,1,_},
		{_,1,_},
		{_,1,_},
		{_,1,_}
	},

	{
		{1,_,1},
		{1,_,1},
		{_,1,_},
		{_,1,_},
		{_,1,_}
	}
};

uint8_t f5x2[][5][2] =
{

	{
		{_,1},
		{1,_},
		{1,_},
		{1,_},
		{_,1}
	},

	{
		{1,_},
		{_,1},
		{_,1},
		{_,1},
		{1,_}
	},



	{
		{1,1},
		{1,_},
		{1,_},
		{1,_},
		{1,1}
	},


	{
		{1,1},
		{_,1},
		{_,1},
		{_,1},
		{1,1}
	},

	{
		{1,_},
		{_,1},
		{_,_},
		{_,_},
		{_,_}
	}
};

uint8_t f5x1[][5][1] =
{
	{
		{1},
		{1},
		{1},
		{_},
		{1}
	},

	{
		{1},
		{1},
		{_},
		{_},
		{_}
	},

	{
		{_},
		{_},
		{_},
		{_},
		{1}
	},

	{
		{_},
		{1},
		{_},
		{_},
		{1}
	},

	{
		{1},
		{_},
		{1},
		{1},
		{1}
	},

	{
		{1},
		{1},
		{1},
		{1},
		{1}
	}
};

uint8_t f4x5[][4][5] =
{
	{
		{_,1,_,1,_},
		{1,_,1,_,1},
		{1,_,_,_,1},
		{1,_,_,_,1}
	},

	{
		{1,_,_,_,1},
		{1,_,1,_,1},
		{1,1,_,1,1},
		{_,1,_,1,_}
	}
};

uint8_t f4x3[][4][3] = 
{
	{
		{1,1,_},
		{_,_,1},
		{1,1,1},
		{1,1,1}
	},


	{
		{1,1,1},
		{1,_,_},
		{1,_,_},
		{1,1,1}
	},

	{
		{1,1,1},
		{1,1,1},
		{1,_,_},
		{1,1,1}
	},

	{
		{1,1,_},
		{1,_,1},
		{1,_,1},
		{1,_,1}
	},

	{
		{_,1,_},
		{1,_,1},
		{1,_,1},
		{_,1,_}
	},

	{
		{_,1,1},
		{1,_,_},
		{1,_,_},
		{1,_,_}
	},

	{
		{_,1,1},
		{1,1,_},
		{_,_,1},
		{1,1,}
	},

	{
		{1,_,1},
		{1,_,1},
		{1,_,1},
		{1,1,1}
	},

	{
		{1,_,1},
		{1,_,1},
		{1,_,1},
		{_,1,_}
	},

	{
		{1,_,1},
		{_,1,_},
		{1,_,1},
		{1,_,1}
	},

	{
		{1,_,1},
		{1,_,1},
		{_,1,_},
		{_,1,_}
	},

	{
		{1,1,1},
		{_,1,_},
		{1,_,_},
		{1,1,1}
	}
};


void fontInit() {
	int i = 0;


	//6x3---------------------------------------------
	for (i = 0; i <= 1; i++) {
		fontz[i + 70] = (struct Sprite){ 6,3,&f6x3[i][0][0] };
	}
	for (i = 2; i <= 3; i++) {
		fontz[i + 78] = (struct Sprite){ 6,3,&f6x3[i][0][0] };
	}
	//6x2---------------------------------------------
	fontz[12] = (struct Sprite){ 6,2,&f6x2[0][0][0] };
	fontz[27] = (struct Sprite){ 6,2,&f6x2[1][0][0] };
	fontz[74] = (struct Sprite){ 6,2,&f6x2[2][0][0] };
	//6x1---------------------------------------------
	fontz[92] = (struct Sprite){ 6,1,&f6x1[0][0][0] };
	//5x5---------------------------------------------
	fontz[0] = (struct Sprite){5,5,&f5x5[0][0][0]};

	for (i = 1; i <=4; i++) {
		fontz[i+2] = (struct Sprite){ 5,5,&f5x5[i][0][0] };
	}

	fontz[15] = (struct Sprite){ 5,5,&f5x5[5][0][0]};
	fontz[45] = (struct Sprite){ 5,5,&f5x5[6][0][0] };

	for (i = 7; i <=8; i++) {
		fontz[i + 47] = (struct Sprite){ 5,5,&f5x5[i][0][0] };
	}

	fontz[60] = (struct Sprite){ 5,5,&f5x5[9][0][0] };
	fontz[62] = (struct Sprite){ 5,5,&f5x5[10][0][0] };
	//5x4---------------------------------------------
	for (i = 0; i <= 8; i++) {
		fontz[i + 32] = (struct Sprite){ 5,4,&f5x4[i][0][0] };
	}

	fontz[43] = (struct Sprite){ 5,4,&f5x4[9][0][0] };

	for (i = 10; i <= 15; i++) {
		fontz[i + 36] = (struct Sprite){ 5,4,&f5x4[i][0][0] };
	}

	fontz[53] = (struct Sprite){ 5,4,&f5x4[16][0][0] };
	fontz[56] = (struct Sprite){ 5,4,&f5x4[17][0][0] };
	fontz[58] = (struct Sprite){ 5,4,&f5x4[18][0][0] };
	fontz[94] = (struct Sprite){ 5,4,&f5x4[19][0][0] };
	//5x3---------------------------------------------

	fontz[2] = (struct Sprite){ 5,3,&f5x3[0][0][0] };
	for (i = 1; i <= 2; i++) {
		fontz[i+9] = (struct Sprite){ 5,3,&f5x3[i][0][0] };
	}
	fontz[13] = (struct Sprite){ 5,3,&f5x3[3][0][0] };

	for (i = 4; i <= 13; i++) {
		fontz[i + 12] = (struct Sprite){ 5,3,&f5x3[i][0][0] };
	}

	for (i = 14; i <= 17; i++) {
		fontz[i + 14] = (struct Sprite){ 5,3,&f5x3[i][0][0] };
	}

	for (i = 18; i <= 19; i++) {
		fontz[i + 23] = (struct Sprite){ 5,3,&f5x3[i][0][0] };
	}

	fontz[63] = (struct Sprite){ 5,3,&f5x3[20][0][0] };
	fontz[66] = (struct Sprite){ 5,3,&f5x3[21][0][0] };
	fontz[68] = (struct Sprite){ 5,3,&f5x3[22][0][0] };
	fontz[72] = (struct Sprite){ 5,3,&f5x3[23][0][0] };
	fontz[75] = (struct Sprite){ 5,3,&f5x3[24][0][0] };
	fontz[84] = (struct Sprite){ 5,3,&f5x3[25][0][0] };
	fontz[91] = (struct Sprite){ 5,3,&f5x3[26][0][0] };
	fontz[93] = (struct Sprite){ 5,3,&f5x3[27][0][0] };
	fontz[44] = (struct Sprite){ 5,3,&f5x3[28][0][0] };
	fontz[52] = (struct Sprite){ 5,3,&f5x3[29][0][0] };
	fontz[57] = (struct Sprite){ 5,3,&f5x3[30][0][0] };
	//5x2---------------------------------------------
	for (i = 0; i <= 1; i++) {
		fontz[i+8] = (struct Sprite){ 5,2,&f5x2[i][0][0] };
	}
	fontz[59] = (struct Sprite){ 5,2,&f5x2[2][0][0] };
	fontz[61] = (struct Sprite){ 5,2,&f5x2[3][0][0] };
	fontz[64] = (struct Sprite){ 5,2,&f5x2[4][0][0] };
	//5x1---------------------------------------------
	fontz[1] = (struct Sprite){ 5,1,&f5x1[0][0][0] };
	fontz[7] = (struct Sprite){ 5,1,&f5x1[1][0][0] };
	fontz[14] = (struct Sprite){ 5,1,&f5x1[2][0][0] };
	fontz[26] = (struct Sprite){ 5,1,&f5x1[3][0][0] };
	fontz[73] = (struct Sprite){ 5,1,&f5x1[4][0][0] };
	fontz[76] = (struct Sprite){ 5,1,&f5x1[5][0][0] };
	//4x5---------------------------------------------
	fontz[77] = (struct Sprite){ 4,5,&f4x5[0][0][0] };
	fontz[87] = (struct Sprite){ 4,5,&f4x5[1][0][0] };
	//4x3---------------------------------------------
	fontz[65] = (struct Sprite){ 4,3,&f4x3[0][0][0] };
	fontz[67] = (struct Sprite){ 4,3,&f4x3[1][0][0] };
	fontz[69] = (struct Sprite){ 4,3,&f4x3[2][0][0] };

	for (i = 3; i <= 4; i++) {
		fontz[i+75] = (struct Sprite){ 4,3,&f4x3[i][0][0] };
	}

	for (i = 5; i <= 6; i++) {
		fontz[i+77] = (struct Sprite){ 4,3,&f4x3[i][0][0] };
	}

	for (i = 7; i <= 8; i++) {
		fontz[i+78] = (struct Sprite){ 4,3,&f4x3[i][0][0] };
	}

	for (i = 9; i <= 11; i++) {
		fontz[i+79] = (struct Sprite){ 4,3,&f4x3[i][0][0] };
	}
	//------------------------------------------------
	

	struct Vec pos = { 0,1 };
	struct Vec scale = { 1,1 };
	
	//printText("R", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	printText(" !\"#$%&\'()*+,-./0123456789:;<=>?", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	pos.y += 6;
	printText("@ABCDEFGHIJKLMNOP", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	pos.y += 6;
	printText("QRSTUVWXYZ[\\]^_`", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	pos.y += 6;
	printText("abcdefghijklmnopqrstuvwxyz{|}~", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	pos.y += 6;
	//printText(" !\"#$%&\'()*+,-./0123456789:;<=>?", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	
}

void delay(int ms) {

	delayAmount = ms / (1000 * T_PERIOD);
	while (delayAmount > 0);
}

int getSw(void) {
	return ((PORTD >> 8) & 0xf);
}

int getBtns(void) {
	return (((PORTD >> 4) & 0xe) | ((PORTF >> 1) & 0x1));	//Button 4-2 + 1
}

uint8_t spi(uint8_t data) {
	while (!(SPI2STAT & PIC32_SPISTAT_SPITBE));		//SPI2STAT & 0x08
	SPI2BUF = data;
	while (!(SPI2STAT & PIC32_SPISTAT_SPIRBF));		//SPI2STAT & 0x01
	return SPI2BUF;
}

void displayUpdate() {
	int page, seg, i;
	int col = 0;

	for (page = 0; page < 4; page++) {
		CMD_MODE_ON;

		spi(0x22);							//Page select command
		spi(page);							//Page number

		spi(0x00);							//Set low nybble of column
		spi(0x10);							//Set high nybble of column

		CMD_MODE_OFF;

		for (seg = 0; seg < 128; seg++) {

			for (i = 0; i < 8; i++) {
				col |= canvas[page * 8 + i][seg] << i;	//Create the column byte
			}
			spi(col);
			col = 0;
		}

	}
}

void drawSprite(struct Sprite asset, struct Vec pos, struct Vec scale) {
	int h, w;
	int c = 0;

	for (h = 0; h < asset.height; h++) {
		for (w = 0; w < asset.width; w++) {
			canvas[h+pos.y][w+pos.x] = *(asset.sprite + w + h * asset.width);
			/*c = *(asset.sprite + w + h * asset.width);
			if(c != 0){
			printf("%d ", c);
			}
			else {
				printf(" ");
			}*/
		}
		//printf("\n");
	}
	//printf("-----------------------\n");
	

}

void printText(char string[], struct Vec pos, struct Vec scale, enum Align align, enum Border border, enum Invert invert) {

	int i = 0;

	while (string[i] != '\0') {
		if (fontz[(int)(string[i]) - 32].height == 4) {
			pos.y += 1;
			drawSprite(fontz[(int)(string[i]) - 32], pos, scale);
			pos.y -= 1;
		}
		else {
			drawSprite(fontz[(int)(string[i]) - 32], pos, scale);
		}
		pos.x += fontz[(int)(string[i]) - 32].width + 1;
		i++;
	}

}

//Debug LEDs
//PORTE = (PORTE & ~0xff) | (getBtns() << 4) | getSw();

/*
if (IFS(0) & 0x100) {
	PORTE = ~PORTE;
	IFSCLR(0) = 0x100;
}*/
