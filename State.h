#pragma once

enum Type
{
    ACCESS,
    MASTER,
    DELETE
};

class State
{
  private:
    Type _type;
    unsigned char yellow, red, green;

  public:
    State();
    void setMode(Type t);
    Type getMode(void);
};