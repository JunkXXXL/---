#pragma once

class Iterator
{
public:
    Iterator() = default;
    virtual ~Iterator() = default;

    virtual bool exists() const = 0;
    virtual int value() const = 0;
    virtual bool hasNext() const = 0;
    virtual void moveToNext() = 0;
};