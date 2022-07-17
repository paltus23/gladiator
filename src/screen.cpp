#include "screen.h"
#include <cmath>

/**
 * @brief show Screen_mem in console
 */
void Screen_t::show()
{
    COORD point = {0,0};
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // print
    SetConsoleCursorPosition(handle, point);
    // std::cout << Screen_mem;

    COORD dwBufferSize = {Size.x, Size.y};
    COORD dwBufferCoord = {0,0};
    SMALL_RECT writeRegion = {0,0,Size.x - 1, Size.y - 1};

    auto res = WriteConsoleOutput(handle, Screen_mem, dwBufferSize, dwBufferCoord, &writeRegion);
}

void Screen_t::draw_char(int x, int y, CHAR_INFO ch)
{
    memcpy(&Screen[y][x], &ch, sizeof(CHAR_INFO) );
}
/**
 * @brief draw char in Screen_mem
 * @param in x - x coord
 * @param in y - y coord
 * @param in ch - character will be print
 * @param in colorFore - character will be print
 * @param in colorBack - character will be print
 */
void Screen_t::draw_char(int x, int y, char ch, int colorFore, int colorBack)
{
    CHAR_INFO cc; 
    cc.Char.AsciiChar = ch;
    cc.Attributes = (colorBack << 4) | colorFore; 
    draw_char(x, y, cc);
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
            Screen[cur_y][cur_x].Char.AsciiChar = ch;
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
        Screen[cur_y][x].Char.AsciiChar = ch;
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
        Screen[y][cur_x].Char.AsciiChar = ch;
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
/**
 * @brief print string from "chars" to Screen_mem
 * @param in chars - size of console window
 */
void Screen_t::print(int x, int y, char* chars)
{
    memcpy(&Screen[y][x], chars, strlen(chars));
}

/**
 * @brief draw arena
 * @param in arena - 
 * @param in x - start x coord
 * @param in y - start y coord
 */
void Screen_t::draw(Arena_t& arena, int start_x, int start_y)
{
    coord_t size;
    arena.get_size(&size);

    for (int i = 0; i < size.x; i++)
    {
        if( (i + start_x) < 0 || (i + start_x >= Size.x) )
            continue;
        for (int j = 0; j < size.y; j++)
        {
            if( (j + start_y) < 0 || (j + start_y >= Size.y) )
                continue;
            
            char ch = '?';

            switch(arena.Cells2[i][j])
            {
                case Arena_t::NOTHING: ch = ' '; break;
                case Arena_t::WALL: ch = '#'; break;
                case Arena_t::FLOOR: ch = '.'; break;
            }
            
            Screen[j + start_y][i + start_x].Char.AsciiChar = ch;
        }
    }
}

//Fill Screen_mem with spaces
void Screen_t::clear()
{
    CHAR_INFO ch; 
    ch.Char.AsciiChar = ' ';
    ch.Attributes = WHITE;
    fill(ch);
}; 