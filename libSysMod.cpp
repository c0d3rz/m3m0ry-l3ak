#include "libSysMod.h"

using namespace std;

void sysCpu(string& inpCpuName, int& inpOpFreq, long& inpAccBal)
{
    vector<string> sysCpuVec;   // the CPU name vector list -- write down all the names of the CPU
    sysCpuVec.push_back("Choose CPU:");
    sysCpuVec.push_back("\t\t1.Intel Core Duo T2700 2.33 GHz");
    sysCpuVec.push_back("\t\t2. Intel Core Duo T2600 2.16 GHz");
    sysCpuVec.push_back("\t\t3. Xeon 5160 – 3.00 GHz (4 MB L2, 1333 MHz FSB, 80 W)");   // the specifications will be shown in another image
    sysCpuVec.push_back("\t\t4. Xeon 5150 – 2.66 GHz (4 MB L2, 1333 MHz FSB, 65 W)");
    sysCpuVec.push_back("\t\t5. Xeon X5355 – 2.66 GHz (2×4 MB L2, 1333 MHz FSB, 105 W)");
    sysCpuVec.push_back("\t\t6. AMD Turion 64 X2");
    sysCpuVec.push_back("\t\t7. AMD Athlon Regor");
    sysCpuVec.push_back("\t\t8. AMD Athlon Propus");

    // list the rest of the CPUs that will be featured in the game
}
