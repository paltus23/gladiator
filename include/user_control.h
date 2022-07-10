#pragma once

#define DEBUG_LVL 0 



class User_control_t
{
    public:
        enum cmd_t
        {
            NOTHING,
            UP,
            DOWN,
            LEFT, 
            RIGHT,
            EXIT
        };
        User_control_t(){}
        ~User_control_t(){}

        Do();
        get_cmd(){auto cmd = Cmd; Cmd = NOTHING; return cmd; }
        cmd_t Cmd;
    private:

};