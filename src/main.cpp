#include "main.hpp"

using namespace VHArgsParser;

/**
 *
 */
int main(int argc, char *argv[])
{
    VHCmdLineParser cmdline;
    verr parse_status;

    // Setup parameters
    {
        std::vector<VHArgTypeBase> arrcmd;

        arrcmd.push_back(VHArgTypeCommand("-add", "Add"));
        arrcmd.push_back(VHArgTypeCommand("-sub", "Sub"));

        arrcmd.push_back(VHArgTypeInteger("-va", "First arg", 3, 0, 100));
        arrcmd.push_back(VHArgTypeInteger("-vb", "Second arg", 2, 0, 100));

        // Test others
        arrcmd.push_back(VHArgTypeFileName("-file", "default.bin", "Simple file"));
        arrcmd.push_back(VHArgTypeString("-text", "abcdef", "Simple text"));

        arrcmd.push_back(VHArgTypeOption("-opta", "Option A", false));
        arrcmd.push_back(VHArgTypeOption("-optb", "Option B", false));

        parse_status = cmdline.ParseCommandLine(arrcmd, argc, argv);
    }

    // Check if cmd line parser correctly
    if (parse_status != vok)
        return 1;

    std::cout << "\n*** Internal parser content" << "\n";

    std::vector<std::string> arrParams = cmdline.listparams();

    for (const auto item : arrParams)
    {
        std::cout << item << "\n";
    }

    //
    std::cout << "\n*** Interface available content" << "\n";
    std::cout << "File Name  : " << " : " << cmdline.GetFileName("-file") << "\n";
    std::cout << "String     : " << " : " << cmdline.GetString("-text") << "\n";
    std::cout << "Command    : " << " : " << cmdline.GetCommand() << "\n";
    std::cout << "Int 1      : " << " : " << cmdline.GetInt("-va") << "\n";
    std::cout << "Int 2      : " << " : " << cmdline.GetInt("-vb") << "\n";
    std::cout << "Option A   : " << " : " << cmdline.GetOpt("-opta") << "\n";
    std::cout << "Option B   : " << " : " << cmdline.GetOpt("-optb") << "\n";
    std::cout << " \n";

    {
        const std::string &strcmd = cmdline.GetCommand();

        if (strcmd == "-add")
        {
            int a = cmdline.GetInt("-va");
            int b = cmdline.GetInt("-vb");
            int r = a + b;
            std::cout << "Result: " << r << "\n";
        }
        else if (strcmd == "-sub")
        {
            int a = cmdline.GetInt("-va");
            int b = cmdline.GetInt("-vb");
            int r = a - b;
            std::cout << "Result: " << r << "\n";
        }
        else
        {
            std::cout << "No operation specified" << "\n";
        }
    }

    std::cout << "\n";

    return 0;
}

/**
 *
 */
verr errlog(int x, const std::string &errmsg)
{

    std::string str;

    str.append("Error code: ");
    str.append(std::to_string(x));
    str.append(" Message: ");
    str.append(errmsg);

    std::cout << str << "\n";

    return x;
}

/**
 *
 */
verr VHArgsParser::verrmsg(int x, const std::string & errmsg)
{
    return errlog(x, errmsg);
}
