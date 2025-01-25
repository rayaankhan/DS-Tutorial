//Server Code
#include "global.h"

using namespace std;

float BLOCK_SIZE = 1;
uint BLOCK_COUNT = 2;
uint PRINT_COUNT = 20;
Logger logger;
vector<string> tokenizedQuery;
ParsedQuery parsedQuery;
TableCatalogue tableCatalogue; // keep the record of all the tables we are dealing or have loaded
BufferManager bufferManager; // simulation of ram, ram is limited so its like a queue, each table into pages (some rows, some cols, or some rows+some cols)

void doCommand()
{
    logger.log("doCommand");
    if (syntacticParse() && semanticParse())
        executeCommand();
    return;
}

int main(void)
{

    regex delim("[^\\s,]+");
    string command;
    system("rm -rf ../data/temp");
    system("mkdir ../data/temp");

    while(!cin.eof())
    {
        cout << "\n> ";
        tokenizedQuery.clear();
        parsedQuery.clear();
        logger.log("\nReading New Command: ");
        getline(cin, command);
        logger.log(command);


        auto words_begin = std::sregex_iterator(command.begin(), command.end(), delim);
        auto words_end = std::sregex_iterator();
        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
            tokenizedQuery.emplace_back((*i).str());

        if (tokenizedQuery.size() == 1 && tokenizedQuery.front() == "QUIT")
        {
            break;
        }

        if (tokenizedQuery.empty())
        {
            continue;
        }

        if (tokenizedQuery.size() == 1)
        {
            cout << "SYNTAX ERROR" << endl;
            continue;
        }

        doCommand();
    }
}