template<typename T>
struct monoid_max{
    T val;

    monoid_max(){
        val = numeric_limits<T>::min();
    }

    monoid_max(T x){
        val = x;
    }

    monoid_max e(){
        return monoid_max();
    }

    monoid_max operator*(monoid_max other){
        if(val > other.val) return *this;
        return other;
    }

    bool operator==(monoid_max other){
        return val == other.val;
    }

    string to_str(){
        if(*this == monoid_max()) return "-inf";
        return to_string(val);
    }
};
