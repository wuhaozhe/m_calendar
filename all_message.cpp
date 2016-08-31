#include "all_message.h"

All_Message::All_Message()
{
    config_filename = "config.txt";
    explain_config(config_filename.c_str());
}

void All_Message::explain_config(string filename)
{
    filename = config_filename;
    ifstream fin;
    fin.open(filename.c_str());
    vector<string> all_config;
    string temp_input;
    while(getline(fin, temp_input))
    {
        all_config.push_back(temp_input);
        temp_input.clear();
    }
    /*for(int i = 0; i < all_config.size(); i++)
    {
        qDebug()<<qPrintable(QString::fromStdString(all_config[i]));
    }*/
    vector< vector<string> >  deal_all_config;
    int deal_all_config_index = -1;            //index of deal_all_config
    for(int i = 0; i < all_config.size(); i++)
    {
        string gettime;
        gettime.clear();
        for(int j = 0; j < 6; j++)
        {
            if(j == all_config[i].size())
                break;
            //qDebug()<<qPrintable(QString::fromStdString(gettime));
            gettime += all_config[i][j];
        }
        if(gettime == "time&:")
        {
            deal_all_config_index++;
            vector<string> temp;
            deal_all_config.push_back(temp);
        }
        if(deal_all_config_index >= 0)
            deal_all_config[deal_all_config_index].push_back(all_config[i]);
    }

    for(int i = 0; i < deal_all_config.size(); i++)
    {
        //qDebug()<<i;
        deal_each_day(deal_all_config[i]);
    }
    fin.close();
    //qDebug("hehe");
}

void All_Message::deal_each_day(vector<string> string_array)
{
    string date;
    for(int i = 7; i < string_array[0].size(); i++)
        date += string_array[0][i];
    //qDebug()<<qPrintable(QString::fromStdString(date));
    vector<event> m_vector;
    for(int i = 1; i < string_array.size(); i++)
    {
        string filename;
        int flag = 0;
        while(string_array[i][flag] != ' ')
        {
            filename += string_array[i][flag];
            flag++;
        }
        flag++;
        string s_color_r, s_color_g, s_color_b;
        while(string_array[i][flag] != ' ')
        {
            s_color_r += string_array[i][flag];
            flag++;
        }
        flag++;
        while(string_array[i][flag] != ' ')
        {
            s_color_g += string_array[i][flag];
            flag++;
        }
        flag++;
        while(string_array[i][flag] != ' ')
        {
            s_color_b += string_array[i][flag];
            flag++;
        }
        flag++;
        int color_r, color_g, color_b;
        stringstream ss;
        ss<<s_color_r;
        ss>>color_r;
        ss.clear();
        ss<<s_color_g;
        ss>>color_g;
        ss.clear();
        ss<<s_color_b;
        ss>>color_b;
        ss.clear();
        QColor return_color = QColor(color_r, color_g, color_b);
        string event_mode;
        event_mode.clear();
        while(string_array[i][flag] != ' ' && (flag < string_array[i].size()))
        {
            event_mode += string_array[i][flag];
            flag++;
        }
        flag++;
        int return_flag = 0;
        //qDebug()<<qPrintable(QString::fromStdString(event_mode));
        //qDebug()<<event_mode.size();
        if(event_mode == "byday")
        {
            //qDebug()<<1;
            return_flag = 0;
        }
        else if(event_mode == "byweek")
        {
            //qDebug()<<2;
            return_flag = 1;
        }
        else if(event_mode == "bymonth")
        {
            //qDebug()<<3;
            return_flag = 2;
        }
        //qDebug()<<return_flag;
        event return_event(return_flag, return_color, filename);
        m_vector.push_back(return_event);

        vector<string> temp_vector;
        string temp_num;
        for(; flag < string_array[i].size(); flag++)           //deal with _d info
        {
            if(string_array[i][flag] == ' ')
            {
                temp_vector.push_back(temp_num);
                temp_num.clear();
                continue;
            }
            else
            {
                temp_num += string_array[i][flag];
            }
        }
        temp_vector.push_back(temp_num);
        vector<string> temp_date_vector;
        for(int j = 0; j < (temp_vector.size() / 3); j++)
        {
            string temp_date;
            for(int k = 0; k < 3; k++)
            {
                temp_date += temp_vector[3 * j + k];
                if(k < 2)
                    temp_date += '-';
            }
            temp_date_vector.push_back(temp_date);
        }
        delete_info[make_pair(date, filename)] = temp_date_vector;
    }
    m_map[date] = m_vector;
}
int All_Message::index(int year, int month, int day)
{
    core temp;
    QVector<int> out_put = temp.get_num(year, month);
    for(int i = 0; i < 40; i++)
    {
        if(i % 8 == 0)
        {
            continue;
        }
        else
        {
            if(out_put[i] > 20 && i < 20)
            {
                continue;
            }
            else if(out_put[i] < 20 && i > 30)
            {
                continue;
            }
            else
            {
                if(out_put[i] == day)
                    return i;
            }
        }
    }
    return -1;
}

