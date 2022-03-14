#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithm>

using namespace std;
using namespace::chrono;

void numberGeneration(vector<long long>& v, int vLength, long long valMax)
{
    long long num, p;
    int i, j, bit, power;
    // srand(time(NULL));
    v.resize(vLength);

    for(j = 0; j < vLength; j++)
    {
        power = 0;
        num = 0;
        p = 1;
        while(valMax > p)
        {
            p *= 2;
            power++;
        }

        p = 1;
        for(i = 0; i < power; i++)
        {
            bit = rand() % 2;
            num = num + bit * p;
            p *= 2;
        }

        if(num > valMax)
            num /= 4;

        v[j] = num;
    }
}

void checkSorted(vector<long long>& v, int vLength)
{
    int i, ok = 1;
    for(i = 1; i < vLength; i++)
        if(v[i] < v[i - 1])
        {
            ok = 0;
            break;
        }

    if(ok == 1)
        cout<<"Array Sorted"<<endl;
    else
        cout<<"Array Not Sorted"<<endl;
}

void mergeSortInterclasare(vector<long long>& v, vector<long long>& aux, int st, int mij, int dr)
{
    int i, j, k, t = 0;
    aux.resize(dr - st + 1);
    i = st;
    j = mij + 1;
    while(i <= mij && j <= dr)
        if(v[i] <= v[j])
        {
            aux[t] = v[i];
            t++;
            i++;
        }
        else
        {
            aux[t] = v[j];
            t++;
            j++;
        }

    while(i <= mij)
    {
        aux[t] = v[i];
        t++;
        i++;
    }

    while(j <= dr)
    {
        aux[t] = v[j];
        t++;
        j++;
    }

    t = 0;
    for(k = st; k <= dr; k++)
    {
        v[k] = aux[t];
        t++;
    }
}

void mergeSort(vector<long long>& v, vector<long long>& aux, int st, int dr)
{
    int mij;
    if(st < dr)
    {
        mij = (st + dr) / 2;
        mergeSort(v, aux, st, mij);
        mergeSort(v, aux, mij + 1, dr);
        mergeSortInterclasare(v, aux, st, mij, dr);
    }
}

void shellSort2k(vector<long long>& v, int vLength)
{
    int gaps[100], gapLength = 0, i, j, offset, k, aux2, po = 2;
    for(i = 0; po <= vLength; i++)
    {
        gaps[i] = vLength / po;
        gapLength++;
        po *= 2;
    }

    for(i = 0; i < gapLength; i++)
        for(offset = 0; offset < gaps[i]; offset++)
            for(k = offset; k < vLength; k += gaps[i])
            {
                aux2 = v[k];
                for(j = k; j >= gaps[i] && v[j - gaps[i]] > aux2; j -= gaps[i])
                    v[j] = v[j - gaps[i]];

                v[j] = aux2;
            }
}

void shellSortKnuth(vector<long long>& v, int vLength)
{
    int gaps[100] = {0}, gapLength = 0, i, j, offset, k, aux2, po = 3, gap;
    for(i = 0;; i++)
    {
        gap = (po - 1) / 2;
        if(gap < vLength)
        {
            gaps[i] = gap;
            gapLength++;
            po *= 3;
        }
        else
            break;
    }

    for(i = gapLength - 1; i >= 0; i--)
        for(offset = 0; offset < gaps[i]; offset++)
            for(k = offset; k < vLength; k += gaps[i])
            {
                aux2 = v[k];
                for(j = k; j >= gaps[i] && v[j - gaps[i]] > aux2; j -= gaps[i])
                    v[j] = v[j - gaps[i]];

                v[j] = aux2;
            }
}

long long radixSortMax(vector<long long>& v, int vLength)
{
    long long ma, i;
    ma = v[0];
    for(i = 1; i < vLength; i++)
        if(v[i] > ma)
            ma = v[i];

    return ma;
}

