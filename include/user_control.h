#pragma once



class User_control
{
    public:
        enum
        {
            NOTHING,
            EXIT
        };
        User_control(){}
        ~User_control(){}

        Do();
        int cmd;
    protected:

    private:

};