void All_Message::set_widget_message(event &temp_event, widget_message &temp_message, string temp_date)
{
    temp_message.color = temp_event.event_color;
    temp_message.filedate.push_back(temp_date);
    temp_message.filename.push_back(temp_event.filename);
    ifstream fin;
    string context;
    string specific_dir;
    specific_dir += temp_message.dir;
    specific_dir += temp_date;
    specific_dir += '\\';
    specific_dir += temp_event.filename;
    fin.open(specific_dir.c_str());
    char a;
    while(fin.get(a))
    {
        context += a;
    }
    temp_message.filecontent.push_back(context);
    fin.close();
    temp_message.happen_flag = temp_event.happen_flag;
}

void All_Message::assign_message(int year, int month)
{
    m_map.clear();
    clear_each_message();
    explain_config(config_filename.c_str());
    for(map< string, vector<event> >::iterator iter = m_map.begin(); iter != m_map.end(); iter++)
    {
        //qDebug("hehe");
        string temp_date = iter->first;
        vector<event> temp_event = iter->second;                //该文件夹下对应的事件
        int temp_year, temp_month, temp_day;

        string string_year, string_month, string_day;         //deal temp_date
        int flag = 0;
        for(int i = 0; i < temp_date.size(); i++)
        {
            if(temp_date[i] == '-')
            {
                flag++;
            }
                if(flag == 0 && temp_date[i] != '-')
            {
                string_year += temp_date[i];
            }
            else if(flag == 1 && temp_date[i] != '-')
            {
                string_month += temp_date[i];
            }
            else if(flag == 2 && temp_date[i] != '-')
            {
                string_day += temp_date[i];
            }
        }
        stringstream ss;
        ss<<string_year;
        ss>>temp_year;
        ss.clear();
        ss<<string_month;
        ss>>temp_month;
        ss.clear();
        ss<<string_day;
        ss>>temp_day;
        ss.clear();


        for(int i = 0; i < temp_event.size(); i++)           //deal each event!
        {
            //qDebug("hehe");
            //qDebug()<<i<<" "<<temp_event[i].happen_flag;
            if(temp_event[i].happen_flag == 0)
            {
                if(year == temp_year && month == temp_month)
                {
                    set_widget_message(temp_event[i], each_message[index(year, month, temp_day)], temp_date);
                    //qDebug()<<year<<" "<<month<<" "<<temp_day;
                }
            }
            if(temp_event[i].happen_flag == 1)
            {
                //qDebug()<<temp_year<<" "<<temp_month<<" "<<temp_day<<"\n";
                int day_of_week = QDate(temp_year, temp_month, temp_day).dayOfWeek();
                //qDebug()<<day_of_week;
                int count = 0;
                vector<int> temp_vector;                //索引
                while(8 * count + day_of_week < 40)
                {
                    //qDebug()<<8 * count + day_of_week + 1;
                    temp_vector.push_back(8 * count + day_of_week);
                    count++;
                }
                vector<int> day_of_date;
                core temp;
                QVector<int> temp_index = temp.get_num(year, month);
                for(int j = 0; j < temp_vector.size(); j++)
                {
                    day_of_date.push_back(temp_index[temp_vector[j]]);
                }
                for(int j = 0; j < day_of_date.size(); j++)
                {
                    if(judge(temp_date, temp_event[i].filename , year, month, day_of_date[j]))
                    {
                        if(j == 0)
                        {
                            if(day_of_date[j] < day_of_date[j + 1])
                            {
                                //qDebug()<<year<<" "<<month<<" "<<day_of_date[j]<<"\n";
                                set_widget_message(temp_event[i], each_message[index(year, month, day_of_date[j])], temp_date);
                            }
                        }
                        else if(j == day_of_date.size() - 1)
                        {
                            if(day_of_date[j] > day_of_date[j - 1])
                            {
                                //qDebug()<<year<<" "<<month<<" "<<day_of_date[j]<<"\n";
                                //qDebug()<<day_of_date[j]<<" "<<day_of_date[j - 1];
                                set_widget_message(temp_event[i], each_message[index(year, month, day_of_date[j])], temp_date);
                            }
                        }
                        else
                        {
                            //qDebug()<<year<<" "<<month<<" "<<day_of_date[j]<<"\n";
                            set_widget_message(temp_event[i], each_message[index(year, month, day_of_date[j])], temp_date);
                        }
                        //qDebug()<<year<<" "<<month<<" "<<day_of_date[j]<<"\n";
                    }
                }
            }
            if(temp_event[i].happen_flag == 2)
            {
                int m_index = index(year, month, temp_day);
                if(m_index > 0)
                {
                    if(judge(temp_date, temp_event[i].filename, year, month, temp_day))
                    {
                        //qDebug()<<year<<" "<<month<<" "<<temp_day<<"\n";
                        set_widget_message(temp_event[i], each_message[m_index], temp_date);
                    }
                }
            }
        }
    }
}