void radixSortCountingBase10(vector<long long>& v, vector<long long>& aux, int vLength, long long num)
{
    long long digits[10] = {0}, i;
    if(vLength >= 10)
        aux.resize(vLength);
    else
        aux.resize(10);

    for(i = 0; i < vLength; i++)
        digits[(v[i] / num) % 10]++;

    for(i = 1; i < 10; i ++)
        digits[i] += digits[i - 1];

    for(i = vLength - 1; i >= 0; i--)
    {
        aux[digits[(v[i] / num) % 10] - 1] = v[i];
        digits[(v[i] / num) % 10]--;
    }

    for(i = 0; i < vLength; i++)
        v[i] = aux[i];
}

void radixSortBase10(vector<long long>& v, vector<long long>& aux,  int vLength)
{
    long long ma, num;
    ma = radixSortMax(v, vLength);

    for(num = 1; ma / num > 0; num *= 10)
        radixSortCountingBase10(v, aux, vLength, num);
}

void radixSortCountingBinary(vector<long long>& v, vector<long long>& aux, int vLength, long long num)
{
    long long digits[65536] = {0}, i;
    if(vLength >= 65536)
        aux.resize(vLength);
    else
        aux.resize(65536);

    for(i = 0; i < vLength; i++)
        digits[(v[i] / num) & 0xFFFF]++;

    for(i = 1; i < 65536; i ++)
        digits[i] += digits[i - 1];

    for(i = vLength - 1; i >= 0; i--)
    {
        aux[digits[(v[i] / num) & 0xFFFF] - 1] = v[i];
        digits[(v[i] / num) & 0xFFFF]--;
    }

    for(i = 0; i < vLength; i++)
        v[i] = aux[i];
}

void radixSortBinary(vector<long long>& v, vector<long long>& aux,  int vLength)
{
    long long ma, num;
    ma = radixSortMax(v, vLength);

    for(num = 1; ma / num > 0; num = num << 16)
        radixSortCountingBinary(v, aux, vLength, num);
}

