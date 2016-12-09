#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cstreamgeo/cstreamgeo.h>

void full_random_alignment_benchmark(const size_t u_n, const size_t v_n, const size_t iterations) {
    double time_accum = 0;
    for (size_t j = 0; j < iterations; j++) {
        srand(time(NULL));
        const stream_t* u = stream_create(u_n);
        float* u_data = u->data;
        const stream_t* v = stream_create(v_n);
        float* v_data = v->data;
        float* cost = malloc(sizeof(float));
        size_t* path_length = malloc(sizeof(size_t));

        for (size_t i = 0; i < u_n; ++i) {
            u_data[2*i] = (float) (i * 1.0 * rand() / RAND_MAX);
            u_data[2*i+1] = (float) (i * 1.0 * rand() / RAND_MAX);
        }
        for (size_t i = 0; i < v_n; ++i) {
            v_data[2*i] = (float) (i * 1.0 * rand() / RAND_MAX);
            v_data[2*i+1] = (float) (i * 1.0 * rand() / RAND_MAX);
        }

        clock_t start, end;
        start = clock();
        const size_t* warp_path = full_align(u, v, cost, path_length);
        end = clock();
        time_accum += ((double) (end - start)) / CLOCKS_PER_SEC;

        free((void *) warp_path);
        free(cost);
        free(path_length);
        stream_destroy(u);
        stream_destroy(v);
    }
    printf("%zu iterations of %zu by %zu full time warp with path took %f millis, average=%f\n", iterations, u_n, v_n, 1000.0*time_accum, (1000.0*time_accum) / iterations);
}

void fast_random_alignment_benchmark(const size_t u_n, const size_t v_n, const size_t radius, const size_t iterations) {
        double time_accum = 0;
    for (size_t j = 0; j < iterations; j++) {
        srand(time(NULL));
        const stream_t* u = stream_create(u_n);
        float* u_data = u->data;
        const stream_t* v = stream_create(v_n);
        float* v_data = v->data;
        float* cost = malloc(sizeof(float));
        size_t* path_length = malloc(sizeof(size_t));

        for (size_t i = 0; i < u_n; ++i) {
            u_data[2*i] = (float) (i * 1.0 * rand() / RAND_MAX);
            u_data[2*i+1] = (float) (i * 1.0 * rand() / RAND_MAX);
        }
        for (size_t i = 0; i < v_n; ++i) {
            v_data[2*i] = (float) (i * 1.0 * rand() / RAND_MAX);
            v_data[2*i+1] = (float) (i * 1.0 * rand() / RAND_MAX);
        }

        clock_t start, end;
        start = clock();
        const size_t* warp_path = fast_align(u, v, radius, cost, path_length);
        end = clock();
        time_accum += ((double) (end - start)) / CLOCKS_PER_SEC;

        free((void *) warp_path);
        free(cost);
        free(path_length);
        stream_destroy(u);
        stream_destroy(v);
    }
    printf("%zu iterations of %zu by %zu fast time warp with path took %f millis, average=%f\n", iterations, u_n, v_n, 1000.0*time_accum, (1000.0*time_accum) / iterations);
}

// Benchmark files aren't very useful until they have real code.
int main() {
/*
    for (size_t i = 100; i < 1000; i += 10) {
        full_random_alignment_benchmark(i, i, 30);
    }
    for (size_t i = 1000; i <= 3000; i += 100) {
        full_random_alignment_benchmark(i, i, 30);
    }
*/
    for (size_t i = 100; i < 1000; i += 10) {
        fast_random_alignment_benchmark(i, i, 0, 30);
    }
    for (size_t i = 1000; i <= 3000; i += 100) {
        fast_random_alignment_benchmark(i, i, 0, 30);
    }
}

