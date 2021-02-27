#ifndef __BORDERS_H
#define __BORDERS_H

#define B_LEFT_TOP      "┌"
#define B_LEFT_MIDDLE   "├"
#define B_LEFT_BOTTOM   "└"
#define B_RIGHT_TOP     "┐"
#define B_RIGHT_MIDDLE  "┤"
#define B_RIGHT_BOTTOM  "┘"
#define B_HORIZONTAL    "─"
#define B_VERTICAL      "│"

#define BORDER(border) (void)printf("%s", border);

#endif /*__BORDERS_H*/
