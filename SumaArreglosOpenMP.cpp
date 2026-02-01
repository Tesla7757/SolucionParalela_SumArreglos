// SumaArreglosOpenMP.cpp

#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    const int N = 1000000;

    int* A = new int[N];
    int* B = new int[N];
    int* R = new int[N];

    // Inicializar arreglos
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    // -----------------------
    // EJECUCIÓN SECUENCIAL
    // -----------------------
    auto inicio_seq = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        R[i] = A[i] + B[i];
    }

    auto fin_seq = high_resolution_clock::now();
    duration<double> tiempo_seq = fin_seq - inicio_seq;

    cout << "Tiempo secuencial: "
        << tiempo_seq.count() << " segundos\n";

    // -----------------------
    // EJECUCIÓN PARALELA
    // -----------------------
    omp_set_num_threads(4);

    auto inicio_par = high_resolution_clock::now();

#pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        int hilo = omp_get_thread_num();
        printf("Hilo %d procesa i = %d\n", hilo, i);
        R[i] = A[i] + B[i];
    }

    auto fin_par = high_resolution_clock::now();
    duration<double> tiempo_par = fin_par - inicio_par;

    cout << "Tiempo paralelo: "
        << tiempo_par.count() << " segundos\n";

    // Verificación
    cout << "\nPrimeros 5 resultados:\n";
    for (int i = 0; i < 5; i++) {
        cout << "R[" << i << "] = "
            << A[i] << " + " << B[i]
            << " = " << R[i] << endl;
    }

    delete[] A;
    delete[] B;
    delete[] R;

    return 0;
}
