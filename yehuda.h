#ifdef __cplusplus
extern "C" {
#endif
    
    void initStockfish(unsigned long threads, unsigned long long memory, unsigned int time);
    void go(const char* fen);
    void stop();
    
#ifdef __cplusplus
}
#endif