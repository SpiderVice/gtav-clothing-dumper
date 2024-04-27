#pragma once

/*
* The following is taken from: https://gist.github.com/root-cause/3b80234367b0c856d60bf5cb4b826f86
*/
#pragma pack(push, 1)
typedef struct
{
    int lockHash;

    int _pad1;
    int hash;

    int _pad2;
    int locate; // <locate value="..." /> in clothing data

    int _pad3;
    int drawable;

    int _pad4;
    int texture;

    int _pad5;
    int f_5;

    int _pad6;
    int componentType;

    int _pad7;
    int f_7;

    int _pad8;
    int f_8;

    int _pad9;
    char gxt[64];
} PedComponent;
#pragma pack(pop)