void All_Message::change_message(widget_message temp_message)
{
    //qDebug()<<temp_message.color.red()<<" "<<temp_message.color.green()<<" "<<temp_message.color.blue();
    //qDebug("pu");
    //qDebug()<<qPrintable(QString::fromStdString(temp_message.filedate[0]));
    ifstream fin;
    fin.open(config_filename.c_str());
    vector<string> config_content;
    string temp_content;
    int date_existed = 0;
    int date_checked = 0;      //whether the date has been checked
    while(getline(fin, temp_content))
    {
        int flag = 0;
        string identify;          //identify whether the head is time&:
        for(; flag < 6; flag++)
        {
            identify += temp_content[flag];
        }
        if(date_existed == 0)
            config_content.push_back(temp_content);
        else if(date_existed == 1 && identify == "time&:")
        {
            date_existed = 0;
            config_content.push_back(temp_content);
        }
        else
            continue;
        if(identify == "time&:")
        {
            flag++;
            string temp_date;
            for(; flag < config_content[config_content.size() - 1].size(); flag++)
            {
                temp_date += config_content[config_content.size() - 1][flag];
            }
            int vec_flag = -1;           //search temp_date
            for(int i = 0; i < temp_message.filedate.size(); i++)
            {
                if(temp_date == temp_message.filedate[i])
                {
                    vec_flag = i;
                    date_existed = 1;
                    date_checked = 1;
                        string temp_line;
                        temp_line += temp_message.filename[vec_flag];
                        temp_line += " ";
                        stringstream ss;
                        ss<<temp_message.color.red();
                        string ttemp;
                        ss>>ttemp;
                        temp_line += ttemp;
                        temp_line += " "; ss.clear(); ttemp.clear();
                        ss<<temp_message.color.green();
                        ss>>ttemp;
                        temp_line += ttemp; ss.clear(); ttemp.clear();
                        temp_line += " ";
                        ss<<temp_message.color.blue();
                        ss>>ttemp;
                        temp_line += ttemp;
                        if(temp_message.happen_flag== 0)
                        {
                            //qDebug()<<i<<" "<<temp_message.happen_flag.size();
                            temp_line += " byday";
                        }
                        else if(temp_message.happen_flag == 1)
                        {
                            //qDebug()<<temp_message.happen_flag.size();
                            temp_line += " byweek";
                        }
                        else if(temp_message.happen_flag == 2)
                        {
                            //qDebug()<<temp_message.happen_flag.size();
                            temp_line += " bymonth";
                        }
                        config_content.push_back(temp_line);

                        string specific_dir;
                        specific_dir += temp_message.dir;
                        specific_dir += temp_message.filedate[vec_flag];
                        specific_dir += '\\';
                        specific_dir += temp_message.filename[vec_flag];                              //write the file again
                        ofstream fout;
                        fout.open(specific_dir.c_str());
                        fout<<temp_message.filecontent[vec_flag];
                        fout.close();

                }
            }
        }
    }
    fin.close();
    //qDebug("3");
    if(date_checked == 0)
    {
        QDir *m_dir = new QDir();
        if(!temp_message.filedate.empty())
        {m_dir->mkdir(QString::fromStdString(temp_message.filedate[0]));      //only possible to the pointed day
        string temp_line;
        temp_line += "time&: ";
        temp_line += temp_message.filedate[0];
        config_content.push_back(temp_line);
        temp_line.clear();
        temp_line += temp_message.filename[0];
        temp_line += ' ';
        for(int i = 0; i < temp_message.filename.size(); i++)
        {
            stringstream ss;
            ss<<temp_message.color.red();
            string ttemp;
            ss>>ttemp;
            temp_line += ttemp;
            temp_line += " "; ss.clear(); ttemp.clear();
            ss<<temp_message.color.green();
            ss>>ttemp;
            temp_line += ttemp; ss.clear(); ttemp.clear();
            temp_line += " ";
            ss<<temp_message.color.blue();
            ss>>ttemp;
            temp_line += ttemp;
            if(temp_message.happen_flag == 0)
                temp_line += " byday";
            else if(temp_message.happen_flag == 1)
                temp_line += " byweek";
            else if(temp_message.happen_flag == 2)
                temp_line += " bymonth";
            config_content.push_back(temp_line);
            temp_line.clear();

            string specific_dir;
            specific_dir += temp_message.dir;
            specific_dir += temp_message.filedate[0];
            specific_dir += '\\';
            specific_dir += temp_message.filename[i];                              //write the file again
            ofstream fout;
            //qDebug("3");
            /*if(fout)
                qDebug("success");
            else
                qDebug("failed");*/
            fout.open(specific_dir.c_str());
            if(fout)
            {
                fout<<temp_message.filecontent[i];
                fout.close();
            }
        }
        }
    }
    ofstream fout;
    fout.open(config_filename.c_str());
    if(fout)
    {
        for(int i = 0; i < config_content.size(); i++)
        {
            fout<<config_content[i]<<"\n";
        }
    }
    fout.close();
}

