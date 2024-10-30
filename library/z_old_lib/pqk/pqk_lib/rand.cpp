random_device seed_gen;
mt19937 engine(seed_gen());

template<typename T>
T rnd();
template<typename T>
T rnd(int n);

template<>
uint rnd<uint>(){
    return engine();
}

template<>
uint64_t rnd<uint64_t>(){
    uint64_t a = engine();
    uint64_t b = engine();
    return (a << 32) + b;
}

template<>
int rnd<int>(){
    return rnd<uint>();
}

template<>
int64_t rnd<int64_t>(){
    return rnd<uint64_t>();
}

template<>
char rnd<char>(){
    //32~126
    return engine()%95+32; 
}

template<>
string rnd<string>(int n){
    string rtn;
    for(int i = 0; i < n; i++) rtn.push_back(rnd<char>());
    return rtn;
}
