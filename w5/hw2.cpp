// Martins_Prokuratovs_221RDB473
#include "song.cpp"


/** Adding some additional functionality to the Song class */
class Rap : public Song {
    string drop = "";

    public:
        Rap(string title, string author, string lyrics, int year)
            : Song(title, author, lyrics, year) {};

        /** Rap a song line(s) */
        Rap break_it(int max_lines = -1, string drop = "yeah") {
            // From https://stackoverflow.com/a/735215
            transform(drop.begin(), drop.end(), drop.begin(), ::toupper);
            this->drop = drop;

            /** If song printed for the first time, print the header */
            if (break_position_line == 0) {
                print_header();
            }
            
            /** Print all lines if nothing or negative number provided */
            for (int i = 0; i < (max_lines < 0 ? lyrics_lines.size() : max_lines); i++) {
                print_break_line();
            }

            return *this;
        }
    
    private:
        int break_position_line = 0;
        
        /** Prints one line if any left */
        void print_break_line() {
            if (break_position_line < lyrics_lines.size()) {
                for (char ch: lyrics_lines[break_position_line]) {
                    /** If a space encountered, print drop phrase */
                    if (ch == ' ' && !drop.empty()) {
                        printf(" %s", drop.c_str());
                    }

                    printf("%c", ch);
                }

                /** Print drop phrase at the end of the line */
                printf(" %s\n", drop.c_str());
                break_position_line++;
            }
        }
};

int main() {
    auto zrap = Rap("Ziemeļmeita", "Jumprava", "Gāju meklēt ziemeļmeitu\nGaru, tālu ceļu veicu", 1988);
    zrap.break_it(1, "yah");

    return 0;
}