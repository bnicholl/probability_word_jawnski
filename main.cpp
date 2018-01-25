//
//  main.cpp
//  proj_one
//
//  Created by Ben Nicholl on 1/23/18.
//  Copyright © 2018 Ben Nicholl. All rights reserved.
//
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <fstream>

class word_prob {
//this map is where all of our words and word counts will go to
std::map<std::string, int> words;
public:
    //this method counts how many words are in a geven text
    std::map<std::string, int> count_words(std::string corpus) {
        //each word will be put into this vector, than deleted when we see a space
        std::vector<char> vec;
        for (char i :corpus){
            //if we are still on the same word(no space) push character into vec
            if (i != ' ')
            {
                vec.push_back(i); //this pushes each element into the vector vec
            }
            //if the word has ended (we get a space character)
            else if ( i == ' ' )
            {
                //breaks at integer position for strings with (., ?, !, etc)
                int number = -1;
                //for (auto iter = std::begin(vec); iter != std::end(vec); ++iter)// this is another way to write loop//
                for (auto iter = vec.begin(); iter != vec.end(); ++iter)
                {
                    ++number;
                    //get rid of all of the below puncuations
                    if (*iter == '.' | *iter == '?' | *iter == '!' | *iter == ',' | *iter == '"' | *iter == ';')
                    {
                        vec.erase(vec.begin() + number);//
                        //we have to go back one in the vector so our loop doesnt iterate through the newly deleted, null value because
                        //value doesnt get deleted until after it leaves its scope, in this case the scope is current iteration in loop
                        --iter;
                    }
                }
                //declare a method as a string. use begin() and end() to iterate through char's in vec, thus turning vec into string.
                std::string str(vec.begin(), vec.end() );
                //erase the vecotr, vec, whcih was containing the individual word
                vec.erase(vec.begin(), vec.end() );
                
                //if this is a new word, thus it doesnt exist in our words map, create it in our map and assign it 1
                if (words.find(str) == words.end() )
                {
                    words[str] = 1;
                }
                //if this is not a new word, than the word is our string variable, thus add 1 to the pre-existing word
                else if (words.find(str) != words.end() )
                {
                    words[str] ++;
                }              
            }
        }
        //this simply prints our our dictionary
        for (auto i : words)
        {
            std::cout << i.first << i.second << std::endl;
        }
        return words;
    }
    //this method turns those counted words into probability values
    void calculate_prob()
    {        
        //this map will be the probability version of our words map from previous method
        std::map<std::string, float> probabilities;
        //this float will be the sum of our words map values
        float sum = 0.00;
        
        //this loop gets the sum of the values in our words map from the previous method
        for (auto it = std::begin(words); it != std::end(words); ++it)
        {
            sum = sum + (*it).second;
        }
        //this loop divides our values from our words map by the sum, thus getting our probabilities
        //we than put those probability values with their cooresponding keys in a seperate map named porbabilities
        for (auto i : words)
        {
            float value = i.second/sum;
            probabilities[i.first] = value;
        }
        
        //this simply prints our our probability map
        for (auto i : probabilities)
        {
            std::cout << i.first << i.second << std::endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    
    //open txt file in a cpp file, and it will show you what getfile method is reading
    //you can than delete any garbage text, and resave it as a txt or cpp file
    //put a space at the end of the text
    //ensure the path is the correct link to the text you are uploading, than run to upload text
    std::ifstream file("/Users/bennicholl/Desktop/Untitled.txt");
    std::string strr;
    std::string file_contents;
    //this loop appends the words in string format to the std::string file_contents variable
    while (std::getline(file, strr))
    {
        file_contents += strr;
        file_contents.push_back('\n');
    }
    //std::cout << file_contents;   //unslash to print conents
    
    //example exerpt from the greatest movie ever made. (ggogle it if you dont recognize it)
    std::string text = "Steven is my name! I'm the most wanted man on my island, of course I'm not on my island. ";
    
    word_prob example;
    example.count_words(text);
    example.calculate_prob();
    return 0; 
};







