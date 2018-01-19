class B {
    int num;
public:
    B(int a = 0, int b = 3): num(a + b) {}
    B& operator += (const B &obj) {
        int tmp = num + obj.num;
        num = tmp;
        return *this;
    }
    int get() {
        return num;
    }
};