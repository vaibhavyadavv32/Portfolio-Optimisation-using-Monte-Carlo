#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int main() 
{
    ifstream fin("stocks.csv");
    if (!fin.is_open()) 
    {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    ofstream fout("stocks_with_DailyReturns.csv");
    if (!fout.is_open()) 
    {
        cerr << "Failed to open output file." << endl;
        return 1;
    }

    string line;

    getline(fin, line);
    stringstream ss(line);

    vector<string> headers;
    string token;

    while (getline(ss, token, ',')) 
    {
        headers.push_back(token);
    }

    for (size_t i = 0; i < headers.size(); ++i) 
    {
        fout << headers[i];
        if (i != headers.size() - 1) fout << ",";
    }

    for (size_t i = 1; i < headers.size(); ++i)
    {
        fout << "," << headers[i] << "_DailyReturn";
    }
    fout << endl;

    vector<double> prev_prices(headers.size() - 1, 0.0);
    bool first_line = true;

    while (getline(fin, line))
    {
        stringstream ss_line(line);
        vector<string> row_data;
        string val;

        while (getline(ss_line, val, ',')) 
        {
            row_data.push_back(val);
        }

        for (size_t i = 0; i < row_data.size(); ++i) 
        {
            fout << row_data[i];
            if (i != row_data.size() - 1) fout << ",";
        }

        for (size_t i = 1; i < row_data.size(); ++i)
        {
            double curr_price = 0.0;
            try 
            {
                curr_price = stod(row_data[i]);
            } 
            catch (...)
            {
                curr_price = 0.0;
            }

            if (first_line) 
            {
                fout << ",0";
                prev_prices[i - 1] = curr_price;
            } 
            else
            {
                if (prev_prices[i - 1] > 0 && curr_price > 0) 
                {
                    double log_return = log(curr_price / prev_prices[i - 1]);
                    fout << "," << log_return;
                } 
                else 
                {
                    fout << ",0";
                }
                prev_prices[i - 1] = curr_price;
            }
        }

        fout << endl;
        first_line = false;
    }

    fin.close();
    fout.close();

    cout << "Saved CSV with daily log returns: stocks_with_DailyReturns.csv\n";
    return 0;
}