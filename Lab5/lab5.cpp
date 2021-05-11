#include  <iostream>
using namespace std;

int abs(int x){
    if (x < 0){
        return -x;
    }
    return x;
}

struct Point3D{
    int x;
    int y;
    int z;

    Point3D(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    int l1norm(Point3D *p){
        return abs(x - p->x) + abs(y - p->y) + abs(z - p->z);
    }
};


int main(){
    Point3D last_point(0, 0, 0);
    int n_test, n_lines;
    cin >> n_test;
    for (int i=0; i<n_test; i++){
        cin >> n_lines;
        for (int j=0; j<n_lines; j++){
            int x, y, z;
            cin >> x >> y >> z;
            Point3D temp(x, y, z);
            if (j!=0){
                cout << temp.l1norm(&last_point) << endl;
            }
            last_point = temp;
        }
    }
    return 0;
}