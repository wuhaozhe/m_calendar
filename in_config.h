#ifndef IN_CONFIG_H
#define IN_CONFIG_H
#include <string>
#include <vector>
#include <fstream>
#include <QDir>
#include <QString>
using namespace std;

class in_config
{
public:
    string config_name;
    vector<string> content;
    void set_configname(string temp);
    void out_configname(string temp);
    bool identify_date(string line);
    string return_date(string line);
    in_config();
    void read();
    void write(string temp);
};

#endif // IN_CONFIG_H
