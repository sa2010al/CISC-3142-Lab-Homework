//
//  main.cpp
//  Lab 1
//
//  Created by Saleh Mosleh on 2/16/22.
//

#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <numeric>
#include <sstream>
#include <vector>
using namespace std;

// This function takes in a string, iterates over it
// and replaces occurrences of char 'at' with 'with'
void replace(string &line, char at, char with)
{
    for(int i = 0; i < line.length(); i++)
    {
        if(line[i] == at)
        {
            line[i] = with;
        }
    }
}

// This function calculates the average prices per brand
void calculateAveragePerBrand(vector<string> vBrand, vector<float> vPrice, ofstream& out_stream)
{
    // Declaring a map to store the prices band wise
    map<string,vector<float> > brandMap;
    
    // Storing the prices band wise
    for(int i = 0; i < vBrand.size(); i++)
    {
        brandMap[vBrand[i]].push_back(vPrice[i]);
    }

    // Writing the headers to the output file
    out_stream << "\tBrand\tAverage\n";
    
    // Declaring an iterator for map to iterate over the map
    map<string,vector<float> >::iterator it;
    
    // Iterating over the map
    for(it = brandMap.begin(); it != brandMap.end(); ++it)
    {
        // Storing the current brand
        string curBrand = it->first;
        // Storing the prices of current brand
        vector<float> curPrices = it->second;
        // Storing the sum of prices of current brand
        float brandSum = accumulate(curPrices.begin(), curPrices.end(),0.0);
        // Calculating the average of prices of current brand
        float average = brandSum / curPrices.size();
        
        // Writing the brand name and it's average to the output file
        out_stream << "\t" << curBrand << "\t" << average << "\n";
    }
    // Writing a newline to the output file
    out_stream << endl;
}

// This function calculates the average prices per category
void calculateAveragePerCategory(vector<string> vCategory, vector<float> vPrice, ofstream& out_stream)
{
    // Declaring a map to store the prices category wise
    map<string,vector<float> > categoryMap;
    // Storing the prices category wise
    for(int i = 0; i < vCategory.size(); i++)
    {
        categoryMap[vCategory[i]].push_back(vPrice[i]);
    }

    // Writing the headers to the output file
    out_stream << "\tCategory\tAverage\n";
    
    // Declaring an iterator for map to iterate over the map
    map<string,vector<float> >::iterator it;
    
    // Iterating over the map
    for(it = categoryMap.begin(); it != categoryMap.end(); it++)
    {
        // Storing the current category
        string curCategory = it->first;
        // Storing the prices of current category
        vector<float> curPrices = it->second;
        // Storing the sum of prices of current category
        float brandSum = accumulate(curPrices.begin(), curPrices.end(),0.0);
        // Calculating the average of prices of current category
        float average = brandSum / curPrices.size();

        // Writing the category name and it's average to the output file
        out_stream << "\t" << curCategory << "\t" << average << "\n";
    }
    // Writing a newline to the output file
    out_stream << endl;
}

void calculateSKUCount(vector<int> vYear,vector<int> vSKU, ofstream& out_stream)
{
    // Declaring a map to store the sku's year wise
    map<int,vector<int> > yearMap;
    
    // Storing the sku's band wise
    for(int i = 0; i < vYear.size(); i++)
    {
        yearMap[vYear[i]].push_back(vSKU[i]);
    }

    // Writing the headers to the output file
    out_stream << "\tYear\tSKU's\n";
    
    // Declaring an iterator for map to iterate over the map
    map<int,vector<int> >::iterator it;
    
    // Iterating over the map
    for(it = yearMap.begin(); it != yearMap.end(); it++)
    {
        // Writing the year to the output file
        out_stream << it->first << "\t";

        // Declaring an iterator to iterate over the vector for the current year
        vector<int>::iterator sku_it;

        // Iterating over sku's for current year
        for(sku_it = it->second.begin(); sku_it != it->second.end(); sku_it++)
        {
            // Writing the sku to the output file
            out_stream << *sku_it;

            // If this is not the last sku for current year, write a space to the output file
            if(sku_it != it->second.end())
            {
                out_stream << " ";
            }
            // Else, write a tab to the output file
            else
            {
                out_stream << "\t";
            }
        }
        // Writing the number of sku's for current year to the output file
        out_stream << "(Count: " << it->second.size() << ")" << endl;
    }
}

int main()
{

    // Defining vectors to store values for each column
    vector<int> vSKU;
    vector<string> vBrand;
    vector<string> vCategory;
    vector<int> vYear;
    vector<float> vPrice;

    // This variable reads data from the file
    ifstream in_stream;
    // This variable writes data to the file
    ofstream out_stream;
    
    in_stream.open("data.csv"); // opening the input file.
    out_stream.open("output.txt");// opening the output file
    
    // If file is opened
    if (!in_stream.fail())
    {

        // This variable stores the current line read from the file
        string line;
        
        // Reading the header line but not using it, because it is not needed
        getline(in_stream,line);

        // while the end of file is NOT reached
        while (getline(in_stream, line))
        {
            // Replacing commas with spaces
            replace(line,',',' ');
            
            // Storing the line to the ss object
            stringstream ss(line);
            
            // Declaring and storing values for each column for current row
            int iSKU;
            string brand;
            string category;
            int iYear;
            float fPrice;
            
            ss >> iSKU;
            ss >> brand;
            ss >> category;
            ss >> iYear;
            ss >> fPrice;

            // Writing values into the vectors
            vSKU.push_back(iSKU);
            vBrand.push_back(brand);
            vCategory.push_back(category);
            vYear.push_back(iYear);
            vPrice.push_back(fPrice);
        }

        in_stream.close(); // closing the file
    }
    // Else
    else
    {
        out_stream << "Unable to open file";
    }
    
    // Writing headers to the output file
    out_stream << "SKU" << "\t" << "Brand" << "\t" << "Category" << "\t\t" << "Year" << "\t" << "Price" << endl;

    // Writing rows read to the output file
    for (int j = 0; j < vSKU.size(); j++)
    {
            out_stream << vSKU[j] << "\t" << vBrand[j] << "\t   " << vCategory[j] << "\t\t" << vYear[j] << "\t" << vPrice[j] << endl;
    }
    // Writing a newline to the output file
    out_stream << endl;

    // Calculating the average price per brand and storing them in the output file
    calculateAveragePerBrand(vBrand,vPrice,out_stream);
    
    // Calculating the average price per category and storing them in the output file
    calculateAveragePerCategory(vCategory,vPrice,out_stream);

    // Calculating the SKU count for each year and storing them in the output file
    calculateSKUCount(vYear,vSKU, out_stream);
    
    // Closing the input and output files
    in_stream.close();
    out_stream.close();
}
