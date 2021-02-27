#ifndef COLORS_H

#define COLORS_H

#define BLACK   "\x1B[0;30m" // Black - Regular
#define RED     "\x1B[0;31m" // Red
#define GREEN   "\x1B[0;32m" // Green
#define YELLOW  "\x1B[0;33m" // Yellow
#define BLUE    "\x1B[0;34m" // Blue
#define PURPLE  "\x1B[0;35m" // Purple
#define CYAN    "\x1B[0;36m" // Cyan
#define WHITE   "\x1B[0;37m" // White

#define BLACK_BOLD  "\x1B[1;30m" // Black - Bold
#define RED_BOLD    "\x1B[1;31m" // Red
#define GREEN_BOLD  "\x1B[1;32m" // Green
#define YELLOW_BOLD "\x1B[1;33m" // Yellow
#define BLUE_BOLD   "\x1B[1;34m" // Blue
#define PURPLE_BOLD "\x1B[1;35m" // Purple
#define CYAN_BOLD   "\x1B[1;36m" // Cyan
#define WHITE_BOLD  "\x1B[1;37m" // White

#define BLACK_UNDERLINE   "\x1B[4;30m" // Black - Underline
#define RED_UNDERLINE     "\x1B[4;31m" // Red
#define GREEN_UNDERLINE   "\x1B[4;32m" // Green
#define YELLOW_UNDERLINE  "\x1B[4;33m" // Yellow
#define BLUE_UNDERLINE    "\x1B[4;34m" // Blue
#define PURPLE_UNDERLINE  "\x1B[4;35m" // Purple
#define CYAN_UNDERLINE    "\x1B[4;36m" // Cyan
#define WHITE_UNDERLINE    "\x1B[4;37m" // White

#define BLACK_BACKGROUND  "\x1B[40m"   // Black - Background
#define RED_BACKGROUND    "\x1B[41m"   // Red
#define GREEN_BACKGROUND  "\x1B[42m"   // Green
#define YELLOW_BACKGROUND "\x1B[43m"   // Yellow
#define BLUE_BACKGROUND   "\x1B[44m"   // Blue
#define PURPLE_BACKGROUND "\x1B[45m"   // Purple
#define CYAN_BACKGROUND   "\x1B[46m"   // Cyan
#define WHITE_BACKGROUND  "\x1B[47m"   // White
#define TEXT_RESET        "\x1B[0m"    // Text Reset

#define COLORIZE(color, msg) (void)printf("%s%s%s", color, msg, TEXT_RESET);

#endif /* end of include guard: COLORS_H */
