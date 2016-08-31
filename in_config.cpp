#include "in_config.h"

in_config::in_config()
{

}

void in_config::set_configname(string temp)
{
    config_name = temp;

    ifstream fin;
    fin.open(temp.c_str());
    string in;
    while(getline(fin, in))
    {
        content.push_back(in);
    }
    read();
}

void in_config::out_configname(string temp)
{
    config_name = temp;
    ifstream fin;
    fin.open("config.txt");
    string in;
    while(getline(fin, in))
    {
        content.push_back(in);
    }
    write(temp);
}

bool in_config::identify_date(string line)
{
    string temp;
    for(int i = 0; i < 6; i++)
        temp += line[i];
    if(temp == "time&:")
        return true;
    else
        return false;
}
string in_config::return_date(string line)
{
    string temp;
    for(int i = 7; i < line.size(); i++)
        temp += line[i];
    return temp;
}

void in_config::read()
{
    ofstream fout;
    fout.open("config.txt");
    string temp_date;
    for(int i = 0; i < content.size(); i++)
    {
        if(identify_date(content[i]))
        {
            QDir *dir = new QDir();
            temp_date = return_date(content[i]);
            dir->mkdir(QString::fromStdString(temp_date));
            fout<<content[i]<<endl;
            delete dir;
        }
        else
        {
            if(content[i][0] != '*')
            {
                string file_name;
                int count = 0;
                while(content[i][count] != ' ')
                {
                    file_name += content[i][count];
                    count++;
                }
                fout<<content[i]<<endl;

                i += 2;                                                    //写文件
                string file_dir = temp_date;
                file_dir += '/';
                file_dir += file_name;
                ofstream out;
                out.open(file_dir.c_str());
                while(content[i][0] != '*')
                {
                    out<<content[i]<<endl;
                    i++;
                }
                out.close();
            }
        }
    }
    fout.close();
}

void in_config::write(string temp)
{
    ofstream fout;
    fout.open(temp.c_str());
    string temp_date;
    for(int i = 0; i < content.size(); i++)
    {
        if(identify_date(content[i]))
        {
            QDir *dir = new QDir();
            temp_date = return_date(content[i]);
            dir->mkdir(QString::fromStdString(temp_date));
            fout<<content[i]<<endl;
            delete dir;
        }
        else
        {
            fout<<content[i]<<endl;
            string file_name;
            int count = 0;
            while(content[i][count] != ' ')
            {
                file_name += content[i][count];
                count++;
            }
            fout<<'*'<<endl;
            string file_dir = temp_date;
            file_dir += '/';
            file_dir += file_name;
            ifstream fin;
            fin.open(file_dir);
            char a;
            while(fin.get(a))
                fout<<a;
            fout<<endl;
            fout<<'*'<<endl;
            fin.close();
        }
    }
    fout.close();
}
