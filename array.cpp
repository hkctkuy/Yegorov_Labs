#include <iostream>

using namespace std;

class Arr {

    int *arr, begin, end;

  public:

    Arr(int inp_begin, int inp_end);

    Arr(const Arr & ref);

    ~Arr();

    Arr & set_val();

    void print() const;

    int & operator[](int index);

    Arr operator+(const Arr & b) const;

    Arr operator-(const Arr & b) const;

    Arr operator*(int scal) const;

    Arr operator/(int scal) const;

    bool correct() const {return arr != 0;}
};

Arr::Arr(int inp_begin, int inp_end) {

    if(inp_begin > inp_end) {

        cout << "Err: bed borders!";

        arr = 0; begin = 0; end = -1;

        return;
    }

    begin = inp_begin; end = inp_end;

    arr = new int[end - begin + 2];

    for (int i = begin; i <= end + 1; i++) {

        arr[i - begin] = 0;
    }
}

Arr::Arr(const Arr & ref) {

    begin = ref.begin; end = ref.end;

    arr = new int[end - begin + 2];

    for (int i = begin; i <= end + 1; i++) {

        arr[i - begin] = ref.arr[i - begin];
    }
}

Arr::~Arr() {

    delete [] arr;
}

Arr & Arr::set_val() {

    if (arr == 0) {

      cout << "Err: bed vector!";

      return *this;
    }

    for (int i = begin; i <= end; i++) {

        cin >> arr[i - begin];
    }
    return *this;
}

void Arr::print() const {

    if (arr == 0) {

        cout << "Err: bed vector!";

        return;
    }

    for (int i = begin; i <= end; i++) {

        cout << arr[i - begin] << ' ';
    }
    cout << endl;

    return;
}

int & Arr::operator[](int index) {

    if(index < begin || index > end) {

        cout << "Err: index is out of borders!" << endl;

        return *(arr + end + 1);
    }
    else {

        return *(arr - begin + index);
    }
}

Arr Arr::operator+(const Arr & b) const {

    if(begin != b.begin || end != b.end) {

        cout << "Err: different border values!" << endl;

        return Arr(0, 0);
    }
    else {

        Arr sum(begin, end);

        for (int i = begin; i <= end; i++) {

            sum.arr[i - begin] = arr[i - begin] + b.arr[i - begin];
        }
        return sum;
    }
}

Arr Arr::operator-(const Arr & b) const {

    if(begin != b.begin || end != b.end) {

        cout << "Err: different border values!" << endl;

        return Arr(0, 0);
    }
    else {

        Arr sum(begin, end);

        for (int i = begin; i <= end; i++) {

            sum.arr[i - begin] = arr[i - begin] - b.arr[i - begin];
        }
        return sum;
    }
}

Arr Arr::operator*(int scal) const {

    Arr prod(begin, end);


    for (int i = begin; i <= end; i++) {

        prod.arr[i - begin] = arr[i - begin] * scal;
    }
    return prod;
}

Arr Arr::operator/(int scal) const {

    Arr quot(begin, end);

    for (int i = begin; i <= end; i++) {

        quot.arr[i - begin] = arr[i - begin] / scal;
    }
    return quot;
}

int main() {

    cout << endl << "Enter borders of vector: ";
    int a, b;
    cin >> a >> b;
    Arr v1(a, b);
    cout << endl << "Enter coordinates of vector: ";
    v1.set_val();
    do {
        cout << endl << "Choose option for checking:" << endl <<
                        "1 - reinput all vector," << endl <<
                        "2 - output all vector," << endl <<
                        "3 - input some element," << endl <<
                        "4 - output some element," << endl <<
                        "5 - sum of 2 vector," << endl <<
                        "6 - difference of 2 vector," << endl <<
                        "7 - product of a vector and a scalar," << endl <<
                        "8 - quotient of a vector and a scalar" << endl <<
                        "and all other for end: ";
        char action;
        cin >> action;
        cout << endl;
        if (action == '1') {

            cout << "Enter new coordinates of vector: ";
            v1.set_val();
        }
        else if (action == '2') {

            v1.print();
        }
        else if (action == '3') {

            cout << "What element needs to be changed?: ";
            int num;
            cin >> num;
            cout << "Enter new value: ";
            cin >>v1[num];
        }
        else if (action == '4') {

            cout << "What element needs to be printed?: ";
            int num;
            cin >> num;
            cout << v1[num] << endl;
        }
        else if (action == '5') {

            cout << "Enter borders of second vector: ";
            int a, b;
            cin >> a >> b;
            Arr v2(a, b);
            if(!v2.correct()) continue;
            cout << endl << "Enter coordinates of second vector: ";
            v2.set_val();

            (v1 + v2).print();
        }
        else if (action == '6') {

            cout << "Enter borders of second vector: ";
            int a, b;
            cin >> a >> b;
            Arr v2(a, b);
            if(!v2.correct()) continue;
            cout << endl << "Enter coordinates of second vector: ";
            v2.set_val();

            (v1 - v2).print();
        }
        else if (action == '7') {

            cout << "Enter scalar: ";
            int scal;
            cin >> scal;
            cout << endl;

            (v1 * scal).print();
        }
        else if (action == '8') {

          cout << endl << "Enter scalar: ";
          int scal;
          cin >> scal;
          cout << endl;

          (v1 / scal).print();
        }
        else {

            break;
        }
    }
    while(true);
    cout <<"Good bye, Sweety!"<<endl;
    return 0;
}