void All_Message::assign_delete_message(int year, int month, int day, string from_date, string file_name, int delete_filemode)
{
    string s_year, s_month, s_day, delete_filedate;
    stringstream ss;
    ss<<year; ss>>s_year; ss.clear();
    ss<<month; ss>>s_month; ss.clear();
    ss<<day; ss>>s_day; ss.clear();
    delete_filedate += s_year;
    delete_filedate += '-';
    delete_filedate += s_month;
    delete_filedate += '-';
    delete_filedate += s_day;

    auto temp_vector = m_map[from_date];
    for(int i = 0; i < temp_vector.size(); i++)
    {
        //qDebug()<<i<<" "<<qPrintable(QString::fromStdString(temp_vector[i].filename))<<"\n";
        if(file_name == temp_vector[i].filename)
        {
            //qDebug()<<temp_vector[i].happen_flag;
            if(delete_filemode == temp_vector[i].happen_flag)
            {
                delete_configline(from_date, file_name);
                string dir; dir += from_date; dir += '/'; dir += file_name;
                //qDebug()<<qPrintable(QString::fromStdString(dir));
                QFile::remove(dir.c_str());
            }
            else
            {
                pair<string, string> temp_pair = make_pair(from_date, file_name);
                if(delete_info.find(temp_pair) != delete_info.end())
                {
                    delete_info[temp_pair].push_back(delete_filedate);
                }
                else
                {
                    vector<string> a; a.push_back(delete_filedate);
                    delete_info[temp_pair] = a;
                }

                add_delete_info(year, month, day, from_date, file_name);
            }
        }
    }
}

