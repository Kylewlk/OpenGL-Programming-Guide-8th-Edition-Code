#include <vermilion.h>

#include "vgl.h"

extern "C" void vglLoadDDS(const char* filename, vglImageData* image);

void main(void)
{
    vglImageData image;

    vglLoadDDS("../../media/test.dds", &image);
}
