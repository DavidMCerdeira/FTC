#include "ftc_frame.h"

string FTC_Frame::frame_header="FTCCLANP/";

FTC_Frame::FTC_Frame(string full_frame)
{
    int indx1, indx2;

    this->full_frame = full_frame;

    /*parse frame specific string*/
    indx1 = full_frame.find_first_of(CHAR_FRAME_DIVIDER);
    indx2 = full_frame.find_first_of(CHAR_FRAME_DIVIDER, indx1 + 1);
    this->frame_specific = full_frame.substr(indx1 + 1, (indx2 - indx1) - 1);

    /*parse frame_data string*/
    indx1 = full_frame.find_first_of(CHAR_FRAME_DIVIDER, indx2 + 1);
    this->frame_data = full_frame.substr(indx2 + 1, (indx1 - indx2) - 1);
}

FTC_Frame::FTC_Frame(string specific, string data)
{
    this->frame_specific = specific;
    this->frame_data = data;

    this->full_frame = FTC_Frame::frame_header;
    this->full_frame += '/';
    this->full_frame += this->frame_specific;
    this->full_frame += '/';
    this->full_frame += this->frame_data;
    this->full_frame += "/END";
}

string FTC_Frame::get_frameData()
{
    return this->frame_data;
}

string FTC_Frame::get_frameSpecific()
{
    return this->frame_specific;
}

string FTC_Frame::get_fullFrame()
{
    return this->full_frame;
}

