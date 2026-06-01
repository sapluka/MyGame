#include "Widget.h"

Widget::Widget(int x, int y, int w, int h)
{
    widgetRect.x = x;
    widgetRect.y = y;
    widgetRect.w = w;
    widgetRect.h = h;
}

bool Widget::containsPoint(int x, int y) const
{
    return (x >= widgetRect.x && x <= widgetRect.x + widgetRect.w &&
            y >= widgetRect.y && y <= widgetRect.y + widgetRect.h);
}