#include <iostream>

using namespace std;

void toh(int n, char start, char end, char aux) {
    if (n == 0)
        return;
    else {
        toh(n-1, start, aux, end);
        cout << "Moved Disk " << n << " from " << start << " to " << end << endl;
        toh(n-1, aux, end, start);
    }
}

int main() {
    int n;
    char start = 'A', aux = 'B', end = 'C';

    cout << "Enter the no. of disks: ";
    cin >> n;

    toh(n, start, end, aux);
    return 0;
}