int qSortPartition(vector<long long>& v, int low, int high)   //pt partitionu normal
{
    int i, j;
    long long pivot;
    pivot = v[high];
    i = low;
    for(j = low; j <= high - 1; j++)
    {
        if(v[j] < pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    }

    swap(v[i + 1], v[high]);
    return i + 1;
}

/*void qSort(vector<long long>& v, int vLength, int low, int high)
{
    long long part;

    if(low < high)
    {
        part = qSortPartition(v, low, high);
        qSort(v, vLength, low, part - 1);
        qSort(v, vLength, part + 1, high);
    }
}

////////////////////////////////////////////////////////////

long long qSortMedianPivot(vector<long long>& v, int vLength, int low, int high)    //pt partitionu pt 3 median
{
    long long st, dr, mij, i, j, mijVal, aux;

    st = v[low];
    dr = v[vLength - 1];
    mij = high / 2;

    long long sortAr[] = {v[low], v[mij], v[high]};

    for(i = 0; i < 2; i ++)
        for(j = i + 1; j <= 2; j ++)
            if(v[i] > v[j])
                swap(v[i], v[j]);

    mijVal = sortAr[1];
    aux = v[high];
    v[high] = mijVal;

    if(mijVal == v[low])
        v[low] = aux;
    else if(mijVal == v[mij])
        v[mij] = aux;

    return(v, low, high);
}

void qSortMedian(vector<long long>& v, int vLength, int low, int high)
{
    long long pivot;

    if(low < high)
    {
        pivot = qSortMedianPivot(v, vLength, low, high);
        qSort(v, vLength, low, high);
    }
}  */

void countingSort(vector<long long>& v, int vLength, vector<long long>& frec, long long valMax)
{
    long long i, j, k = 0;
    frec.resize(valMax + 1);
    for(i = 0; i <= valMax; i++)
        frec[i] = 0;

    for(i = 0; i < vLength; i++)
        frec[v[i]]++;

    for(i = 0; i <= valMax; i++)
        for(j = 1; j <= frec[i]; j++)
        {
            v[k] = i;
            k++;
        }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void timSortMerge(vector<long long>& v, vector<long long>& vSt, vector<long long>& vDr, int st, int mij, int dr)
{
    long long len1, len2, i, j, k = st;

    len1 = mij - st + 1;
    len2 = dr - mij;
    vSt.resize(len1 + 1);
    vDr.resize(len2 + 1);

    for(i = 0; i < len1; i++)
        vSt[i] = v[st + i];
    for(i = 0; i < len2; i++)
        vDr[i] = v[mij + 1 + i];

    i = 0;
    j = 0;

    while(i < len1 && j < len2)
    {
        if(vSt[i] <= vDr[j])
        {
            v[k] = vSt[i];
            i++;
        }
        else
        {
            v[k] = vDr[j];
            j++;
        }

        k++;
    }

    while(i < len1)
    {
        v[k] = vSt[i];
        k++;
        i++;
    }

    while(j < len2)
    {
        v[k] = vDr[j];
        k++;
        j++;
    }

}

void timSortInsertion(vector<long long>& v, int st, int dr)
{
    long long i, j, aux;

    for(i = st + 1; i <= dr; i++)
    {
        aux = v[i];
        j = i - 1;
        while(j >= st && v[j] > aux)
        {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = aux;
    }
}



void timSort(vector<long long>&v, int vLength, vector<long long>& vSt, vector<long long>& vDr)
{
    long long i, mij, k = 32, s, mi, st, dr;

    for(i = 0; i < vLength; i += k)
    {
        if(i + k - 1 < vLength - 1)
            mi = i + k - 1;
        else
            mi = vLength - 1;

        timSortInsertion(v, i, mi);
    }

    for(s = k; s < vLength; s = s * 2)
    {
        for(st = 0; st < vLength; st = st + 2 * s)
        {
            mij = st + s - 1;
            if(st + 2 * s - 1 < vLength - 1)
                mi = st + 2 * s - 1;
            else
                mi = vLength - 1;

            dr = mi;
            if(mij < dr)
                timSortMerge(v, vSt, vDr, st, mij, dr);
        }

    }

}


int main()
{
    ifstream in("Date.in");

    long long valMax, ma = 0;
    int length, i, base = 10, T, k;
    vector<long long> v, v2, aux, frec, vSt, vDr;
    long long lengthV[50], valMaxV[50];

    in>>T;



    for(k = 1; k <= T; k++)
    {
        in>>lengthV[k];
        in>>valMaxV[k];
        cout<<"........................................N = "<<lengthV[k]<<" Max = "<<valMaxV[k]<<"........................................"<<endl<<endl;

        length = lengthV[k];
        valMax = valMaxV[k];

        numberGeneration(v, length, valMax);
        v2.resize(length);



        cout<<"C++ Sort (Introsort)"<<endl;
        for(i = 0; i < length; i++)
            v2[i] = v[i];
        auto start = high_resolution_clock::now();
        sort(v2.begin(), v2.end());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        checkSorted(v2, length);
        cout<<"Min: "<<duration.count() / 60000000<<endl<<"Sec: "<<(duration.count() - (duration.count() / 60000000) * 60000000) / 1000000<<endl<<"Milisec: "<<(duration.count() - (duration.count() / 1000000) * 1000000) / 1000<<endl<<endl;

        cout<<"MergeSort"<<endl;
        for(i = 0; i < length; i++)
            v2[i] = v[i];
        start = high_resolution_clock::now();
        mergeSort(v2, aux, 0, length - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        checkSorted(v2, length);
        cout<<"Min: "<<duration.count() / 60000000<<endl<<"Sec: "<<(duration.count() - (duration.count() / 60000000) * 60000000) / 1000000<<endl<<"Milisec: "<<(duration.count() - (duration.count() / 1000000) * 1000000) / 1000<<endl<<endl;

        cout<<"ShellSort2k"<<endl;
        for(i = 0; i < length; i++)
            v2[i] = v[i];
        start = high_resolution_clock::now();
        shellSort2k(v2, length);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        checkSorted(v2, length);
        cout<<"Min: "<<duration.count() / 60000000<<endl<<"Sec: "<<(duration.count() - (duration.count() / 60000000) * 60000000) / 1000000<<endl<<"Milisec: "<<(duration.count() - (duration.count() / 1000000) * 1000000) / 1000<<endl<<endl;

        cout<<"ShellSortKnuth"<<endl;
        for(i = 0; i < length; i++)
            v2[i] = v[i];
        start = high_resolution_clock::now();
        shellSortKnuth(v2, length);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        checkSorted(v2, length);
        cout<<"Min: "<<duration.count() / 60000000<<endl<<"Sec: "<<(duration.count() - (duration.count() / 60000000) * 60000000) / 1000000<<endl<<"Milisec: "<<(duration.count() - (duration.count() / 1000000) * 1000000) / 1000<<endl<<endl;

        cout<<"RadixSortBase10"<<endl;
        for(i = 0; i < length; i++)
            v2[i] = v[i];
        start = high_resolution_clock::now();
        radixSortBase10(v2, aux, length);             //sa fac pt mm baze
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        checkSorted(v2, length);
        cout<<"Min: "<<duration.count() / 60000000<<endl<<"Sec: "<<(duration.count() - (duration.count() / 60000000) * 60000000) / 1000000<<endl<<"Milisec: "<<(duration.count() - (duration.count() / 1000000) * 1000000) / 1000<<endl<<endl;

        cout<<"RadixSortBinary"<<endl;
        for(i = 0; i < length; i++)
            v2[i] = v[i];
        start = high_resolution_clock::now();
        radixSortBinary(v2, aux, length);             //sa fac pt mm baze
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        checkSorted(v2, length);
        cout<<"Min: "<<duration.count() / 60000000<<endl<<"Sec: "<<(duration.count() - (duration.count() / 60000000) * 60000000) / 1000000<<endl<<"Milisec: "<<(duration.count() - (duration.count() / 1000000) * 1000000) / 1000<<endl<<endl;

        cout<<"TimSort"<<endl;
        for(i = 0; i < length; i++)
            v2[i] = v[i];
        start = high_resolution_clock::now();
        timSort(v2, length, vSt, vDr);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        checkSorted(v2, length);
        cout<<"Min: "<<duration.count() / 60000000<<endl<<"Sec: "<<(duration.count() - (duration.count() / 60000000) * 60000000) / 1000000<<endl<<"Milisec: "<<(duration.count() - (duration.count() / 1000000) * 1000000) / 1000<<endl<<endl;
    }

    cout<<"###CountingSort a fost facut la final pt a nu da crash la tot programul in cazul unor valori prea mari (peste 3 * 10^9)###"<<endl<<endl;

    for(k = 1; k <= T; k++)
    {
        cout<<"........................................N = "<<lengthV[k]<<" Max = "<<valMaxV[k]<<"........................................"<<endl<<endl;

        length = lengthV[k];
        valMax = valMaxV[k];

        numberGeneration(v, length, valMax);
        v2.resize(length);

        if(valMax <= 3000000000)
        {

            cout<<"CountingSort"<<endl;
            for(i = 0; i < length; i++)
                v2[i] = v[i];
            auto start = high_resolution_clock::now();
            countingSort(v2, length, frec, valMax);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            checkSorted(v2, length);
            cout<<"Min: "<<duration.count() / 60000000<<endl<<"Sec: "<<(duration.count() - (duration.count() / 60000000) * 60000000) / 1000000<<endl<<"Milisec: "<<(duration.count() - (duration.count() / 1000000) * 1000000) / 1000<<endl<<endl;
        }
        else
            cout<<"CountingSort: Nu functioneaza pt valori mai mari de 3 * 10^9, deci sortarea nu a fost realizata"<<endl;
    }

    return 0;
}
