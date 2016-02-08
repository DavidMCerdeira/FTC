#ifndef FTC_FRAME_H
#define FTC_FRAME_H

#include <string>

using namespace std;
/*
    This class manages the structure of a frame,
    in case of being a request or a response frame.
*/

#define CHAR_FRAME_DIVIDER 47  // '/' slash char

class FTC_Frame
{
public:
    FTC_Frame(string full_frame);
    FTC_Frame(string frame_Specific, string data);

    string get_fullFrame();
    string get_frameData();
    string get_frameSpecific();

private:
    static string frame_header;
    string full_frame;
    string frame_data;
    string frame_specific;
};

#endif // FTC_FRAME_H
