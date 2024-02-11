#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Song {
    public:
        string title = "";
        string author = "";
        string lyrics = "";
        int year = 0;

        Song(string title, string author, string lyrics, int year) {
            this->title = title;
            this->author = author;
            this->lyrics = lyrics;
            this->year = year;
            prepare_lyrics_lines();

            printf("New song made: %s - %s \n", author.c_str(), title.c_str());
        }

        /** Print a song line(s) */
        Song sing(int max_lines = -1) {
            /** If song printed for the first time, print the header */
            if (sing_position_line == 0) {
                print_header();
            }
            
            /** Print all lines if nothing or negative number provided */
            for (int i = 0; i < (max_lines < 0 ? lyrics_lines.size() : max_lines); i++) {
                print_sing_line();
            }

            return *this;
        }

        /** Yell a song line(s) */
        Song yell(int max_lines = -1) {
            /** If song printed for the first time, print the header */
            if (yell_position_line == 0) {
                print_header();
            }
            
            /** Print all lines if nothing or negative number provided */
            for (int i = 0; i < (max_lines < 0 ? uppercase_lyrics_lines.size() : max_lines); i++) {
                print_yell_line();
            }

            return *this;
        }


    protected:
        int sing_position_line = 0;
        int yell_position_line = 0;
        vector<string> lyrics_lines;
        vector<string> uppercase_lyrics_lines;

        /** Prints the header of the song as "Author - Title (Year)" */
        void print_header() {
            printf("%s - %s (%d)\n", author.c_str(), title.c_str(), year);
        }

        /** Sings the next line and increments its counter */
        void print_sing_line() {
            if (sing_position_line < lyrics_lines.size()) {
                printf("%s\n", lyrics_lines[sing_position_line].c_str());
                sing_position_line++;
            }
        }

        /** Yells the next line and increments its counter */
        void print_yell_line() {
            if (yell_position_line < uppercase_lyrics_lines.size()) {
                printf("%s\n", uppercase_lyrics_lines[yell_position_line].c_str());
                yell_position_line++;
            }
        }

        void prepare_lyrics_lines() {
            /** Split lyrics in lines and save for later */
            vector<char> line;
            for(char ch: lyrics) {
                if (ch == '\n') {
                    lyrics_lines.push_back(string(line.begin(), line.end()));
                    line.clear();

                } else {
                    line.push_back(ch);
                }
            }

            lyrics_lines.push_back(string(line.begin(), line.end()));
            prepare_uppercase_lyrics_lines();
        }

        /** Transfer the whole lyrics to uppercase */
        void prepare_uppercase_lyrics_lines() {
            uppercase_lyrics_lines = lyrics_lines;
            
            for (int i = 0; i < uppercase_lyrics_lines.size(); i++) {
                // From https://stackoverflow.com/a/735215
                transform(uppercase_lyrics_lines[i].begin(), uppercase_lyrics_lines[i].end(), uppercase_lyrics_lines[i].begin(), ::toupper);
            }
        }
};