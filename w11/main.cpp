// Martins_Prokuratovs_221RDB473
// Run `./main.exe -i dancing_men.txt -l` for sample
#include <cstring>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <iterator>

using namespace std;


int main(int argc, char* argv[]) {
    bool lowercase = false;
    string inputFileName = ""; string outputFileName = "";

    // Handle command line arguments
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0)
            lowercase = true;
        if (strcmp(argv[i], "-i") == 0)
            inputFileName = argv[i + 1];
        if (strcmp(argv[i], "-o") == 0)
            outputFileName = argv[i + 1];
    }

    if (inputFileName == "") {
        printf("Input file name is missing");
        return 1;
    }

    if (outputFileName == "")
        outputFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".tsv";

    /** 
     * Needed to interpret UTF-8 characters
     * If exception encountered, as per https://github.com/potree/PotreeConverter/issues/281#issuecomment-375997005
     * Uncomment 'C.UTF-8' in '/etc/locale.gen' and run 'sudo locale-gen'
     */
    locale::global(locale("C.UTF-8"));

    /**
     * Idea of file reading similar as in previous HW.
     * https://stackoverflow.com/a/10057703
     */
    wifstream inputFile(inputFileName, ios::binary);
    vector<wchar_t> fileContent {
        istream_iterator<wchar_t, wchar_t>(inputFile),
        istream_iterator<wchar_t, wchar_t>()
    };

    if (lowercase) {
        for (int i = 0; i < fileContent.size(); i++) {
            fileContent[i] = towlower(fileContent[i]);
        }
    }

    /** 
     * Character count is stored in a map with key as character and value as count.
     * Ref: https://en.cppreference.com/w/cpp/container/unordered_map 
     */
    unordered_map<wchar_t, int> charCount;

    for (int i = 0; i < fileContent.size(); i++) {
        if (charCount.find(fileContent[i]) == charCount.end())
            charCount[fileContent[i]] = 1;
        else
            charCount[fileContent[i]]++;        
    }


    /** 
     * Output TAB separated values to the specified output file
     */
    std::wofstream fout(outputFileName);
    fout << "symbol\tcount" << endl;
    for (auto ch = charCount.begin(); ch != charCount.end(); ch++) {
        fout << ch->first << "\t" << ch->second << endl;
    }
    
    return 0;
}
