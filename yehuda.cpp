#include "yehuda.h"

#include <sstream>
#include "bitboard.h"
#include "evaluate.h"
#include "position.h"
#include "search.h"
#include "thread.h"
#include "tt.h"
#include "uci.h"
//#include "syzygy/tbprobe.h"

std::string cmd;

void initStockfish(unsigned long threads, unsigned long long memory, unsigned int time) {

    UCI::init(Options);
    PSQT::init();
    Bitboards::init();
    Position::init();
    Bitbases::init();
    Search::init();
    Eval::init();
    Pawns::init();
    Threads.init();
    //Tablebases::init(Options["SyzygyPath"]);
    TT.resize(Options["Hash"]);
    
    std::string tstr = "name Threads value " + std::to_string(threads);
    std::istringstream tis(tstr);
    UCI::ysetoption(tis);
    
    std::string mstr = "name Hash value " + std::to_string(memory);
    std::istringstream mis(mstr);
    UCI::ysetoption(mis);
    
    while(true) {
        if(cmd.empty()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
        else if(cmd == "STOP") {
            UCI::ystop();
        } else {
            std::string gstr = "movetime ";
            gstr += std::to_string(time);
            std::istringstream gis(gstr);
            UCI::ygo(cmd, gis);
            cmd = "";
        }
    }
}

void go(const char* fen) {
    cmd = std::string(fen);
}

void stop() {
    cmd = "STOP";
}
