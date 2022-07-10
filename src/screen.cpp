#include "screen.h"
#include "windows.h"
#include <cmath>

/**
 * @brief show Screen_mem in console
 */
void Screen_t::show()
{
    COORD point = {0,0};
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // hide cursor
    const CONSOLE_CURSOR_INFO console_cursor_info = {1,false};
    SetConsoleCursorInfo(handle, &console_cursor_info);
    // print
    SetConsoleCursorPosition(handle, point);
    std::cout << Screen_mem;
}


/**
 * @brief draw rectangle in Screen_mem
 * @param in x - start x coord
 * @param in y - start y coord
 * @param in size_x - size on x coord
 * @param in size_y - size on y coord
 * @param ch - character will be print
 */
void Screen_t::draw_rectangle(int x, int y, size_t size_x, size_t size_y, char ch)
{
    int end_x = x + size_x;
    int end_y = y + size_y;

    for(int cur_y = y<0 ? 0 : y; cur_y<Size.y && cur_y<end_y; cur_y++)
    {
        for(int cur_x = x<0 ? 0 : x; cur_x<Size.x && cur_x<end_x; cur_x++)
        {
            Screen[cur_y][cur_x] = ch;
        }
    }
}
/**
 * @brief draw vertical line
 * @param in x - start x coord
 * @param in y - start y coord
 * @param in size - length of line
 * @param ch - character will be print
 */
void Screen_t::draw_vertical_line(int x, int y, size_t size, char ch)
{
    int end_y = y + size;
    for(int cur_y = y<0 ? 0 : y; cur_y<Size.y && cur_y<end_y; cur_y++)
    {
        Screen[cur_y][x] = ch;
    }
}
/**
 * @brief draw horizontal line
 * @param in x - start x coord
 * @param in y - start y coord
 * @param in size - length of line
 * @param ch - character will be print
 */
void Screen_t::draw_horizontal_line(int x, int y, size_t size, char ch)
{
    int end_x = x + size;
    for(int cur_x = x<0 ? 0 : x; cur_x<Size.x && cur_x<end_x; cur_x++)
    {
        Screen[y][cur_x] = ch;
    }
}


/**
 * @brief draw rectangle edge
 * @param in x - start x coord
 * @param in y - start y coord
 * @param in size_x - size on x coord
 * @param in size_y - size on y coord
 * @param ch - character will be print
 */
void Screen_t::draw_rectangle_edge(int x, int y, size_t size_x, size_t size_y, char ch)
{
    int end_x = x + size_x;
    int end_y = y + size_y;

    if(size_y < 1 || size_x < 1)
        return;

    draw_vertical_line(x, y, size_y, ch);
    draw_horizontal_line(x, y, size_x, ch);
    draw_vertical_line(x + size_x - 1, y, size_y, ch);
    draw_horizontal_line(x, y + size_y - 1, size_x, ch);

}
/**
 * @brief get size of console window in chars
 * @param out coord - size of console window
 */
void Screen_t::get_console_size(coord_t *coord)
{
    CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleScreenBufferInfo) )
    {
        coord->x = ConsoleScreenBufferInfo.srWindow.Right - ConsoleScreenBufferInfo.srWindow.Left + 1;
        coord->y = ConsoleScreenBufferInfo.srWindow.Bottom - ConsoleScreenBufferInfo.srWindow.Top + 1;
    }
}

