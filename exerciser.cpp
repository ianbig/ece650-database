#include "exerciser.h"

void exercise(connection *C)
{
    query2(C, "LightBlue");
    query3(C, "Duke");
    query3(C, "UNC");
    query4(C, "NC", "DarkBlue");
    query5(C, 10);

    query1(C, 0, 10, 40, 0, 30, 50, 0, 20, 50, 0, 0, 30, 0, 5, 35, 0, 20, 50);
}
