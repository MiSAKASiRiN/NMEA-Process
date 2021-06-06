//MisakaSirin NMEA interpreter for GNSS
#include <iostream>
#include <string>
std::string GPGtest = "$BDGGA,092204.999,4250.5589,S,14718.5084,E,1,04,24.4,19.7,M,,,,0000*1F";
int debug = 0;
class SirinToolbox 
{
    private:
        std::string tempdata;
        int * currentAddr;

    public:
        std::string Var_split(std::string indata, int start = 0, int end = 1)
        {
            tempdata = "";
            if(debug == 1) 
                {
                    currentAddr = &end;
                    std::cout<<"[Debug]Toolbox:Var_split Start ";
                    std::cout<< start<<"-->"<<end<<" @"<<currentAddr<<std::endl;
                }

            for(int i = start; i < end; i++)
            {
                tempdata.append(1, indata[i]);
                if(debug == 1)
                {
                   std::cout<<"[Debug]Toolbox:Var_split";
                   std::cout<<i<<":"<<tempdata<<std::endl;
                }
            }
            return tempdata;
        };

};
SirinToolbox tb;

class SirinNMEA
{
    private:
        std::string tempdata;
        std::string currentFormat;
        int Hour, Min, Sec, MSec;
        std::string Hour_str, Min_Str, Sec_Str, MSec_Str;
        std::string Latitude;
        std::string LatUnit;
        std::string Longitude;
        std::string LonUnit;
    public:
        int update(std::string indata)
        {
            tempdata = tb.Var_split(indata, 0, 3);
            if(tempdata == "$GP")
            {
                currentFormat = "GPS";
            } else if(tempdata == "$BD")
            {
                currentFormat = "BDS";
            } else {
                std::cout<<tempdata<<std::endl;
                std::cout<<"Not GNSS Format!";
                return 1;
            }
            std::cout<<"SirinNMEA-Rec:"<<std::endl<<currentFormat<<std::endl;

            tempdata = tb.Var_split(indata, 3, 6);
            if(tempdata == "GGA")
            {
                Hour = atoi(tb.Var_split(indata, 7, 9).c_str());
                Min = atoi(tb.Var_split(indata, 9, 11).c_str());
                Sec = atoi(tb.Var_split(indata, 11, 13).c_str());
                MSec = atoi(tb.Var_split(indata, 14, 17).c_str());
                std::cout<<"SirinNMEA-UTC:"<<std::endl;
                std::cout<<Hour<<":"<<Min<<":"<<Sec<<"."<<MSec<<std::endl;
                Latitude = tb.Var_split(indata, 18, 27);
                LatUnit = tb.Var_split(indata, 28, 29);
                std::cout<<"Lat:"<<Latitude<<LatUnit<<std::endl;
                Longitude = Latitude = tb.Var_split(indata, 30, 40);
                LonUnit = tb.Var_split(indata, 41, 42);
                std::cout<<"Long:"<<Longitude<<LonUnit<<std::endl;
            }
            return 0;
        };
};
SirinNMEA nmea;

int main()
{
    std::cout<<"MisakaSirin NMEA DataConvert"<<std::endl;
    nmea.update(GPGtest);
    return 0;

};

