template<typename T>
struct monoid_min{
    T val;

    monoid_min(){
        val = numeric_limits<T>::max();
    }

    monoid_min(T x){
        val = x;
    }

    monoid_min e(){
        return monoid_min();
    }

    monoid_min operator*(monoid_min other){
        if(val < other.val) return *this;
        return other;
    }

    bool operator==(monoid_min other){
        return val == other.val;
    }

    string to_str(){
        if(*this == monoid_min()) return "inf";
        return to_string(val);
    }
};
