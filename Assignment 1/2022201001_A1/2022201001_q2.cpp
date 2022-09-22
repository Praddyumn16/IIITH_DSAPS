#include <iostream>
using namespace std;
//#define SIZE 5

template <typename T>

class dequeue
{

private:
    int front_, rear_, curr_size, SIZE = 5;
    T *arr;

public:
    dequeue()
    {
        front_ = -1;
        rear_ = -1;
        curr_size = 0;
        arr = new T[SIZE];
    }

    dequeue(int n, T x)
    {
        arr = new T[n];
        for (int i = 0; i < n; i++)
            arr[i] = x;
        front_ = 0;
        rear_ = n - 1;
        curr_size = SIZE = n;
    }

    void push_back(T x)
    {

        if ((front_ == 0 && rear_ == SIZE - 1) || (front_ == rear_ + 1))
        {

            SIZE *= 2;
            T *new_arr = new T[SIZE];

            int i = front_, j = 0;
            while (i != rear_)
            {
                new_arr[j] = arr[i];
                i = (i + 1) % SIZE;
                j++;
            }

            new_arr[j] = arr[i];
            front_ = 0, rear_ = curr_size - 1;

            delete[] arr;
            arr = new_arr;

            curr_size++;
            return;
        }

        if (rear_ == -1)
        {
            front_ = 0;
            rear_ = 0;
        }
        else if (rear_ == SIZE - 1)
            rear_ = 0;
        else
            rear_++;

        arr[rear_] = x;
        curr_size++;
    }

    void pop_back()
    {

        if (front_ == -1)
            return;
        
        if (front_ == rear_)
        {
            front_ = -1;
            rear_ = -1;
        }
        else
            rear_ = (rear_ - 1 + SIZE) % SIZE;

        curr_size--;
    }

    void push_front(T x)
    {

        if ((front_ == 0 && rear_ == SIZE - 1) || (front_ == rear_ + 1))
        {

            SIZE *= 2;
            T *new_arr = new T[SIZE];

            int i = front_, j = 0;
            while (i != rear_)
            {
                new_arr[j] = arr[i];
                i = (i + 1) % SIZE;
                j++;
            }

            new_arr[j] = arr[i];
            front_ = 0, rear_ = curr_size - 1;

            delete[] arr;
            arr = new_arr;

            curr_size++;
            return;
        }

        if (front_ == -1)
        {
            front_ = 0;
            rear_ = 0;
        }
        else if (front_ == 0)
            front_ = SIZE - 1;
        else
            front_--;

        arr[front_] = x;
        curr_size++;
    }

    void pop_front()
    {

        if (front_ == -1)
            return;

        if (front_ == rear_)
        {
            front_ = -1;
            rear_ = -1;
        }
        else
            front_ = (front_ + 1) % SIZE;

        curr_size--;
    }

    T front()
    {
        if (front_ == -1)
            return T();
        return arr[front_];
    }

    T back()
    {
        if (rear_ == -1)
            return T();
        return arr[rear_];
    }

    T operator[](int n)
    {
        if (n > curr_size)
        {
            cout << "invalid index" << endl;
            abort();
        }
        return arr[(front_ + n) % curr_size];
    }

    bool empty()
    {
        if (front_ == -1 && rear_ == -1)
            return true;
        else
            return false;
    }

    int size()
    {
        return curr_size;
    }

    void resize(int x, T d)
    {

        if (x == curr_size)
            return;
        else if (x > curr_size)
        {
            T *new_arr = new T(x);
            int temp = x - curr_size, i = front_, j = 0;
            while (i != rear_)
            {
                new_arr[j] = arr[i];
                i = (i + 1) % curr_size;
                j++;
            }
            new_arr[j] = arr[i];
            j++;
            while (temp--)
            {
                new_arr[j] = d;
                j++;
            }
            arr = new_arr;
            front_ = 0;
            rear_ = x - 1;
            curr_size = x;
        }
        else
        {
            T *new_arr = new T(x);
            int temp = curr_size - x, i = front_, j = 0;
            while (temp--)
            {
                new_arr[j] = arr[i];
                i = (i + 1) % curr_size;
                j++;
            }
            arr = new_arr;
            front_ = 0;
            rear_ = x - 1;
            curr_size = x;
        }
    }

    void clear()
    {
        delete[] arr;
        front_ = -1;
        rear_ = -1;
        curr_size = 0;
        SIZE = 5;
    }
};

int main()
{
    dequeue<int> DQ;
    int choice, flag = 1, n, val;

    while(flag) {
        cout << "-------------------------\n";
        cout << "choice: ";
        cin >> choice;
        switch(choice) {
            case 0:
                flag = 0;
                break;
            // case 1:
            //     DQ.deque();
            //     break;
            // case 2:
            //     cin >> n >> val;
            //     DQ.deque(n, val);
            //     break;
            case 3:
                cin >> val;
                DQ.push_back(val);
                break;
            case 4:
                DQ.pop_back();
                break;
            case 5:
                cin >> val;
                DQ.push_front(val);
                break;
            case 6:
                DQ.pop_front();
                break;
            case 7:
                cout << DQ.front() << endl;
                break;
            case 8:
                cout << DQ.back() << endl;
                break;
            case 9:
                cout << ((DQ.empty()) ? "true" : "false") << endl;
                break;
            case 10:
                cout << DQ.size() << endl;
                break;
            case 11:
                cin >> n >> val;
                DQ.resize(n, val);
                break;
            case 12:
                DQ.clear();
                break;
            case 13:
                cin >> n;
                cout << DQ[n] << endl;
                break;
            default:
                cout << "Enter correct choice\n";
        }
    }
    return 0;
}