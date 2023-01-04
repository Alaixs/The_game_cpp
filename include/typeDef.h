#ifndef TYPEDEF_H
#define TYPEDEF_H

/*
 * Element of a list
 */
struct Element
{
    int value = 0;
    Element * next = nullptr;
};

/*
 * Definition of a list
 */
struct List
{
    int size = 0;
    Element * first = nullptr;
};

#endif // TYPEDEF_H