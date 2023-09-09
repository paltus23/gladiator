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
            ENTER,
            EXIT
        };
        User_control_t(){Cmd = NOTHING;}
        ~User_control_t(){}

        Do();
        cmd_t get_cmd()
        {
            auto cmd = Cmd; 
            if(Cmd != NOTHING) 
            {
                ActionsCount++;
                Cmd = NOTHING; 
            }
            return cmd; 
        }

        cmd_t Cmd;

        unsigned int ActionsCount = 0;
    private:

};