void All_Message::delete_configline(string delete_filedate, string delete_filename)
{
    vector<string> config_text;
    ifstream fin;
    fin.open(config_filename.c_str());
    string temp;
    while(getline(fin, temp))
    {
        //qDebug()<<qPrintable(QString::fromStdString(temp));
        config_text.push_back(temp);
    }
    fin.close();

    ofstream fout;
    fout.open(config_filename.c_str());
    int index = search_index(delete_filedate, delete_filename, config_text);
    for(int i = 0; i < config_text.size(); i++)
    {
        if(i != index)
        {
            fout<<config_text[i]<<"\n";

        }
    }
    fout.close();
    //qDebug()<<index;
}

void All_Message::add_delete_info(int year, int month, int day, string from_date, string file_name)
{
    vector<string> config_text;
    ifstream fin;
    fin.open(config_filename.c_str());
    string temp;
    while(getline(fin, temp))
    {
        //qDebug()<<qPrintable(QString::fromStdString(temp));
        config_text.push_back(temp);
    }
    int index = search_index(from_date, file_name, config_text);
    ofstream fout;
    fout.open(config_filename.c_str());
    for(int i = 0; i < config_text.size(); i++)
    {
        if(i != index)
            fout<<config_text[i]<<"\n";
        else
        {
            string s_year, s_month, s_day, delete_filedate;
            stringstream ss;
            ss<<year; ss>>s_year; ss.clear();
            ss<<month; ss>>s_month; ss.clear();
            ss<<day; ss>>s_day; ss.clear();
            fout<<config_text[i]<<" "<<s_year<<" "<<s_month<<" "<<s_day<<"\n";
        }
    }
    fout.close();
}

int All_Message::search_index(string file_date, string file_name, vector<string> input)
{
    for(int i = 0; i < input.size(); i++)
    {
        string line_start;
        string temp_date;
        int flag = 0;
        for(; flag < 6; flag++)
        {
            line_start += input[i][flag];
        }
        flag++;
        if(line_start == "time&:")
        {
            for(; flag < input[i].size(); flag++)
                temp_date += input[i][flag];
        }
        if(temp_date == file_date)
        {
            for(int j = i + 1; j < input.size(); j++)
            {
                //qDebug("hehe");
                int title_flag = 0;
                string temp_filename;
                while(input[j][title_flag] != ' ')
                {
                    //qDebug("hehe");
                    temp_filename += input[j][title_flag];
                    title_flag++;
                }
                if(temp_filename == file_name)
                    return j;
            }
        }
    }
    return 0;
}

bool All_Message::judge(string from_date, string file_name, int year, int month, int day)
{
    string s_year, s_month, s_day, delete_filedate;
    stringstream ss;
    ss<<year; ss>>s_year; ss.clear();
    ss<<month; ss>>s_month; ss.clear();
    ss<<day; ss>>s_day; ss.clear();
    delete_filedate += s_year;
    delete_filedate += '-';
    delete_filedate += s_month;
    delete_filedate += '-';
    delete_filedate += s_day;

    pair<string, string> temp_pair = make_pair(from_date, file_name);
    if(delete_info.find(temp_pair) != delete_info.end())
    {
        vector<string>::iterator it = find(delete_info[temp_pair].begin(), delete_info[temp_pair].end(), delete_filedate);
        if(it != delete_info[temp_pair].end())
            return false;
        else
            return true;
    }
    else
    {
        return true;
    }
}

void All_Message::clear_each_message()
{
    for(int i = 0; i < 40; i++)
    {
        each_message[i].color = Qt::white;
        each_message[i].dir = "";
        each_message[i].delete_filedate.clear();
        each_message[i].delete_filemode = -1;
        each_message[i].delete_fliename.clear();
        each_message[i].filecontent.clear();
        each_message[i].filedate.clear();
        each_message[i].filename.clear();
        each_message[i].happen_flag = -1;
    }
}
